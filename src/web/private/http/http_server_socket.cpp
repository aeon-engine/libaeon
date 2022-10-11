// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/constants.h>
#include <aeon/web/http/url_encoding.h>
#include <aeon/sockets/config.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/string_stream.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/common/string_utils.h>

namespace aeon::web::http
{

http_server_socket::http_server_socket(asio::ip::tcp::socket socket)
    : tcp_socket{std::move(socket)}
    , state_{http_state::server_read_method}
    , request_{http_method::invalid}
    , circular_buffer_{streams::circular_buffer_filter{},
                       streams::memory_device<std::vector<char>>{sockets::tcp_socket_circular_buffer_size}}
    , expected_content_length_{0}
{
}

http_server_socket::~http_server_socket() = default;

void http_server_socket::respond(const common::string &content_type, const common::string &data, const status_code code)
{
    streams::string_stream<std::vector<std::byte>> sstream{std::size(data)};
    sstream << data;
    respond(content_type, sstream.release(), code);
}

void http_server_socket::respond(const common::string &content_type, std::vector<std::byte> data,
                                 const status_code code)
{
    streams::string_stream<std::vector<std::byte>> sstream{64};
    sstream << detail::http_version_string;
    sstream << ' ';
    sstream << std::to_string(static_cast<int>(code));
    sstream << ' ';
    sstream << status_code_to_string(code);
    sstream << "\r\n";
    sstream << "Connection: keep-alive\r\n";
    sstream << "Content-type: ";
    sstream << content_type;
    sstream << "\r\n";
    sstream << "Content-Length: ";
    sstream << std::to_string(std::size(data));
    sstream << "\r\n\r\n";

    send(sstream.release());
    send(std::move(data));
    __reset_state();
}

void http_server_socket::on_data(const std::span<const std::byte> &data)
{
    circular_buffer_.write(std::data(data), std::size(data));
    streams::stream_reader reader(circular_buffer_);

    while (circular_buffer_.size() != 0)
    {
        if (state_ == http_state::server_read_body)
        {
            std::vector<std::byte> vec;
            reader.read_to_vector(vec);
            request_.append_raw_content_data(vec);

            if (request_.get_content_length() >= expected_content_length_)
                __enter_reply_state();
        }
        else
        {
            const auto result = __on_line(reader.read_line());
            if (result != status_code::ok)
            {
                respond_default(result);
                disconnect();
                return;
            }
        }
    }
}

auto http_server_socket::__on_line(const common::string &line) -> status_code
{
    switch (state_)
    {
        case http_state::server_read_method:
            return __handle_read_method_state(line);
        case http_state::server_read_headers:
            return __handle_read_headers_state(line);

        // Unexpected read body state. Body must be read binary.
        // If this happens, there is a bug.
        case http_state::server_read_body:
            return status_code::internal_server_error;

        // Did not expect to receive more data in reply state.
        case http_state::server_reply:
            return status_code::bad_request;
        // If default happens, there is a bug.
        default:
            return status_code::internal_server_error;
    }
}

void http_server_socket::respond_default(const status_code code)
{
    respond(detail::default_response_content_type, status_code_to_string(code), code);
}

auto http_server_socket::__parse_expected_content_length_and_type() -> status_code
{
    const auto http_headers = parse_raw_http_headers(request_.get_raw_headers());

    const auto content_length_result = http_headers.find(detail::content_length_key);

    if (content_length_result == http_headers.end())
        return status_code::length_required;

    const auto content_type_result = http_headers.find(detail::content_type_key);

    if (content_type_result == http_headers.end())
        return status_code::bad_request;

    expected_content_length_ = std::stoll(content_length_result->second.str());
    request_.set_content_type(content_type_result->second);
    return status_code::ok;
}

auto http_server_socket::__enter_parse_body_state() -> status_code
{
    const auto result = __parse_expected_content_length_and_type();

    // If there was a parse error for the content length
    if (result != status_code::ok)
        return result;

    // If content length is simply 0.
    if (expected_content_length_ == 0)
    {
        __enter_reply_state();
        return status_code::ok;
    }

    state_ = http_state::server_read_body;
    return status_code::ok;
}

void http_server_socket::__enter_reply_state()
{
    state_ = http_state::server_reply;
    on_http_request(request_);
}

auto http_server_socket::__handle_read_method_state(const common::string &line) -> status_code
{
    auto method_line_split = common::string_utils::split(line, ' ');

    if (method_line_split.size() != 3)
        return status_code::bad_request;

    const auto method = method_line_split[0];
    const auto request_uri = method_line_split[1];
    const auto version_string = method_line_split[2];

    if (!detail::validate_http_version_string(common::string{version_string.as_std_u8string_view()}))
        return status_code::http_version_not_supported;

    if (!detail::validate_uri(common::string{request_uri.as_std_u8string_view()}))
        return status_code::bad_request;

    const request request(method, url_decode(request_uri));

    if (request.get_method() == http_method::invalid)
        return status_code::method_not_allowed;

    request_ = request;
    state_ = http_state::server_read_headers;

    return status_code::ok;
}

auto http_server_socket::__handle_read_headers_state(const common::string &line) -> status_code
{
    if (line.empty())
    {
        if (request_.get_method() == http_method::post)
            return __enter_parse_body_state();

        __enter_reply_state();
        return status_code::ok;
    }

    request_.append_raw_http_header_line(line);
    return status_code::ok;
}

void http_server_socket::__reset_state()
{
    state_ = http_state::server_read_method;
    request_ = request{http_method::invalid};
    expected_content_length_ = 0;
}
} // namespace aeon::web::http

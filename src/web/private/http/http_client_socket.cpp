// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/http_client_socket.h>
#include <aeon/web/http/url_encoding.h>
#include <aeon/web/http/constants.h>
#include <aeon/sockets/config.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/string_stream.h>
#include <aeon/common/string_utils.h>
#include <aeon/common/u8_stream.h>
#include <aeon/common/assert.h>

namespace aeon::web::http
{

http_client_socket::http_client_socket(asio::io_context &context)
    : tcp_socket{context}
    , state_{http_state::client_read_status}
    , reply_{}
    , circular_buffer_{streams::circular_buffer_filter{},
                       streams::memory_device<std::vector<char>>{sockets::tcp_socket_circular_buffer_size}}
    , expected_content_length_{0}
{
}

http_client_socket::~http_client_socket() = default;

void http_client_socket::request_async(const std::u8string &host, const std::u8string &uri,
                                       [[maybe_unused]] const http_method method)
{
    // TODO: Use the given method for the request, instead of just GET
    streams::string_stream<std::vector<std::byte>> request{64};
    request << "GET ";
    request << url_encode(uri);
    request << ' ';
    request << detail::http_version_string;
    request << "\r\n";
    request << "Host: ";
    request << host;
    request << "\r\n\r\n";

    send(request.release());
}

void http_client_socket::on_data(const std::span<const std::byte> &data)
{
    circular_buffer_.write(std::data(data), std::size(data));
    streams::stream_reader reader(circular_buffer_);

    while (circular_buffer_.size() != 0)
    {
        if (state_ == http_state::client_read_body)
        {
            std::vector<std::byte> vec;
            reader.read_to_vector(vec);
            reply_.append_raw_content_data(vec);

            if (reply_.get_content_length() >= expected_content_length_)
            {
                disconnect();
                on_http_reply(reply_);
            }
        }
        else
        {
            const auto result = __on_line(reader.read_u8line());
            if (!result)
            {
                // TODO: Better error code here.
                on_error(std::error_code{});
                disconnect();
                return;
            }
        }
    }
}

auto http_client_socket::__on_line(const std::u8string &line) -> bool
{
    /*
    HTTP/1.1 200 Ok
    Connection: close
    Content-type: text/plain
    Content-Length: 6

    Hello!
    */

    switch (state_)
    {
        case http_state::client_read_status:
            return __handle_read_status_state(line);
        case http_state::client_read_headers:
            return __handle_read_headers_state(line);

        // Unexpected read body state. Body must be read binary.
        // If this happens, there is a bug.
        case http_state::client_read_body:
            aeon_assert_fail("Unexpected read body state.");
            return false;

        default:
            return false;
    }
}

auto http_client_socket::__parse_expected_content_length() -> bool
{
    const auto http_headers = parse_raw_http_headers(reply_.get_raw_headers());

    const auto result = http_headers.find(detail::content_length_key);

    if (result == http_headers.end())
        return false;

    // TODO: Fix when there is a way to convert utf8 strings to numbers
    const auto str = std::string{std::begin(result->second), std::end(result->second)};
    expected_content_length_ = std::stoll(str);
    return true;
}

auto http_client_socket::__handle_read_status_state(const std::u8string &line) -> bool
{
    auto status_line_split = common::string_utils::split(line, ' ');

    // The line looks like this: "HTTP/1.1 200 Ok"
    // We only need to parse the version string and the status code.
    // We don't really care about the status text.
    if (status_line_split.size() < 2)
        return false;

    const auto version_string = status_line_split[0];
    const auto status_code_string = status_line_split[1];

    auto status_code_int = 0;

    try
    {
        // TODO: Fix when stoi supports utf8.
        const auto str = std::string{std::cbegin(status_code_string), std::end(status_code_string)};
        status_code_int = std::stoi(str);
    }
    catch (const std::invalid_argument &)
    {
        return false;
    }

    if (!verify_status_code(status_code_int))
        return false;

    reply_ = reply(static_cast<status_code>(status_code_int));
    state_ = http_state::client_read_headers;

    return true;
}

auto http_client_socket::__handle_read_headers_state(const std::u8string &line) -> bool
{
    if (line.empty())
    {
        if (!__parse_expected_content_length())
            return false;

        state_ = http_state::client_read_body;
        return true;
    }

    reply_.append_raw_http_header_line(line);
    return true;
}

} // namespace aeon::web::http

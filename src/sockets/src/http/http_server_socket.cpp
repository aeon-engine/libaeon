/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/sockets/http/http_server_socket.h>
#include <aeon/sockets/http/constants.h>
#include <aeon/sockets/http/url_encoding.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/string.h>

namespace aeon::sockets::http
{

http_server_socket::http_server_socket(asio::ip::tcp::socket socket)
    : tcp_socket{std::move(socket)}
    , state_{http_state::server_read_method}
    , request_{http_method::invalid}
    , circular_buffer_{}
    , expected_content_length_{0}
{
}

http_server_socket::~http_server_socket() = default;

void http_server_socket::respond(const std::string &content_type, const std::string &data, const status_code code)
{
    streams::memory_stream stream;

    stream.write(reinterpret_cast<const std::uint8_t *>(data.c_str()), data.size());
    respond(content_type, stream, code);
}

void http_server_socket::respond(const std::string &content_type, streams::stream &data, const status_code code)
{
    streams::memory_stream stream;
    auto headers = detail::http_version_string + " " + std::to_string(static_cast<int>(code)) + " " +
                   status_code_to_string(code) +
                   "\r\n"
                   "Connection: keep-alive\r\n"
                   "Content-type: " +
                   content_type +
                   "\r\n"
                   "Content-Length: " +
                   std::to_string(data.size()) + "\r\n\r\n";

    stream.write(reinterpret_cast<const std::uint8_t *>(headers.c_str()), headers.size());
    send(stream);
    send(data);
    __reset_state();
}

void http_server_socket::on_data(const std::uint8_t *data, const std::size_t size)
{
    circular_buffer_.write(data, size);
    streams::stream_reader reader(circular_buffer_);

    while (!circular_buffer_.empty())
    {
        if (state_ == http_state::server_read_body)
        {
            request_.append_raw_content_data(circular_buffer_.read_to_vector());

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

auto http_server_socket::__on_line(const std::string &line) -> status_code
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

    expected_content_length_ = std::stoll(content_length_result->second);
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

auto http_server_socket::__handle_read_method_state(const std::string &line) -> status_code
{
    auto method_line_split = common::string::split(line, ' ');

    if (method_line_split.size() != 3)
        return status_code::bad_request;

    const auto method = method_line_split[0];
    const auto request_uri = method_line_split[1];
    const auto version_string = method_line_split[2];

    if (!detail::validate_http_version_string(version_string))
        return status_code::http_version_not_supported;

    if (!detail::validate_uri(request_uri))
        return status_code::bad_request;

    request request(method, url_decode(request_uri));

    if (request.get_method() == http_method::invalid)
        return status_code::method_not_allowed;

    request_ = request;
    state_ = http_state::server_read_headers;

    return status_code::ok;
}

auto http_server_socket::__handle_read_headers_state(const std::string &line) -> status_code
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
} // namespace aeon::sockets::http

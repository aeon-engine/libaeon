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

#include <aeon/sockets/http/http_client_socket.h>
#include <aeon/sockets/http/url_encoding.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/sockets/http/constants.h>
#include <aeon/common/string.h>

namespace aeon::sockets::http
{

http_client_socket::http_client_socket(asio::io_context &context)
    : tcp_socket{context}
    , state_{http_state::client_read_status}
    , reply_{}
    , circular_buffer_{}
    , expected_content_length_{0}
{
}

http_client_socket::~http_client_socket() = default;

void http_client_socket::request_async(const std::string &host, const std::string &uri, const http_method method)
{
    streams::memory_stream stream;
    auto request = "GET " + url_encode(uri) + " " + detail::http_version_string + "\r\n" + "Host: " + host + "\r\n\r\n";

    stream.write(reinterpret_cast<const std::uint8_t *>(request.c_str()), request.size());
    send(stream);
}

void http_client_socket::on_data(const std::uint8_t *data, const std::size_t size)
{
    circular_buffer_.write(data, size);
    streams::stream_reader<streams::circular_buffer_stream<AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE>> reader(
        circular_buffer_);

    while (circular_buffer_.size() != 0)
    {
        if (state_ == http_state::client_read_body)
        {
            reply_.append_raw_content_data(circular_buffer_.read_to_vector());

            if (reply_.get_content_length() >= expected_content_length_)
            {
                disconnect();
                on_http_reply(reply_);
            }
        }
        else
        {
            const auto result = __on_line(reader.read_line());
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

auto http_client_socket::__on_line(const std::string &line) -> bool
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

    expected_content_length_ = std::stoll(result->second);
    return true;
}

auto http_client_socket::__handle_read_status_state(const std::string &line) -> bool
{
    auto status_line_split = common::string::split(line, ' ');

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
        status_code_int = std::stoi(status_code_string);
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

auto http_client_socket::__handle_read_headers_state(const std::string &line) -> bool
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

} // namespace aeon::sockets::http

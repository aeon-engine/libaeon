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

#include <aeon/sockets/webserver/http_protocol_handler.h>
#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/string.h>
#include <iostream>

namespace aeon::webserver
{

static const auto status_ok = "Ok";
static const auto status_not_found = "Not Found";
static const auto status_internal_server_error = "Internal Server Error";

static const auto content_length_key = "Content-Length";

http_protocol_handler::http_protocol_handler(asio::ip::tcp::socket socket)
    : sockets::tcp_server<http_protocol_handler>::protocol_handler(std::move(socket))
    , state_(http_state::read_method)
    , request_(this, http_method::invalid)
    , circular_buffer_()
    , expected_content_length_(0)
{
}

void http_protocol_handler::respond(const std::string &content_type, const std::string &data, status_code code)
{
    streams::memory_stream stream;

    stream.write(reinterpret_cast<const std::uint8_t *>(data.c_str()), data.size());
    respond(content_type, stream, code);
}

void http_protocol_handler::respond(const std::string &content_type, streams::stream &data, status_code code)
{
    streams::memory_stream stream;
    auto headers = "HTTP/1.0 " + std::to_string(static_cast<int>(code)) + " " + __http_status_to_string(code) +
                   "\r\n"
                   "Connection: close\r\n" // TODO: Support keep-alive
                   "Content-type: " +
                   content_type +
                   "\r\n"
                   "Content-Length: " +
                   std::to_string(data.size()) + "\r\n\r\n";

    stream.write(reinterpret_cast<const std::uint8_t *>(headers.c_str()), headers.size());
    send(stream);
    send(data);
}

void http_protocol_handler::on_data(std::uint8_t *data, std::size_t size)
{
    circular_buffer_.write(data, size);
    streams::stream_reader<streams::circular_buffer_stream<AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE>> reader(
        circular_buffer_);

    while (circular_buffer_.size() != 0)
    {
        if (state_ == http_state::read_body)
        {
            request_.append_raw_content_data(circular_buffer_.read_to_vector());

            if (request_.content_length() >= expected_content_length_)
                __enter_reply_state();
        }
        else
        {
            __on_line(reader.read_line());
        }
    }
}

void http_protocol_handler::__on_line(const std::string &line)
{
    switch (state_)
    {
        case http_state::read_method:
        {
            auto method_line_split = common::string::split(line, ' ');

            if (method_line_split.size() != 3)
            {
                std::cout << "TODO: Method Parse error." << std::endl;
                return;
            }

            const auto method = method_line_split[0];
            const auto request_uri = method_line_split[1];
            const auto version_string = method_line_split[2];

            http_request request(this, method, request_uri, version_string);

            if (request.method() == http_method::invalid)
            {
                std::cout << "TODO: Method Parse error." << std::endl;
                return;
            }

            request_ = request;
            state_ = http_state::read_headers;
        }
        break;

        case http_state::read_headers:
        {
            if (line.empty())
            {
                if (request_.method() == http_method::post)
                {
                    __enter_parse_body_state();
                    return;
                }

                __enter_reply_state();
                return;
            }

            request_.append_raw_http_header_line(line);
        }
        break;

        case http_state::read_body:
        {
            std::cout << "TODO: Unexpected read body state. Body must be read binary.\n";
        }
        break;

        case http_state::reply:
        {
            std::cout << "TODO: Did not expect to receive more data in "
                         "reply state: '"
                      << line << "'\n";
            return;
        }
        break;
    }
}

void http_protocol_handler::respond_default(const status_code code)
{
    respond("text/plain", __http_status_to_string(code), code);
}

auto http_protocol_handler::__http_status_to_string(const status_code code) const -> const char *
{
    switch (code)
    {
        case status_code::ok:
            return status_ok;
        case status_code::not_found:
            return status_not_found;
        case status_code::internal_server_error:
            return status_internal_server_error;
    }

    return status_internal_server_error;
}

void http_protocol_handler::__parse_expected_content_length()
{
    const auto http_headers = parse_raw_http_headers(request_.raw_headers());

    const auto result = http_headers.find(content_length_key);

    if (result == http_headers.end())
        return;

    expected_content_length_ = std::stoll(result->second);
}

void http_protocol_handler::__enter_parse_body_state()
{
    __parse_expected_content_length();

    if (expected_content_length_ == 0)
    {
        __enter_reply_state();
        return;
    }

    state_ = http_state::read_body;
}

void http_protocol_handler::__enter_reply_state()
{
    state_ = http_state::reply;
    on_http_request(request_);
}
} // namespace aeon::webserver

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

#pragma once

#include <aeon/sockets/webserver/http_request.h>
#include <aeon/sockets/tcp_server.h>
#include <aeon/sockets/config.h>
#include <aeon/streams/circular_buffer_stream.h>
#include <asio.hpp>
#include <string>

namespace aeon::webserver
{

enum class status_code
{
    ok = 200,
    not_found = 404,
    internal_server_error = 500,
};

class http_protocol_handler : public sockets::tcp_server<http_protocol_handler>::protocol_handler
{
    enum class http_state
    {
        read_method,
        read_headers,
        read_body,
        reply
    };

public:
    explicit http_protocol_handler(asio::ip::tcp::socket socket);

    void respond(const std::string &content_type, const std::string &data, status_code code = status_code::ok);
    void respond(const std::string &content_type, streams::stream &data, status_code code = status_code::ok);

    void respond_default(const status_code code);

    virtual void on_http_request(http_request &request) = 0;

private:
    void on_data(std::uint8_t *data, std::size_t size) override;

    void __on_line(const std::string &line);

    auto __http_status_to_string(status_code const code) const -> const char *;

    void __parse_expected_content_length();

    void __enter_parse_body_state();
    void __enter_reply_state();

    http_state state_;
    http_request request_;
    streams::circular_buffer_stream<AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE> circular_buffer_;
    std::uint64_t expected_content_length_;
};

} // namespace aeon::webserver

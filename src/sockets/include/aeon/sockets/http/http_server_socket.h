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

#include <aeon/sockets/http/request.h>
#include <aeon/sockets/http/status_code.h>
#include <aeon/sockets/tcp_socket.h>
#include <aeon/sockets/config.h>
#include <aeon/streams/circular_buffer_stream.h>
#include <asio.hpp>
#include <string>

namespace aeon::sockets::http
{

namespace detail
{
auto validate_http_version_string(const std::string &version_string) -> bool;
auto validate_uri(const std::string &uri) -> bool;
} // namespace detail

class http_server_session;

class http_server_socket : public tcp_socket
{
    enum class http_state
    {
        server_read_method,
        server_read_headers,
        server_read_body,
        server_reply
    };

public:
    /*!
     * Server socket ctor
     */
    explicit http_server_socket(asio::ip::tcp::socket socket);

    virtual ~http_server_socket();

    http_server_socket(http_server_socket &&) = delete;
    auto operator=(http_server_socket &&) -> http_server_socket & = delete;

    http_server_socket(const http_server_socket &) = delete;
    auto operator=(const http_server_socket &) -> http_server_socket & = delete;

    void respond(const std::string &content_type, const std::string &data, const status_code code = status_code::ok);
    void respond(const std::string &content_type, streams::stream &data, const status_code code = status_code::ok);

    void respond_default(const status_code code);

    virtual void on_http_request(const request &request) = 0;

private:
    void on_data(const std::uint8_t *data, const std::size_t size) override;

    auto __on_line(const std::string &line) -> status_code;

    auto __parse_expected_content_length_and_type() -> status_code;

    auto __enter_parse_body_state() -> status_code;
    void __enter_reply_state();

    auto __handle_read_method_state(const std::string &line) -> status_code;
    auto __handle_read_headers_state(const std::string &line) -> status_code;

    void __reset_state();

    http_state state_;
    request request_;
    streams::circular_buffer_stream<AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE> circular_buffer_;
    std::uint64_t expected_content_length_;
};

} // namespace aeon::sockets::http

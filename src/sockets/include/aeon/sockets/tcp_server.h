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

#include <aeon/sockets/tcp_socket.h>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <memory>
#include <cstdint>

namespace aeon::sockets
{

template <typename socket_handler_t>
class tcp_server
{
public:
    explicit tcp_server(asio::io_context &io_context, const std::uint16_t port);
    ~tcp_server() = default;

protected:
    void start_async_accept();

    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
    asio::io_context &io_context_;
};

template <typename socket_handler_t>
inline tcp_server<socket_handler_t>::tcp_server(asio::io_context &io_context, const std::uint16_t port)
    : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    , socket_(io_context)
    , io_context_(io_context)
{
    start_async_accept();
}

template <typename socket_handler_t>
inline void tcp_server<socket_handler_t>::start_async_accept()
{
    acceptor_.async_accept(socket_, [this](std::error_code ec) {
        if (!ec)
        {
            std::make_shared<socket_handler_t>(std::move(socket_))->internal_socket_start();
        }
        start_async_accept();
    });
}

} // namespace aeon::sockets

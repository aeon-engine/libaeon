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
#include <string>

namespace aeon::sockets
{

template <typename socket_handler_t>
class tcp_client
{
public:
    explicit tcp_client(asio::io_context &io_context, const std::string &host, const std::uint16_t port);
    explicit tcp_client(asio::io_context &io_context, const std::string &host, const std::string &service);
    ~tcp_client() = default;

    auto operator-> () const -> socket_handler_t *;

protected:
    asio::ip::tcp::resolver resolver_;
    std::shared_ptr<socket_handler_t> socket_;
    asio::io_context &io_context_;
};

template <typename socket_handler_t>
inline tcp_client<socket_handler_t>::tcp_client(asio::io_context &io_context, const std::string &host,
                                                const std::uint16_t port)
    : tcp_client(io_context, host, std::to_string(port))
{
}

template <typename socket_handler_t>
inline tcp_client<socket_handler_t>::tcp_client(asio::io_context &io_context, const std::string &host,
                                                const std::string &service)
    : resolver_(io_context)
    , socket_(std::make_shared<socket_handler_t>(io_context))
    , io_context_(io_context)
{
    auto result = resolver_.resolve(host, service);
    socket_->internal_connect(result);
}

template <typename socket_handler_t>
inline auto tcp_client<socket_handler_t>::operator-> () const -> socket_handler_t *
{
    return socket_.get();
}

} // namespace aeon::sockets

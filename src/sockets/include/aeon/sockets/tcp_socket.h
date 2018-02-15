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

#include <aeon/sockets/config.h>
#include <aeon/streams/memory_stream.h>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/strand.hpp>
#include <queue>
#include <array>
#include <memory>
#include <cstdint>

namespace aeon::sockets
{

class tcp_socket : public std::enable_shared_from_this<tcp_socket>
{
    template <typename socket_handler_t>
    friend class tcp_server;

    template <typename socket_handler_t>
    friend class tcp_client;

public:
    /*!
     * Client socket ctor
     */
    explicit tcp_socket(asio::io_context &context);

    /*!
     * Server socket ctor
     */
    explicit tcp_socket(asio::ip::tcp::socket socket);

    virtual ~tcp_socket();

    virtual void on_connected();
    virtual void on_disconnected();
    virtual void on_data(const std::uint8_t *data, const std::size_t size) = 0;
    virtual void on_error(const std::error_code &ec);

    void send(streams::stream &stream);

    void send(const std::shared_ptr<streams::memory_stream> &stream);

    void disconnect();

private:
    void internal_connect(const asio::ip::basic_resolver_results<asio::ip::tcp> &endpoint);
    void internal_socket_start();
    void internal_handle_read();
    void internal_handle_write();

    asio::ip::tcp::socket socket_;
    asio::io_context::strand strand_;
    std::array<std::uint8_t, AEON_TCP_SOCKET_MAX_BUFF_LEN> data_;
    std::queue<std::shared_ptr<streams::memory_stream>> send_data_queue_;
};

} // namespace aeon::sockets

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
#include <asio.hpp>
#include <vector>
#include <queue>
#include <memory>
#include <cstdint>

namespace aeon::sockets
{

template <typename socket_handler_type>
class tcp_server
{
public:
    class protocol_handler : public std::enable_shared_from_this<protocol_handler>
    {
        friend class tcp_server;

    public:
        explicit protocol_handler(asio::ip::tcp::socket socket)
            : socket_(std::move(socket))
            , data_()
            , send_data_queue_()
        {
        }

        virtual ~protocol_handler() = default;

        virtual void on_connected()
        {
        }
        virtual void on_disconnected()
        {
        }
        virtual void on_data(std::uint8_t *data, std::size_t size) = 0;
        virtual void on_error(asio::error_code ec)
        {
        }

        void send(streams::stream &stream)
        {
            const auto memorystream = std::make_shared<streams::memory_stream>(stream.read_to_vector());
            send(memorystream);
        }

        void send(const std::shared_ptr<streams::memory_stream> &stream)
        {
            send_data_queue_.push(stream);

            if (send_data_queue_.size() == 1)
                tcp_server_handle_write();
        }

        void disconnect()
        {
            if (!socket_.is_open())
                return;

            socket_.shutdown(asio::ip::tcp::socket::shutdown_both);
            socket_.close();
            on_disconnected();
        }

        void tcp_server_socket_start()
        {
            tcp_server_handle_read();
            on_connected();
        }

    protected:
        auto &io_service()
        {
            return socket_.get_io_service();
        }

    private:
        void tcp_server_handle_read()
        {
            auto self(protocol_handler::shared_from_this());

            socket_.async_read_some(asio::buffer(data_, AEON_TCP_SOCKET_MAX_BUFF_LEN),
                                    [self](asio::error_code ec, std::size_t length) {
                                        if (ec && ec != asio::error::eof)
                                            self->on_error(ec);

                                        if (length > 0)
                                        {
                                            self->on_data(self->data_.data(), length);

                                            if (!ec)
                                                self->tcp_server_handle_read();
                                        }
                                        else
                                        {
                                            self->socket_.close();
                                            self->on_disconnected();
                                        }
                                    });
        }

        void tcp_server_handle_write()
        {
            if (send_data_queue_.empty())
                return;

            const auto buffer = send_data_queue_.front();
            auto self(protocol_handler::shared_from_this());

            asio::async_write(socket_, asio::buffer(buffer->data(), buffer->size()),
                              [self, buffer](asio::error_code ec, std::size_t /*length*/) {
                                  self->send_data_queue_.pop();

                                  if (!ec)
                                      self->tcp_server_handle_write();
                              });
        }

        asio::ip::tcp::socket socket_;
        std::array<std::uint8_t, AEON_TCP_SOCKET_MAX_BUFF_LEN> data_;
        std::queue<std::shared_ptr<streams::memory_stream>> send_data_queue_;
    };

    explicit tcp_server(asio::io_service &io_service, std::uint16_t port)
        : acceptor_(io_service, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
        , socket_(io_service)
        , io_service_(io_service)
    {
        start_async_accept();
    }

protected:
    void start_async_accept()
    {
        acceptor_.async_accept(socket_, [this](asio::error_code ec) {
            if (!ec)
            {
                std::make_shared<socket_handler_type>(std::move(socket_))->tcp_server_socket_start();
            }
            start_async_accept();
        });
    }

    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
    asio::io_service &io_service_;
};

} // namespace aeon::sockets

// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/stream_reader.h>
#include <asio/write.hpp>
#include <asio/connect.hpp>
#include <asio/bind_executor.hpp>

namespace aeon::sockets
{

tcp_socket::tcp_socket(asio::io_context &context)
    : context_{context}
    , socket_{context}
    , data_{}
    , send_data_queue_{}
{
}

tcp_socket::tcp_socket(asio::ip::tcp::socket socket)
    : context_{static_cast<asio::io_context &>(socket.get_executor().context())}
    , socket_{std::move(socket)}
    , data_{}
    , send_data_queue_{}
{
}

tcp_socket::~tcp_socket() = default;

void tcp_socket::on_connected()
{
}

void tcp_socket::on_disconnected()
{
}

void tcp_socket::on_error([[maybe_unused]] const std::error_code &ec)
{
}

void tcp_socket::send(std::vector<std::byte> data)
{
    if (std::empty(data))
        return;

    auto self(shared_from_this());

    asio::post(context_,
               [self, data = std::move(data)]() mutable
               {
                   const auto write_in_progress = !std::empty(self->send_data_queue_);

                   self->send_data_queue_.push(std::move(data));
                   if (!write_in_progress)
                       self->internal_handle_write();
               });
}

void tcp_socket::disconnect()
{
    auto self(shared_from_this());

    asio::post(context_,
               [self]()
               {
                   if (!self->socket_.is_open())
                       return;

                   self->socket_.shutdown(asio::ip::tcp::socket::shutdown_both);
                   self->socket_.close();
                   self->on_disconnected();
               });
}

void tcp_socket::internal_connect(const asio::ip::basic_resolver_results<asio::ip::tcp> &endpoint)
{
    auto self(shared_from_this());

    asio::async_connect(socket_, endpoint,
                        asio::bind_executor(context_,
                                            [self](const std::error_code ec, auto)
                                            {
                                                if (ec && ec != asio::error::eof)
                                                    self->on_error(ec);

                                                self->internal_handle_read();
                                                self->on_connected();
                                            }));
}

void tcp_socket::internal_socket_start()
{
    internal_handle_read();
    on_connected();
}

void tcp_socket::internal_handle_read()
{
    auto self(shared_from_this());

    socket_.async_read_some(asio::buffer(data_, tcp_socket_max_buff_len),
                            asio::bind_executor(context_,
                                                [self](const std::error_code ec, const std::size_t length)
                                                {
                                                    if (ec && ec != asio::error::eof)
                                                        self->on_error(ec);

                                                    if (length > 0)
                                                    {
                                                        self->on_data({self->data_.data(), length});

                                                        if (!ec && self->socket_.is_open())
                                                            self->internal_handle_read();
                                                    }
                                                    else
                                                    {
                                                        self->socket_.close();
                                                        self->on_disconnected();
                                                    }
                                                }));
}

void tcp_socket::internal_handle_write()
{
    auto self(shared_from_this());

    const auto &data = send_data_queue_.front();

    asio::async_write(self->socket_, asio::buffer(std::data(*data), std::size(*data)),
                      [self](const std::error_code ec, const std::size_t /*length*/)
                      {
                          if (ec && ec != asio::error::eof)
                          {
                              self->on_error(ec);
                              self->on_disconnected();
                              self->socket_.close();
                              return;
                          }

                          self->send_data_queue_.pop();

                          if (!std::empty(self->send_data_queue_))
                              self->internal_handle_write();
                      });
}

} // namespace aeon::sockets

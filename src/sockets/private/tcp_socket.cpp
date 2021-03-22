// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/stream_reader.h>
#include <asio/write.hpp>
#include <asio/connect.hpp>
#include <asio/bind_executor.hpp>

namespace aeon::sockets
{

tcp_socket::tcp_socket(asio::io_context &context)
    : socket_{context}
    , strand_{context}
    , data_{}
    , send_data_queue_{}
{
}

tcp_socket::tcp_socket(asio::ip::tcp::socket socket)
    : socket_{std::move(socket)}
    , strand_{static_cast<asio::io_context &>(socket.get_executor().context())}
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

    auto send_impl = [self, data = std::move(data)]() mutable {
        self->send_data_queue_.push(std::move(data));

        if (self->send_data_queue_.size() == 1)
            self->internal_handle_write();
    };

    if (strand_.running_in_this_thread())
        send_impl();
    else
        asio::post(strand_, send_impl);
}

void tcp_socket::disconnect()
{
    auto self(shared_from_this());

    auto disconnect_impl = [self]() {
        if (!self->socket_.is_open())
            return;

        self->socket_.shutdown(asio::ip::tcp::socket::shutdown_both);
        self->socket_.close();
        self->on_disconnected();
    };

    if (strand_.running_in_this_thread())
        disconnect_impl();
    else
        asio::post(strand_, disconnect_impl);
}

void tcp_socket::internal_connect(const asio::ip::basic_resolver_results<asio::ip::tcp> &endpoint)
{
    auto self(shared_from_this());

    asio::async_connect(socket_, endpoint, asio::bind_executor(strand_, [self](const std::error_code ec, auto) {
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
                            asio::bind_executor(strand_, [self](const std::error_code ec, const std::size_t length) {
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

    asio::post(strand_, [self]() {
        if (self->send_data_queue_.empty())
            return;

        const auto &buffer = self->send_data_queue_.front();

        asio::async_write(
            self->socket_, asio::buffer(reinterpret_cast<const std::uint8_t *>(std::data(*buffer)), std::size(*buffer)),
            asio::bind_executor(self->strand_, [self](const std::error_code ec, const std::size_t /*length*/) {
                if (ec && ec != asio::error::eof)
                    self->on_error(ec);

                self->send_data_queue_.pop();

                if (!ec && self->socket_.is_open())
                    self->internal_handle_write();
            }));
    });
}

} // namespace aeon::sockets

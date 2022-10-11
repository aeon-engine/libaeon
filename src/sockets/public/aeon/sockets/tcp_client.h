// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/sockets/tcp_socket.h>
#include <aeon/common/string.h>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <memory>
#include <cstdint>

namespace aeon::sockets
{

template <typename socket_handler_t>
class tcp_client
{
public:
    explicit tcp_client(asio::io_context &io_context);
    explicit tcp_client(asio::io_context &io_context, const common::string &host, const std::uint16_t port);
    explicit tcp_client(asio::io_context &io_context, const common::string &host, const common::string &service);
    ~tcp_client() = default;

    tcp_client(tcp_client &&) = delete;
    auto operator=(tcp_client &&) -> tcp_client & = delete;

    tcp_client(const tcp_client &) = delete;
    auto operator=(const tcp_client &) -> tcp_client & = delete;

    void connect(const common::string &host, const std::uint16_t port);
    void connect(const common::string &host, const common::string &service);

    auto operator->() const -> socket_handler_t *;

protected:
    asio::ip::tcp::resolver resolver_;
    std::shared_ptr<socket_handler_t> socket_;
    asio::io_context &io_context_;
};

template <typename socket_handler_t>
inline tcp_client<socket_handler_t>::tcp_client(asio::io_context &io_context)
    : resolver_{io_context}
    , socket_{std::make_shared<socket_handler_t>(io_context)}
    , io_context_{io_context}
{
}

template <typename socket_handler_t>
inline tcp_client<socket_handler_t>::tcp_client(asio::io_context &io_context, const common::string &host,
                                                const std::uint16_t port)
    : tcp_client{io_context}
{
    connect(host, port);
}

template <typename socket_handler_t>
inline tcp_client<socket_handler_t>::tcp_client(asio::io_context &io_context, const common::string &host,
                                                const common::string &service)
    : tcp_client{io_context}
{
    connect(host, service);
}

template <typename socket_handler_t>
inline void tcp_client<socket_handler_t>::connect(const common::string &host, const std::uint16_t port)
{
    connect(host, std::to_string(port));
}

template <typename socket_handler_t>
inline void tcp_client<socket_handler_t>::connect(const common::string &host, const common::string &service)
{
    auto result = resolver_.resolve(host.as_std_string_view(), service.as_std_string_view());
    socket_->internal_connect(result);
}

template <typename socket_handler_t>
inline auto tcp_client<socket_handler_t>::operator->() const -> socket_handler_t *
{
    return socket_.get();
}

} // namespace aeon::sockets

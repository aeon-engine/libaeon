// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/sockets/tcp_socket.h>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <memory>
#include <type_traits>
#include <cstdint>

namespace aeon::sockets
{

struct default_session
{
};

/*!
 * TCP Server class.
 *
 * socket_handler_t must be given some implementation of tcp_socket. A new
 * socket is created for each incoming connection.
 *
 * session_handler_t is an optional template argument that can be given a
 * implementation for a session handler. If session_handler_t is set,
 * each socket that is instantiated will also be given a session_handler_t&
 * in the constructor as second argument.
 */
template <typename socket_t, typename session_t = default_session>
class tcp_server
{
public:
    explicit tcp_server(asio::io_context &io_context, const std::uint16_t port);
    explicit tcp_server(asio::io_context &io_context, std::unique_ptr<session_t> session_handler,
                        const std::uint16_t port);
    ~tcp_server() = default;

    auto get_session() const -> session_t &;

protected:
    void start_async_accept();

    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
    asio::io_context &io_context_;
    std::unique_ptr<session_t> session_handler_;
};

template <typename socket_t, typename session_t>
inline tcp_server<socket_t, session_t>::tcp_server(asio::io_context &io_context, const std::uint16_t port)
    : tcp_server(io_context, std::make_unique<session_t>(), port)
{
    start_async_accept();
}

template <typename socket_t, typename session_t>
inline tcp_server<socket_t, session_t>::tcp_server(asio::io_context &io_context,
                                                   std::unique_ptr<session_t> session_handler, const std::uint16_t port)
    : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
    , socket_(io_context)
    , io_context_(io_context)
    , session_handler_(std::move(session_handler))
{
    start_async_accept();
}

template <typename socket_t, typename session_t>
inline void tcp_server<socket_t, session_t>::start_async_accept()
{
    acceptor_.async_accept(socket_, [this](std::error_code ec) {
        if (!ec)
        {
            if constexpr (std::is_same<session_t, default_session>::value)
            {
                std::make_shared<socket_t>(std::move(socket_))->internal_socket_start();
            }
            else
            {
                std::make_shared<socket_t>(std::move(socket_), *session_handler_)->internal_socket_start();
            }
        }
        start_async_accept();
    });
}

template <typename socket_t, typename session_t>
inline auto tcp_server<socket_t, session_t>::get_session() const -> session_t &
{
    return *session_handler_;
}

} // namespace aeon::sockets

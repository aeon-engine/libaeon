// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/sockets/config.h>
#include <aeon/common/unique_obj.h>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <queue>
#include <array>
#include <memory>
#include <span>

namespace aeon::sockets
{

class tcp_socket : public std::enable_shared_from_this<tcp_socket>
{
    template <typename socket_handler_t, typename session_handler_t>
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

    tcp_socket(tcp_socket &&) = delete;
    auto operator=(tcp_socket &&) -> tcp_socket & = delete;

    tcp_socket(const tcp_socket &) = delete;
    auto operator=(const tcp_socket &) -> tcp_socket & = delete;

    virtual void on_connected();
    virtual void on_disconnected();
    virtual void on_data(const std::span<const std::byte> &data) = 0;
    virtual void on_error(const std::error_code &ec);

    void send(std::vector<std::byte> data);

    void disconnect();

private:
    void internal_connect(const asio::ip::basic_resolver_results<asio::ip::tcp> &endpoint);
    void internal_socket_start();
    void internal_handle_read();
    void internal_handle_write();

    asio::io_context &context_;
    asio::ip::tcp::socket socket_;
    std::array<std::byte, tcp_socket_max_buff_len> data_;
    std::queue<common::unique_obj<std::vector<std::byte>>> send_data_queue_;
};

} // namespace aeon::sockets

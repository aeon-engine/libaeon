// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/config.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/idynamic_stream.h>
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
    virtual void on_data(const std::uint8_t *data, const std::size_t size) = 0;
    virtual void on_error(const std::error_code &ec);

    void send(streams::idynamic_stream &stream);

    void send(const std::shared_ptr<streams::memory_device<std::vector<std::uint8_t>>> &stream);

    void disconnect();

private:
    void internal_connect(const asio::ip::basic_resolver_results<asio::ip::tcp> &endpoint);
    void internal_socket_start();
    void internal_handle_read();
    void internal_handle_write();

    asio::ip::tcp::socket socket_;
    asio::io_context::strand strand_;
    std::array<std::uint8_t, AEON_TCP_SOCKET_MAX_BUFF_LEN> data_;
    std::queue<std::shared_ptr<streams::memory_device<std::vector<std::uint8_t>>>> send_data_queue_;
};

} // namespace aeon::sockets

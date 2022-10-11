// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/streams/stream.h>

namespace aeon::sockets
{

/*!
 * Protocol implementation for a line protocol.
 * A line protocol can be any generic text-based TCP protocol that uses
 * line endings to distinguish between different packets.
 *
 * Examples of line protocols are: Telnet, HTTP and IRC.
 */
class line_protocol_socket : public tcp_socket
{
public:
    /*!
     * Client socket ctor
     */
    explicit line_protocol_socket(asio::io_context &service);

    /*!
     * Server socket ctor
     */
    explicit line_protocol_socket(asio::ip::tcp::socket socket);

    line_protocol_socket(line_protocol_socket &&) = delete;
    auto operator=(line_protocol_socket &&) -> line_protocol_socket & = delete;

    line_protocol_socket(const line_protocol_socket &) = delete;
    auto operator=(const line_protocol_socket &) -> line_protocol_socket & = delete;

    ~line_protocol_socket() override;

protected:
    virtual void on_line(const common::string &line) = 0;

private:
    void on_data(const std::span<const std::byte> &data) override;

    streams::aggregate_device<streams::circular_buffer_filter, streams::memory_device<std::vector<char>>>
        circular_buffer_;
};

} // namespace aeon::sockets

// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/tcp_socket.h>
#include <aeon/sockets/config.h>
#include <aeon/streams/circular_buffer_stream.h>

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

    virtual ~line_protocol_socket();

    virtual void on_line(const std::string &line) = 0;

private:
    void on_data(const std::uint8_t *data, const std::size_t size) override;

    streams::circular_buffer_stream<AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE> circular_buffer_;
};

} // namespace aeon::sockets

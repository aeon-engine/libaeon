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
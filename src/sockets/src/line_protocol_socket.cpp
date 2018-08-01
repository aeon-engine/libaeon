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

#include <aeon/sockets/line_protocol_socket.h>
#include <aeon/streams/stream_reader.h>

namespace aeon::sockets
{

line_protocol_socket::line_protocol_socket(asio::io_context &service)
    : tcp_socket(service)
{
}

line_protocol_socket::line_protocol_socket(asio::ip::tcp::socket socket)
    : tcp_socket(std::move(socket))
{
}

line_protocol_socket::~line_protocol_socket() = default;

void line_protocol_socket::on_data(const std::uint8_t *data, const std::size_t size)
{
    circular_buffer_.write(data, size);
    streams::stream_reader reader(circular_buffer_);

    while (!circular_buffer_.empty())
    {
        on_line(reader.read_line());
    }
}

} // namespace aeon::sockets

// Copyright (c) 2012-2019 Robin Degen

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

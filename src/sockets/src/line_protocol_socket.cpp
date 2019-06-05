// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/sockets/line_protocol_socket.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/sockets/config.h>

namespace aeon::sockets
{

line_protocol_socket::line_protocol_socket(asio::io_context &service)
    : tcp_socket(service)
    , circular_buffer_{streams::circular_buffer_filter{},
                       streams::memory_device<std::vector<char>>{AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE}}
{
}

line_protocol_socket::line_protocol_socket(asio::ip::tcp::socket socket)
    : tcp_socket(std::move(socket))
    , circular_buffer_{streams::circular_buffer_filter{},
                       streams::memory_device<std::vector<char>>{AEON_TCP_SOCKET_CIRCULAR_BUFFER_SIZE}}
{
}

line_protocol_socket::~line_protocol_socket() = default;

void line_protocol_socket::on_data(const std::uint8_t *data, const std::size_t size)
{
    circular_buffer_.write(reinterpret_cast<const char *>(data), size);
    streams::stream_reader reader(circular_buffer_);

    while (circular_buffer_.size() != 0)
    {
        on_line(reader.read_line());
    }
}

} // namespace aeon::sockets

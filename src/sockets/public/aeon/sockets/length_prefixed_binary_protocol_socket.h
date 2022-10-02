// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <concepts>

namespace aeon::sockets
{

template <std::unsigned_integral length_t>
class length_prefixed_binary_frame : public streams::stream_writer<streams::memory_device<std::vector<std::byte>>>
{
public:
    explicit length_prefixed_binary_frame(const std::size_t reserve_size = 0)
        : stream_writer<streams::memory_device<std::vector<std::byte>>>{device_}
    {
        if (reserve_size > 0)
            device_.reserve(reserve_size + sizeof(length_t));

        // Write placeholder length at the start to avoid reallocation later
        *this << length_t();
    }

    ~length_prefixed_binary_frame() = default;

    length_prefixed_binary_frame(length_prefixed_binary_frame &&other) noexcept
        : stream_writer<streams::memory_device<std::vector<std::byte>>>{other.device_}
    {
        device_ = std::move(other.device_);
        stream_writer<streams::memory_device<std::vector<std::byte>>>::device(device_);
    }

    auto operator=(length_prefixed_binary_frame &&other) noexcept -> length_prefixed_binary_frame &
    {
        if (this == &other) [[unlikely]]
            return *this;

        device_ = std::move(other.device_);
        stream_writer<streams::memory_device<std::vector<std::byte>>>::device(device_);

        return *this;
    }

    length_prefixed_binary_frame(const length_prefixed_binary_frame &) = delete;
    auto operator=(const length_prefixed_binary_frame &) -> length_prefixed_binary_frame & = delete;

    [[nodiscard]] auto release() noexcept
    {
        device_.seekp(0, streams::seek_direction::begin);
        *this << length_t(device_.size() - sizeof(length_t));

        return std::move(device_.release());
    }

private:
    streams::memory_device<std::vector<std::byte>> device_;
};

/*!
 * Protocol implementation for a binary protocol that has its frames prefixed by a length
 * This is very common for binary protocol implementations over TCP
 */
template <std::unsigned_integral length_t>
class length_prefixed_binary_protocol_socket : public tcp_socket
{
public:
    /*!
     * Client socket ctor
     */
    explicit length_prefixed_binary_protocol_socket(asio::io_context &service);

    /*!
     * Server socket ctor
     */
    explicit length_prefixed_binary_protocol_socket(asio::ip::tcp::socket socket);

    ~length_prefixed_binary_protocol_socket() override = default;

    length_prefixed_binary_protocol_socket(length_prefixed_binary_protocol_socket &&) = delete;
    auto operator=(length_prefixed_binary_protocol_socket &&) -> length_prefixed_binary_protocol_socket & = delete;

    length_prefixed_binary_protocol_socket(const length_prefixed_binary_protocol_socket &) = delete;
    auto operator=(const length_prefixed_binary_protocol_socket &) -> length_prefixed_binary_protocol_socket & = delete;

    virtual void on_frame(const streams::memory_view_device<std::vector<std::byte>> &frame) = 0;

    void send_frame(length_prefixed_binary_frame<length_t> frame);

private:
    void on_data(const std::span<const std::byte> &data) override;

    streams::aggregate_device<streams::circular_buffer_filter, streams::memory_device<std::vector<std::byte>>>
        circular_buffer_;

    length_t expected_length_;
    std::vector<std::byte> frame_buffer_;
};

template <std::unsigned_integral length_t>
inline length_prefixed_binary_protocol_socket<length_t>::length_prefixed_binary_protocol_socket(
    asio::io_context &service)
    : tcp_socket(service)
    , circular_buffer_{streams::circular_buffer_filter{},
                       streams::memory_device<std::vector<std::byte>>{tcp_socket_circular_buffer_size}}
    , expected_length_{0}
{
}

template <std::unsigned_integral length_t>
inline length_prefixed_binary_protocol_socket<length_t>::length_prefixed_binary_protocol_socket(
    asio::ip::tcp::socket socket)
    : tcp_socket(std::move(socket))
    , circular_buffer_{streams::circular_buffer_filter{},
                       streams::memory_device<std::vector<std::byte>>{tcp_socket_circular_buffer_size}}
    , expected_length_{0}
{
}

template <std::unsigned_integral length_t>
void length_prefixed_binary_protocol_socket<length_t>::send_frame(length_prefixed_binary_frame<length_t> frame)
{
    send(frame.release());
}

template <std::unsigned_integral length_t>
inline void length_prefixed_binary_protocol_socket<length_t>::on_data(const std::span<const std::byte> &data)
{
    circular_buffer_.write(std::data(data), std::size(data));
    streams::stream_reader reader{circular_buffer_};

    while (true)
    {
        if (expected_length_ == 0 && circular_buffer_.size() >= sizeof(length_t))
            reader >> expected_length_;

        if (expected_length_ == 0)
            break;

        if (circular_buffer_.size() < expected_length_)
            break;

        reader.read_to_vector<std::byte>(frame_buffer_, static_cast<std::streamoff>(expected_length_));
        streams::memory_view_device device{frame_buffer_};
        on_frame(device);
        frame_buffer_.clear();

        expected_length_ = 0;
    }
}

} // namespace aeon::sockets

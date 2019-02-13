// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/length_prefix_string.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/exception.h>
#include <aeon/common/signed_sizeof.h>
#include <aeon/common/assert.h>
#include <string>
#include <vector>
#include <cstring>

namespace aeon::streams
{

class dynamic_stream_reader
{
    static constexpr std::streamsize read_block_size = 64;

public:
    explicit dynamic_stream_reader(idynamic_stream &device) noexcept;

    dynamic_stream_reader(dynamic_stream_reader &&) noexcept = default;
    auto operator=(dynamic_stream_reader &&) noexcept -> dynamic_stream_reader & = default;

    dynamic_stream_reader(const dynamic_stream_reader &) noexcept = default;
    auto operator=(const dynamic_stream_reader &) noexcept -> dynamic_stream_reader & = default;

    ~dynamic_stream_reader() = default;

    auto device() const noexcept -> idynamic_stream &;

    void read_line(std::string &line) const;
    auto read_line() const -> std::string;

    template <typename T>
    void read_to_vector(std::vector<T> &vec) const;
    auto read_to_vector() const -> std::vector<char>;

    void read_to_string(std::string &str) const;
    auto read_to_string() const -> std::string;

private:
    idynamic_stream *device_;
};

inline dynamic_stream_reader::dynamic_stream_reader(idynamic_stream &device) noexcept
    : device_{&device}
{
    aeon_assert(device_->is_input(), "Stream reader requires an input device.");
}

inline auto dynamic_stream_reader::device() const noexcept -> idynamic_stream &
{
    return *device_;
}

inline void dynamic_stream_reader::read_line(std::string &line) const
{
    aeon_assert(device_->is_input_seekable(), "read_line requires an input seekable device.");

    std::streamsize peek_size = 0;
    char peek_data[read_block_size] = {};
    while ((peek_size = device_->read(peek_data, read_block_size)) > 0)
    {
        // TODO: Replace strchr with something more modern.
        const char *line_end = std::strchr(peek_data, '\n');

        if (!line_end)
        {
            line.append(peek_data, peek_size);
        }
        else
        {
            const auto temp_size = line_end - peek_data;
            line.append(peek_data, temp_size);

            const auto jump_back = (static_cast<std::ptrdiff_t>(peek_size) - temp_size) - 1;

            if (jump_back == 0)
                break;

            if (!device_->seekg(-jump_back, seek_direction::current))
                throw stream_exception{};

            break;
        }
    }

    if (!line.empty())
    {
        if (line[line.size() - 1] == '\r')
            line.resize(line.size() - 1);
    }
}

inline auto dynamic_stream_reader::read_line() const -> std::string
{
    std::string line;
    read_line(line);
    return line;
}

template <typename T>
inline void dynamic_stream_reader::read_to_vector(std::vector<T> &vec) const
{
    static_assert(sizeof(T) == 1, "Given template argument size must be 1 byte.");
    aeon_assert(device_->has_size(), "read_to_vector requires a device with known size.");
    aeon_assert(std::empty(vec), "Expected given vector to be empty.");

    const auto size = device_->size();
    vec.resize(size);

    if (device_->read(reinterpret_cast<char *>(std::data(vec)), static_cast<std::streamsize>(size)) != size)
        throw stream_exception{};
}

inline auto dynamic_stream_reader::read_to_vector() const -> std::vector<char>
{
    std::vector<char> vec;
    read_to_vector(vec);
    return vec;
}

inline void dynamic_stream_reader::read_to_string(std::string &str) const
{
    aeon_assert(std::empty(str), "Expected given string to be empty.");

    const auto vec = read_to_vector();
    str.insert(std::begin(str), std::begin(vec), std::end(vec));
}

inline auto dynamic_stream_reader::read_to_string() const -> std::string
{
    std::string str;
    read_to_string(str);
    return str;
}

template <typename T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto &operator>>(dynamic_stream_reader &reader, T &val)
{
    if (reader.device().read(reinterpret_cast<char *>(&val), aeon_signed_sizeof(T)) != aeon_signed_sizeof(T))
        throw stream_exception{};

    return reader;
}

inline auto &operator>>(dynamic_stream_reader &reader, std::string &val)
{
    reader.read_line(val);
    return reader;
}

template <typename T>
inline auto &operator>>(dynamic_stream_reader &reader, length_prefix_string<T> &&value)
{
    T length = 0;
    reader >> length;
    value.string.resize(length);

    if (reader.device().read(std::data(value.string), length) != static_cast<std::streamoff>(length))
        throw stream_exception{};

    return reader;
}

} // namespace aeon::streams

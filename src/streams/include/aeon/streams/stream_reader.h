// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream.h>
#include <aeon/streams/exception.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/common/signed_sizeof.h>
#include <aeon/common/assert.h>
#include <string>
#include <vector>

namespace aeon::streams
{

template <typename device_t>
class stream_reader
{
    static constexpr std::streamsize read_block_size = 64;

public:
    explicit stream_reader(device_t &device) noexcept;

    stream_reader(stream_reader &&) noexcept = default;
    auto operator=(stream_reader &&) noexcept -> stream_reader & = default;

    stream_reader(const stream_reader &) noexcept = default;
    auto operator=(const stream_reader &) noexcept -> stream_reader & = default;

    ~stream_reader() = default;

    [[nodiscard]] auto device() const noexcept -> device_t &;

    void read_line(std::string &line) const;
    [[nodiscard]] auto read_line() const -> std::string;

    template <typename T>
    void read_to_vector(std::vector<T> &vec) const;

    template <typename T>
    [[nodiscard]] auto read_to_vector() const -> std::vector<T>;

    template <typename T>
    void read_to_vector(std::vector<T> &vec, const std::streamoff size) const;

    template <typename T>
    [[nodiscard]] auto read_to_vector(const std::streamoff size) const -> std::vector<T>;

    void read_to_string(std::string &str) const;
    [[nodiscard]] auto read_to_string() const -> std::string;

private:
    device_t *device_;
};

template <typename device_t>
class dynamic_stream;

template <typename device_t>
stream_reader(dynamic_stream<device_t> &)->stream_reader<idynamic_stream>;

template <typename device_t>
inline stream_reader<device_t>::stream_reader(device_t &device) noexcept
    : device_{&device}
{
    if constexpr (std::is_same_v<device_t, idynamic_stream>)
    {
        aeon_assert(device_->is_input(), "Stream reader requires an input device.");
    }
    else
    {
        static_assert(is_device_v<device_t>, "Stream writer requires a device.");
        static_assert(is_input_v<device_t>, "Stream reader requires an input device.");
    }
}

template <typename device_t>
[[nodiscard]] inline auto stream_reader<device_t>::device() const noexcept -> device_t &
{
    return *device_;
}

template <typename device_t>
inline void stream_reader<device_t>::read_line(std::string &line) const
{
    if constexpr (std::is_same_v<device_t, idynamic_stream>)
        aeon_assert(device_->is_input_seekable(), "read_line requires an input seekable device.");
    else
        static_assert(is_input_seekable_v<device_t>, "read_line requires an input seekable device.");

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

template <typename device_t>
[[nodiscard]] inline auto stream_reader<device_t>::read_line() const -> std::string
{
    std::string line;
    read_line(line);
    return line;
}

template <typename device_t>
template <typename T>
inline void stream_reader<device_t>::read_to_vector(std::vector<T> &vec) const
{
    if constexpr (std::is_same_v<device_t, idynamic_stream>)
        aeon_assert(device_->has_size(), "read_to_vector requires a device with known size.");
    else
        static_assert(has_size_v<device_t>, "read_to_vector requires a device with known size.");

    read_to_vector(vec, device_->size());
}

template <typename device_t>
template <typename T>
[[nodiscard]] inline auto stream_reader<device_t>::read_to_vector() const -> std::vector<T>
{
    std::vector<T> vec;
    read_to_vector(vec);
    return vec;
}

template <typename device_t>
template <typename T>
inline void stream_reader<device_t>::read_to_vector(std::vector<T> &vec, const std::streamoff size) const
{
    static_assert(sizeof(T) == 1, "Given template argument size must be 1 byte.");
    aeon_assert(std::empty(vec), "Expected given vector to be empty.");

    vec.resize(size);

    if (device_->read(reinterpret_cast<char *>(std::data(vec)), size) != size)
        throw stream_exception{};
}

template <typename device_t>
template <typename T>
[[nodiscard]] inline auto stream_reader<device_t>::read_to_vector(const std::streamoff size) const -> std::vector<T>
{
    std::vector<T> vec;
    read_to_vector(vec, size);
    return vec;
}

template <typename device_t>
inline void stream_reader<device_t>::read_to_string(std::string &str) const
{
    aeon_assert(std::empty(str), "Expected given string to be empty.");

    const auto vec = read_to_vector<char>();
    str.insert(std::begin(str), std::begin(vec), std::end(vec));
}

template <typename device_t>
[[nodiscard]] inline auto stream_reader<device_t>::read_to_string() const -> std::string
{
    std::string str;
    read_to_string(str);
    return str;
}

template <typename device_t, typename T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
inline auto &operator>>(stream_reader<device_t> &reader, T &val)
{
    if (reader.device().read(reinterpret_cast<char *>(&val), aeon_signed_sizeof(T)) != aeon_signed_sizeof(T))
        throw stream_exception{};

    return reader;
}

template <typename device_t>
inline auto &operator>>(stream_reader<device_t> &reader, std::string &val)
{
    reader.read_line(val);
    return reader;
}

} // namespace aeon::streams

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/filters/filter.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/streams/tags.h>
#include <algorithm>
#include <array>

namespace aeon::streams
{

template <int buffer_size>
class sink_buffer_filter : public filter
{
public:
    struct category : output_tag, output_seekable_tag, flushable_tag
    {
    };

    sink_buffer_filter() noexcept
        : offset_{0}
    {
    }

    sink_buffer_filter(sink_buffer_filter &&) noexcept = default;
    auto operator=(sink_buffer_filter &&) noexcept -> sink_buffer_filter & = default;

    sink_buffer_filter(const sink_buffer_filter &) noexcept = default;
    auto operator=(const sink_buffer_filter &) noexcept -> sink_buffer_filter & = default;

    ~sink_buffer_filter() = default;

    template <typename sink_t>
    auto write(sink_t &sink, const std::byte *data, const std::streamsize size) -> std::streamsize
    {
        auto size_remaining = size;
        auto data_offset = data;

        do
        {
            const auto size_to_write = std::min(size_remaining, static_cast<std::streamsize>(buffer_size - offset_));
            std::copy_n(data_offset, size_to_write, std::data(buffer_) + offset_);

            data_offset += size_to_write;
            size_remaining -= size_to_write;
            offset_ += size_to_write;

            if (offset_ >= buffer_size)
                internal_flush(sink);
        } while (size_remaining > 0);

        return size;
    }

    template <typename sink_t>
    auto seekp(sink_t &sink, const std::streamoff offset, const seek_direction direction) -> bool
    {
        static_assert(is_output_seekable_v<sink_t>, "Sink does not support seekp.");
        flush(sink);
        return sink.seek(offset, direction);
    }

    template <typename sink_t>
    [[nodiscard]] auto tellp(sink_t &sink) const -> std::streamoff
    {
        static_assert(is_output_seekable_v<sink_t>, "Sink does not support tellp.");
        flush(sink);
        return sink.tellp();
    }

    template <typename sink_t>
    void flush(sink_t &sink)
    {
        if (offset_ == 0)
            return;

        internal_flush(sink);
    }

private:
    template <typename sink_t>
    void internal_flush(sink_t &sink)
    {
        sink.write(std::data(buffer_), offset_);
        offset_ = 0;
    }

    std::array<std::byte, buffer_size> buffer_;
    std::streamoff offset_;
};

} // namespace aeon::streams

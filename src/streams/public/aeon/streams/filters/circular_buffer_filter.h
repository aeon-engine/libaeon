// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/filters/filter.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/stream_traits.h>
#include <aeon/streams/tags.h>
#include <aeon/streams/exception.h>

namespace aeon::streams
{

class circular_buffer_filter_exception : public stream_exception
{
};

class circular_buffer_filter : public filter
{
public:
    struct category : input_tag, input_seekable_tag, output_tag, output_seekable_tag, has_eof_tag, has_size_tag
    {
    };

    circular_buffer_filter() noexcept
        : tail_{0}
        , head_{0}
        , size_{0}
    {
    }

    circular_buffer_filter(circular_buffer_filter &&) noexcept = default;
    auto operator=(circular_buffer_filter &&) noexcept -> circular_buffer_filter & = default;

    circular_buffer_filter(const circular_buffer_filter &) noexcept = default;
    auto operator=(const circular_buffer_filter &) noexcept -> circular_buffer_filter & = default;

    ~circular_buffer_filter() = default;

    template <typename sink_t>
    auto write(sink_t &sink, const char *data, const std::streamsize size) -> std::streamsize
    {
        static_assert(has_size_v<sink_t>, "Circular buffer requires stream with size.");

        // Can we fit this in at all?
        if (is_out_of_bounds(sink, size))
            return 0;

        // We are about to overwrite data that was not yet read. Abort.
        if (!fits_in_buffer(sink, size))
            throw circular_buffer_filter_exception{};

        auto bytes_to_write = size;
        std::streamoff read_offset = 0;

        // If this doesn't fit, we loop around
        if (is_out_of_bounds(sink, size + head_))
        {
            auto bytes_until_end = sink.size() - head_;
            bytes_to_write -= bytes_until_end;
            read_offset = bytes_until_end;

            sink.seekp(head_, seek_direction::begin);
            sink.write(data, bytes_until_end);

            head_ = 0;
        }

        // Do we still have anything to write?
        if (bytes_to_write > 0)
        {
            sink.seekp(head_, seek_direction::begin);
            sink.write(data + read_offset, bytes_to_write);

            head_ += bytes_to_write;
        }

        // Finally check if we're at the end of the buffer
        if (head_ >= sink.size())
            head_ = 0;

        // Update the size of the buffer
        size_ += size;

        return size;
    }

    template <typename source_t>
    auto read(source_t &source, char *data, const std::streamsize size) -> std::streamsize
    {
        static_assert(has_size_v<source_t>, "Circular buffer requires stream with size.");

        auto actual_size = size;

        // Can we read this size at all?
        if (is_out_of_bounds(source, actual_size))
            return 0;

        // Do we have this many bytes in the buffer?
        if (actual_size > size_)
            actual_size = size_;

        auto bytes_to_read = actual_size;
        std::streamoff write_offset = 0;

        // If we can't read everything at once, read the first part
        if (is_out_of_bounds(source, actual_size + tail_))
        {
            auto bytes_until_end = source.size() - tail_;

            source.seekg(tail_, seek_direction::begin);
            source.read(data, bytes_until_end);

            bytes_to_read -= bytes_until_end;
            write_offset = bytes_until_end;
            tail_ = 0;
        }

        // Do we have anything left to read?
        if (bytes_to_read > 0)
        {
            source.seekg(tail_, seek_direction::begin);
            source.read(data + write_offset, bytes_to_read);

            tail_ += bytes_to_read;
        }

        // Update the size of the buffer
        size_ -= actual_size;

        return actual_size;
    }

    template <typename source_t>
    auto seekg(source_t &source, const std::streamoff offset, const seek_direction direction) -> bool
    {
        static_assert(has_size_v<source_t>, "Circular buffer requires stream with size.");

        if (direction != seek_direction::current)
            return false;

        const auto source_size = source.size();

        tail_ += offset;

        if (size_ > 0)
            tail_ = tail_ % source_size;

        if (tail_ < 0)
            tail_ = source_size + tail_;

        size_ -= offset;

        if (size_ > source_size)
            size_ = source_size;

        return true;
    }

    template <typename source_t>
    [[nodiscard]] auto tellg(source_t &source) const -> std::streamoff
    {
        static_assert(has_size_v<source_t>, "Circular buffer requires stream with size.");
        return tail_;
    }

    template <typename sink_t>
    auto seekp(sink_t &sink, const std::streamoff offset, const seek_direction direction) -> bool
    {
        static_assert(has_size_v<sink_t>, "Circular buffer requires stream with size.");
        return false;
    }

    template <typename sink_t>
    [[nodiscard]] auto tellp(sink_t &sink) const -> std::streamoff
    {
        static_assert(has_size_v<sink_t>, "Circular buffer requires stream with size.");
        return head_;
    }

    template <typename source_t>
    [[nodiscard]] auto eof(source_t &source) const -> bool
    {
        static_assert(has_size_v<source_t>, "Circular buffer requires stream with size.");
        return size_ == source.size();
    }

    template <typename source_t>
    [[nodiscard]] auto size(source_t &) const noexcept -> std::streamoff
    {
        return size_;
    }

private:
    template <typename stream_t>
    [[nodiscard]] auto is_out_of_bounds(stream_t &stream, std::streamoff offset) const -> bool
    {
        return (offset > stream.size());
    }

    template <typename stream_t>
    [[nodiscard]] auto fits_in_buffer(stream_t &stream, std::streamoff size) const -> bool
    {
        return ((size_ + size) <= stream.size());
    }

    std::streamoff tail_;
    std::streamoff head_;
    std::streamoff size_;
};

} // namespace aeon::streams

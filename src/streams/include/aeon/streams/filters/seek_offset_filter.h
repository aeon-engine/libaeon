// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/streams/filters/filter.h>
#include <aeon/streams/seek_direction.h>
#include <aeon/streams/tags.h>

namespace aeon::streams
{

template <std::streamoff seek_offset = 0>
class source_seek_offset_filter : public filter
{
public:
    struct category : input_seekable
    {
    };

    explicit source_seek_offset_filter() = default;
    ~source_seek_offset_filter() = default;

    source_seek_offset_filter(source_seek_offset_filter &&) noexcept = default;
    auto operator=(source_seek_offset_filter &&) noexcept -> source_seek_offset_filter & = default;

    source_seek_offset_filter(const source_seek_offset_filter &) noexcept = default;
    auto operator=(const source_seek_offset_filter &) noexcept -> source_seek_offset_filter & = default;

    template <typename source_t>
    auto seekg(source_t &source, const std::streamoff offset, const seek_direction direction) -> bool
    {
        return source.seekg(offset + seek_offset, direction);
    }

    template <typename source_t>
    [[nodiscard]] auto tellg(source_t &source) -> std::streamoff
    {
        return source.tellg() + seek_offset;
    }
};

template <std::streamoff seek_offset = 0>
class sink_seek_offset_filter : public filter
{
public:
    struct category : output_seekable
    {
    };

    explicit sink_seek_offset_filter() = default;
    ~sink_seek_offset_filter() = default;

    sink_seek_offset_filter(sink_seek_offset_filter &&) noexcept = default;
    auto operator=(sink_seek_offset_filter &&) noexcept -> sink_seek_offset_filter & = default;

    sink_seek_offset_filter(const sink_seek_offset_filter &) noexcept = default;
    auto operator=(const sink_seek_offset_filter &) noexcept -> sink_seek_offset_filter & = default;

    template <typename sink_t>
    auto seekp(sink_t &sink, const std::streamoff offset, const seek_direction direction) -> bool
    {
        return sink.seekp(offset + seek_offset, direction);
    }

    template <typename sink_t>
    [[nodiscard]] auto tellp(sink_t &sink) const -> std::streamoff
    {
        return sink.tellp() + seek_offset;
    }
};

template <std::streamoff seek_offset = 0>
class seek_offset_filter : public source_seek_offset_filter<seek_offset>, public sink_seek_offset_filter<seek_offset>
{
public:
    struct category : input_seekable, output_seekable
    {
    };

    explicit seek_offset_filter() = default;
    ~seek_offset_filter() = default;

    seek_offset_filter(seek_offset_filter &&) noexcept = default;
    auto operator=(seek_offset_filter &&) noexcept -> seek_offset_filter & = default;

    seek_offset_filter(const seek_offset_filter &) noexcept = default;
    auto operator=(const seek_offset_filter &) noexcept -> seek_offset_filter & = default;
};

} // namespace aeon::streams

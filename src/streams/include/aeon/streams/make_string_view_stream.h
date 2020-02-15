// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_view_device.h>

namespace aeon::streams
{

inline auto make_string_view_stream(std::string &str)
{
    return make_dynamic_stream(streams::memory_view_device{str});
}

inline auto make_string_view_stream(const std::string &str)
{
    return make_dynamic_stream(streams::memory_view_device{str});
}

inline auto make_string_view_stream(std::u8string &str)
{
    return make_dynamic_stream(streams::memory_view_device{str});
}

inline auto make_string_view_stream(const std::u8string &str)
{
    return make_dynamic_stream(streams::memory_view_device{str});
}

inline auto make_string_view_stream_ptr(std::string &str)
{
    return make_dynamic_stream_ptr(streams::memory_view_device{str});
}

inline auto make_string_view_stream_ptr(const std::string &str)
{
    return make_dynamic_stream_ptr(streams::memory_view_device{str});
}

inline auto make_string_view_stream_ptr(std::u8string &str)
{
    return make_dynamic_stream_ptr(streams::memory_view_device{str});
}

inline auto make_string_view_stream_ptr(const std::u8string &str)
{
    return make_dynamic_stream_ptr(streams::memory_view_device{str});
}

} // namespace aeon::streams

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_device.h>

namespace aeon::streams
{

inline auto make_string_stream()
{
    return make_dynamic_stream(streams::memory_device<std::string>{});
}

inline auto make_string_stream(std::string &&str)
{
    return make_dynamic_stream(streams::memory_device{std::move(str)});
}

inline auto make_string_stream(const std::string &str)
{
    return make_dynamic_stream(streams::memory_device{str});
}

inline auto make_string_stream_ptr()
{
    return make_dynamic_stream_ptr(streams::memory_device<std::string>{});
}

inline auto make_string_stream_ptr(std::string &&str)
{
    return make_dynamic_stream_ptr(streams::memory_device{std::move(str)});
}

inline auto make_string_stream_ptr(const std::string &str)
{
    return make_dynamic_stream_ptr(streams::memory_device{str});
}

} // namespace aeon::streams

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_device.h>

namespace aeon::streams
{

template <typename T>
inline auto make_vector_stream()
{
    return make_dynamic_stream(streams::memory_device<std::vector<T>>{});
}

template <typename T>
inline auto make_vector_stream(std::vector<T> &&data)
{
    auto device = streams::memory_device{std::move(data)};
    return make_dynamic_stream(std::move(device));
}

template <typename T>
inline auto make_vector_stream(const std::vector<T> &data)
{
    auto device = streams::memory_device{data};
    return make_dynamic_stream(std::move(device));
}

template <typename T>
inline auto make_vector_stream_ptr()
{
    return make_dynamic_stream_ptr(streams::memory_device<std::vector<T>>{});
}

template <typename T>
inline auto make_vector_stream_ptr(std::vector<T> &&data)
{
    auto device = streams::memory_device{std::move(data)};
    return make_dynamic_stream_ptr(std::move(device));
}

template <typename T>
inline auto make_vector_stream_ptr(const std::vector<T> &data)
{
    auto device = streams::memory_device{data};
    return make_dynamic_stream_ptr(std::move(device));
}

} // namespace aeon::streams

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_view_device.h>

namespace aeon::streams
{

template <typename T>
inline auto make_vector_view_stream(std::vector<T> &data)
{
    auto device = streams::memory_view_device{data};
    return make_dynamic_stream(std::move(device));
}

template <typename T>
inline auto make_vector_view_stream(const std::vector<T> &data)
{
    auto device = streams::memory_view_device{data};
    return make_dynamic_stream(std::move(device));
}

template <typename T>
inline auto make_vector_view_stream_ptr(std::vector<T> &data)
{
    auto device = streams::memory_view_device{data};
    return make_dynamic_stream_ptr(std::move(device));
}

template <typename T>
inline auto make_vector_view_stream_ptr(const std::vector<T> &data)
{
    auto device = streams::memory_view_device{data};
    return make_dynamic_stream_ptr(std::move(device));
}

} // namespace aeon::streams

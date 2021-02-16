// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/streams/aggregate_device.h>

namespace aeon::streams
{

template <typename first_t, typename... T>
inline auto make_aggregate_device(first_t &&first, T &&...t)
{
    return (std::forward<first_t>(first) | (... | std::forward<T>(t)));
}

} // namespace aeon::streams

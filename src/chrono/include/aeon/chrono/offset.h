// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <chrono>

namespace aeon::chrono
{

enum class offset_timezone
{
    local,
    gmt
};

struct offset_result final
{
    std::chrono::milliseconds raw_offset{};
    std::chrono::milliseconds dst_offset{};
};

} // namespace aeon::chrono

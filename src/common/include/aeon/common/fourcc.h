// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <cstdint>

namespace aeon::common
{

inline constexpr auto fourcc(const char a, const char b, const char c, const char d) noexcept
{
    return static_cast<std::uint32_t>(d) << 24 | static_cast<std::uint32_t>(c) << 16 |
           static_cast<std::uint32_t>(b) << 8 | static_cast<std::uint32_t>(a);
}

inline constexpr auto fourcc(const char str[5]) noexcept
{
    return static_cast<std::uint32_t>(str[3]) << 24 | static_cast<std::uint32_t>(str[2]) << 16 |
           static_cast<std::uint32_t>(str[1]) << 8 | static_cast<std::uint32_t>(str[0]);
}

} // namespace aeon::common

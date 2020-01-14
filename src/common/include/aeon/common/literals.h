// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <cstddef>
#include <cstdint>

inline constexpr auto operator"" _size_t(unsigned long long int x) noexcept -> std::size_t
{
    return static_cast<std::size_t>(x);
}

inline constexpr auto operator"" _uint8_t(unsigned long long int x) noexcept -> std::uint8_t
{
    return static_cast<std::uint8_t>(x);
}

inline constexpr auto operator"" _uint16_t(unsigned long long int x) noexcept -> std::uint16_t
{
    return static_cast<std::uint16_t>(x);
}

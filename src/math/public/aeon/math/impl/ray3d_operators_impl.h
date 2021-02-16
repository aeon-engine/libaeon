// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr auto operator==(const ray3d<T> &lhs, const ray3d<T> &rhs) noexcept -> bool
{
    return normal(lhs) == normal(rhs) && origin(lhs) == origin(rhs);
}

template <typename T>
inline constexpr auto operator!=(const ray3d<T> &lhs, const ray3d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math

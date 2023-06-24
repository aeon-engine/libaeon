// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const ray3d<T> &lhs, const ray3d<T> &rhs) noexcept -> bool
{
    return normal(lhs) == normal(rhs) && origin(lhs) == origin(rhs);
}

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator!=(const ray3d<T> &lhs, const ray3d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math

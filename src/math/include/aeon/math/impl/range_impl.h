// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

namespace aeon::math
{

template <typename T>
inline constexpr range<T>::range() noexcept
    : begin{}
    , end{}
{
}

template <typename T>
inline constexpr range<T>::range(const T begin, const T end) noexcept
    : begin{begin}
    , end{end}
{
}

template <typename T>
[[nodiscard]] inline constexpr auto begin(const range<T> &range) noexcept -> T
{
    return range.begin;
}

template <typename T>
[[nodiscard]] inline constexpr auto end(const range<T> &range) noexcept -> T
{
    return range.end;
}

template <typename T>
[[nodiscard]] inline constexpr auto size(const range<T> &range) noexcept -> T
{
    return range.end - range.begin;
}

template <typename T>
inline constexpr auto operator==(const range<T> &lhs, const range<T> &rhs) noexcept -> bool
{
    return begin(lhs) == begin(rhs) && end(lhs) == end(rhs);
}

template <typename T>
inline constexpr auto operator!=(const range<T> &lhs, const range<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math

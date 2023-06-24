// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
constexpr line_segment2d<T>::line_segment2d() noexcept = default;

template <common::concepts::arithmetic_convertible T>
constexpr line_segment2d<T>::line_segment2d(const vector2<T> &begin, const vector2<T> &end) noexcept
    : range<vector2<T>>{begin, end}
{
}

template <common::concepts::arithmetic_convertible T>
constexpr line_segment2d<T>::line_segment2d(const T begin_x, const T begin_y, const T end_x, const T end_y) noexcept
    : range<vector2<T>>{{vector2<T>{begin_x, begin_y}}, {vector2<T>{end_x, end_y}}}
{
}

} // namespace aeon::math

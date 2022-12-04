// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
constexpr line_segment3d<T>::line_segment3d() noexcept = default;

template <common::concepts::arithmetic_convertible T>
constexpr line_segment3d<T>::line_segment3d(const vector3<T> &begin, const vector3<T> &end) noexcept
    : range<vector3<T>>{begin, end}
{
}

template <common::concepts::arithmetic_convertible T>
constexpr line_segment3d<T>::line_segment3d(const T begin_x, const T begin_y, const T begin_z, const T end_x,
                                            const T end_y, const T end_z) noexcept
    : range<vector3<T>>{{vector3<T>{begin_x, begin_y, begin_z}}, {vector3<T>{end_x, end_y, end_z}}}
{
}

} // namespace aeon::math

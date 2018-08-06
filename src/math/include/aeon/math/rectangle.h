/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <aeon/math/anchor_point.h>
#include <aeon/math/math_fwd.h>
#include <type_traits>
#include <tuple>

namespace aeon::math
{

template <typename T>
class size2d;

template <typename T>
class rectangle
{
public:
    constexpr rectangle() noexcept;

    constexpr rectangle(const T left, const T top, const T right, const T bottom) noexcept;

    constexpr rectangle(const vector2<T> left_top, const vector2<T> right_bottom) noexcept;

    constexpr rectangle(const T left, const T top, const size2d<T> size) noexcept;

    constexpr rectangle(const vector2<T> left_top, const size2d<T> size) noexcept;

    constexpr rectangle(const vector2<T> position, const size2d<T> size, const anchor_point anchor) noexcept;

    ~rectangle() noexcept = default;

    constexpr rectangle(const rectangle<T> &) noexcept = default;
    constexpr auto operator=(const rectangle<T> &) noexcept -> rectangle<T> & = default;

    constexpr rectangle(rectangle<T> &&) noexcept = default;
    constexpr auto operator=(rectangle<T> &&) noexcept -> rectangle<T> & = default;

    T left;
    T top;
    T right;
    T bottom;
};

template <typename T>
inline constexpr auto left(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto top(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto right(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto bottom(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto width(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto height(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto left_top(const rectangle<T> &rect) noexcept -> vector2<T>;

template <typename T>
inline constexpr auto right_top(const rectangle<T> &rect) noexcept -> vector2<T>;

template <typename T>
inline constexpr auto left_bottom(const rectangle<T> &rect) noexcept -> vector2<T>;

template <typename T>
inline constexpr auto right_bottom(const rectangle<T> &rect) noexcept -> vector2<T>;

template <typename T>
inline constexpr auto center(const rectangle<T> &rect) noexcept -> vector2<T>;

template <typename T>
inline constexpr auto empty(const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline constexpr auto null(const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline constexpr auto valid(const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline constexpr auto size(const rectangle<T> &rect) noexcept -> size2d<T>;

template <typename T>
inline constexpr void translate(rectangle<T> &rect, const T x, const T y) noexcept;

template <typename T>
inline constexpr void translate(rectangle<T> &rect, const vector2<T> &vec) noexcept;

template <typename T>
inline constexpr auto translated(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto translated(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>;

template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const T x, const T y) noexcept;

template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const vector2<T> &vec) noexcept;

template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const T x, const T y, const anchor_point anchor) noexcept;

template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const vector2<T> &vec, const anchor_point anchor) noexcept;

template <typename T>
inline constexpr auto positioned(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto positioned(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto positioned(const rectangle<T> &rect, const T x, const T y, const anchor_point anchor) noexcept
    -> rectangle<T>;

template <typename T>
inline constexpr auto positioned(const rectangle<T> &rect, const vector2<T> &vec, const anchor_point anchor) noexcept
    -> rectangle<T>;

template <typename T>
inline constexpr auto contains(const rectangle<T> &inner, const rectangle<T> &outer) noexcept -> bool;

template <typename T>
inline constexpr auto contains(const vector2<T> &vec, const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline constexpr auto overlaps(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> bool;

template <typename T>
inline constexpr auto intersection(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> rectangle<T>;

template <typename T, typename... U>
inline constexpr auto bounding_box(const rectangle<T> &first, const rectangle<U> &... rectangles) noexcept
    -> rectangle<T>;

template <typename T>
inline constexpr void inflate(rectangle<T> &rect, const T val) noexcept;

template <typename T>
inline constexpr auto inflated(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>;

template <typename T>
inline constexpr void scale(rectangle<T> &rect, const T val) noexcept;

template <typename T>
inline constexpr void scale(rectangle<T> &rect, const T x, const T y) noexcept;

template <typename T>
inline constexpr void scale(rectangle<T> &rect, const vector2<T> &vec) noexcept;

template <typename T>
inline constexpr void scale(rectangle<T> &rect, const size2d<T> &size) noexcept;

template <typename T>
inline constexpr auto scaled(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto scaled(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto scaled(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto scaled(const rectangle<T> &rect, const size2d<T> &size) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto distance(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> T;

template <typename T>
inline constexpr auto distance(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> T;

template <typename T>
inline constexpr auto area(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline constexpr auto closest_point(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline constexpr void normalize(rectangle<T> &rect) noexcept;

template <typename T>
inline constexpr auto normalized(const rectangle<T> &rect) noexcept -> rectangle<T>;

template <typename T, typename U>
inline constexpr auto
    slice_horizontal(const rectangle<T> &rect, const U ratio,
                     typename std::enable_if<std::is_floating_point_v<U>>::type *dummy = nullptr) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

template <typename T>
inline constexpr auto slice_horizontal_absolute(const rectangle<T> &rect, const T value) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

template <typename T, typename U>
inline constexpr auto
    slice_vertical(const rectangle<T> &rect, const U ratio,
                   typename std::enable_if<std::is_floating_point_v<U>>::type *dummy = nullptr) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

template <typename T>
inline constexpr auto slice_vertical_absolute(const rectangle<T> &rect, const T value) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

template <typename T>
inline constexpr auto operator==(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator+(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator+=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator+(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator+=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*(const rectangle<T> &lhs, const size2d<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*=(rectangle<T> &lhs, const size2d<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

} // namespace aeon::math

#include <aeon/math/impl/rectangle_impl.h>

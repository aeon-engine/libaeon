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

#include <aeon/math/vector2.h>
#include <type_traits>

namespace aeon::math
{

template <typename T>
class size2d;

template <typename T>
class rectangle;

template <typename T>
class circle
{
public:
    circle(const T radius) noexcept;

    circle(const vector2<T> position, const T radius) noexcept;

    ~circle() noexcept = default;

    circle(const circle &) noexcept = default;
    auto operator=(const circle &) noexcept -> circle & = default;

    circle(circle &&) noexcept = default;
    auto operator=(circle &&) noexcept -> circle & = default;

    vector2<T> position;
    T radius;
};

template <typename T>
inline auto position(const circle<T> &c) noexcept -> vector2<T>;

template <typename T>
inline auto center(const circle<T> &c) noexcept -> vector2<T>;

template <typename T>
inline auto empty(const circle<T> &c) noexcept -> bool;

template <typename T>
inline auto null(const circle<T> &c) noexcept -> bool;

template <typename T>
inline auto valid(const circle<T> &c) noexcept -> bool;

template <typename T>
inline auto size(const circle<T> &c) noexcept -> size2d<T>;

template <typename T>
inline auto radius(const circle<T> &c) noexcept -> T;

template <typename T>
inline auto radius_squared(const circle<T> &c) noexcept -> T;

template <typename T>
inline auto diameter(const circle<T> &c) noexcept -> T;

template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type * = nullptr>
inline auto circumference(const circle<T> &c) noexcept -> float;

template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type * = nullptr>
inline auto circumference(const circle<T> &c) noexcept -> T;

template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type * = nullptr>
inline auto area(const circle<T> &c) noexcept -> float;

template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type * = nullptr>
inline auto area(const circle<T> &c) noexcept -> T;

template <typename T>
inline auto set_position(const circle<T> &c, const T x, const T y) noexcept -> circle<T>;

template <typename T>
inline auto set_position(const circle<T> &c, const vector2<T> &vec) noexcept -> circle<T>;

template <typename T>
inline auto inflate(const circle<T> &c, const T val) noexcept -> circle<T>;

template <typename T>
inline auto scale(const circle<T> &c, const T val) noexcept -> circle<T>;

template <typename T>
inline auto rect(const circle<T> &c) noexcept -> rectangle<T>;

template <typename T>
inline auto distance(const circle<T> &lhs, const circle<T> &rhs) noexcept -> T;

template <typename T>
inline auto distance(const circle<T> &lhs, const vector2<T> &rhs) noexcept -> T;

template <typename T>
inline auto contains(const circle<T> &c, const vector2<T> &vec) noexcept -> bool;

template <typename T>
inline auto overlaps(const circle<T> &c, const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline auto operator==(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/circle_impl.h>

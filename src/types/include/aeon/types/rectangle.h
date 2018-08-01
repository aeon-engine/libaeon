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

#include <aeon/math/math_fwd.h>

namespace aeon::types
{

template <typename T>
class coordinate;

template <typename T>
class size2d;

template <typename T>
class rectangle
{
public:
    rectangle() noexcept;

    rectangle(const T left, const T top, const T right, const T bottom) noexcept;

    ~rectangle() noexcept = default;

    rectangle(const rectangle<T> &) noexcept = default;
    auto operator=(const rectangle<T> &) noexcept -> rectangle<T> & = default;

    rectangle(rectangle<T> &&) noexcept = default;
    auto operator=(rectangle<T> &&) noexcept -> rectangle<T> & = default;

    T left;
    T top;
    T right;
    T bottom;
};

template <typename T>
inline auto left(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline auto top(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline auto right(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline auto bottom(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline auto width(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline auto height(const rectangle<T> &rect) noexcept -> T;

template <typename T>
inline auto left_top(const rectangle<T> &rect) noexcept -> coordinate<T>;

template <typename T>
inline auto right_top(const rectangle<T> &rect) noexcept -> coordinate<T>;

template <typename T>
inline auto left_bottom(const rectangle<T> &rect) noexcept -> coordinate<T>;

template <typename T>
inline auto right_bottom(const rectangle<T> &rect) noexcept -> coordinate<T>;

template <typename T>
inline auto empty(const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline auto size(const rectangle<T> &rect) noexcept -> size2d<T>;

template <typename T>
inline auto translate(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

template <typename T>
inline auto translate(const rectangle<T> &rect, const math::vector2<T> &vec) noexcept -> rectangle<T>;

template <typename T>
inline auto translate(const rectangle<T> &rect, const coordinate<T> &coord) noexcept -> rectangle<T>;

template <typename T>
inline auto contains(const rectangle<T> &small, const rectangle<T> &large) noexcept -> bool;

template <typename T>
inline auto contains(const math::vector2<T> &vec, const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline auto contains(const coordinate<T> &coord, const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline auto operator==(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator*(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline auto operator*=(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

} // namespace aeon::types

#include <aeon/types/impl/rectangle_impl.h>

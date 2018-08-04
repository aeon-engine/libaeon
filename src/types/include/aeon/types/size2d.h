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
class rectangle;

template <typename T>
class size2d
{
public:
    size2d() noexcept;

    size2d(const T width, const T height) noexcept;

    ~size2d() noexcept = default;

    size2d(const size2d &) noexcept = default;
    auto operator=(const size2d &) noexcept -> size2d & = default;

    size2d(size2d &&) noexcept = default;
    auto operator=(size2d &&) noexcept -> size2d & = default;

    T width;
    T height;
};

template <typename T>
inline auto width(const size2d<T> &size) noexcept -> T;

template <typename T>
inline auto height(const size2d<T> &size) noexcept -> T;

template <typename T>
inline auto surface(const size2d<T> &size) noexcept -> T;

template <typename T>
inline auto rect(const size2d<T> &size) noexcept -> rectangle<T>;

template <typename T>
inline auto contains(const math::vector2<T> &vec, const size2d<T> size) noexcept -> bool;

template <typename T>
inline auto operator==(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator+(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator+=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator+(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator+=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator-(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator-=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator-(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator-=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator*(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator*=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator*(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline auto operator*=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

} // namespace aeon::types

#include <aeon/types/impl/size2d_impl.h>

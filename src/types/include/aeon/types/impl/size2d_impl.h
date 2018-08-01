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

#include <aeon/types/rectangle.h>

namespace aeon::types
{

template <typename T>
inline size2d<T>::size2d() noexcept
    : width{}
    , height{}
{
}

template <typename T>
inline size2d<T>::size2d(const T width, const T height) noexcept
    : width{width}
    , height{height}
{
}

template <typename T>
inline auto width(const size2d<T> &size) noexcept -> T
{
    return size.width;
}

template <typename T>
inline auto height(const size2d<T> &size) noexcept -> T
{
    return size.height;
}

template <typename T>
inline auto surface(const size2d<T> &size) noexcept -> T
{
    return width(size) * height(size);
}

template <typename T>
inline auto rect(const size2d<T> &size) noexcept -> rectangle<T>
{
    return {0, 0, width(size), height(size)};
}

template <typename T>
inline auto operator==(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return lhs.width == rhs.width && lhs.height == rhs.height;
}

template <typename T>
inline auto operator!=(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator+(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width + rhs.width, lhs.height + rhs.height};
}

template <typename T>
inline auto operator+=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {lhs.width + rhs, lhs.height + rhs};
}

template <typename T>
inline auto operator+=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width - rhs.width, lhs.height - rhs.height};
}

template <typename T>
inline auto operator-=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {lhs.width - rhs, lhs.height - rhs};
}

template <typename T>
inline auto operator-=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {lhs.width * rhs.width, lhs.height * rhs.height};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {lhs.width * rhs, lhs.height * rhs};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

} // namespace aeon::types

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

namespace aeon::math
{

template <typename T>
class vector2;

template <typename T>
class vector3;

template <typename T>
class vector4
{
public:
    vector4() noexcept;

    explicit vector4(const T xyzw) noexcept;

    vector4(const T x, const T y) noexcept;

    vector4(const T x, const T y, const T z) noexcept;

    vector4(const T x, const T y, const T z, const T w) noexcept;

    template <typename U>
    explicit vector4(const U x, const U y) noexcept;

    template <typename U>
    explicit vector4(const U x, const U y, const U z) noexcept;

    template <typename U>
    explicit vector4(const U x, const U y, const U z, const U w) noexcept;

    explicit vector4(const vector2<T> vec) noexcept;

    explicit vector4(const vector2<T> vec, const T z) noexcept;

    explicit vector4(const vector2<T> vec, const T z, const T w) noexcept;

    explicit vector4(const vector3<T> vec) noexcept;

    explicit vector4(const vector3<T> vec, const T w) noexcept;

    explicit vector4(const T xyzw[4]) noexcept;

    ~vector4() noexcept = default;

    vector4(const vector4<T> &) noexcept = default;
    auto operator=(const vector4<T> &) noexcept -> vector4<T> & = default;

    vector4(vector4<T> &&) noexcept = default;
    auto operator=(vector4<T> &&) noexcept -> vector4<T> & = default;

    auto operator=(const vector2<T> &vec) noexcept -> vector4<T> &;

    auto operator=(const vector3<T> &vec) noexcept -> vector4<T> &;

    static auto zero() noexcept -> vector4<T>;

    void set(const T new_x, const T new_y, const T new_z, const T new_w) noexcept;

    T x;
    T y;
    T z;
    T w;
};

template <typename T>
inline auto operator+(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator+(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator+(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const vector4<T> &vec) noexcept -> vector4<T>;

template <typename T>
inline auto operator*(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator*(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator*(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator/(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator+=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator+=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator+=(T &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator-=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator-=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator-=(T &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator*=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator*=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator*=(T &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator/=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator==(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto dot(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T;

template <typename T>
inline auto length(const vector4<T> &vec) noexcept -> T;

template <typename T>
inline auto squared_length(const vector4<T> &vec) noexcept -> T;

template <typename T>
inline auto normalized(const vector4<T> &vec) noexcept -> vector4<T>;

template <typename T>
inline auto sin(const vector4<T> &vec) noexcept -> vector4<T>;

template <typename T>
inline auto cos(const vector4<T> &vec) noexcept -> vector4<T>;

template <typename T>
inline auto tan(const vector4<T> &vec) noexcept -> vector4<T>;

template <typename T>
inline auto distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T;

template <typename T>
inline auto squared_distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T;

template <typename T>
inline auto midpoint(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto floor(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto ceil(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto ptr(vector4<T> &vec) noexcept -> T *;

template <typename T>
inline auto ptr(const vector4<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector4_impl.h>
#include <aeon/math/impl/vector4_operators_impl.h>

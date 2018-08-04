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

#include <cstddef>

namespace aeon::math
{

template <typename T>
class vector2
{
public:
    vector2() noexcept;

    explicit vector2(const T xy) noexcept;

    vector2(const T x, const T y) noexcept;

    template <typename U>
    explicit vector2(const U x, const U y) noexcept;

    explicit vector2(const T xy[2]) noexcept;

    ~vector2() noexcept = default;

    vector2(const vector2<T> &) noexcept = default;
    auto operator=(const vector2<T> &) noexcept -> vector2<T> & = default;

    vector2(vector2<T> &&) noexcept = default;
    auto operator=(vector2<T> &&) noexcept -> vector2<T> & = default;

    auto operator[](const std::size_t i) noexcept -> T &;
    auto operator[](const std::size_t i) const noexcept -> const T &;

    static auto zero() noexcept -> vector2<T>;

    void set(const T new_x, const T new_y) noexcept;

    union {
        struct
        {
            T x;
            T y;
        };
        T value[2];
    };
};

template <typename T>
inline auto operator+(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator+(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator+(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto operator*(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator*(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator*(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator/(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator/(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator+=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator+=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator+=(T &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator-=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator-=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator-=(T &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator*=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator*=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator*=(T &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator/=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator/=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator==(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto translate(const vector2<T> &lhs, const T x, const T y) noexcept -> vector2<T>;

template <typename T>
inline auto translate(const vector2<T> &lhs, const math::vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto dot(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

template <typename T>
inline auto cross(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

template <typename T>
inline auto length(const vector2<T> &vec) noexcept -> T;

template <typename T>
inline auto squared_length(const vector2<T> &vec) noexcept -> T;

template <typename T>
inline auto normalized(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto sin(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto cos(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto tan(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto asin(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto acos(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto atan(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto atan2(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto abs(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

template <typename T>
inline auto squared_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

template <typename T>
inline auto midpoint(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto floor(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto ceil(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto ptr(vector2<T> &vec) noexcept -> T *;

template <typename T>
inline auto ptr(const vector2<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector2_impl.h>
#include <aeon/math/impl/vector2_operators_impl.h>

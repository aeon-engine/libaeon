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

class mat4;

class mat3
{
public:
    mat3() noexcept;
    mat3(const float m00, const float m10, const float m20, const float m01, const float m11, const float m21,
         const float m02, const float m12, const float m22) noexcept;
    ~mat3() noexcept = default;

    explicit mat3(const mat4 &m) noexcept;

    mat3(const mat3 &) noexcept = default;
    auto operator=(const mat3 &) noexcept -> mat3 & = default;

    mat3(mat3 &&) noexcept = default;
    auto operator=(mat3 &&) noexcept -> mat3 & = default;

    auto at(const int row, const int column) const noexcept -> float;

    static auto zero() noexcept -> mat3;

    static auto indentity() noexcept -> mat3;

    static auto scale(const float xy) noexcept -> mat3;
    static auto scale(const float x, const float y) noexcept -> mat3;
    static auto scale(const vector2<float> &vec) noexcept -> mat3;

    template <typename T>
    static auto scale(const T xy) noexcept -> mat3;

    template <typename T>
    static auto scale(const T x, const T y) noexcept -> mat3;

    template <typename T>
    static auto scale(const vector2<T> &vec) noexcept -> mat3;

    static auto translate(const float x, const float y) noexcept -> mat3;
    static auto translate(const vector2<float> &vec) noexcept -> mat3;

    template <typename T>
    static auto translate(const T x, const T y) noexcept -> mat3;

    template <typename T>
    static auto translate(const vector2<T> &vec) noexcept -> mat3;

    static auto rotate(const float angle) noexcept -> mat3;

    template <typename T>
    static auto rotate(const T angle) noexcept -> mat3;

    float m00;
    float m10;
    float m20;

    float m01;
    float m11;
    float m21;

    float m02;
    float m12;
    float m22;
};

inline auto operator*(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3;

inline auto operator*(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>;

inline auto operator*(const mat3 &lhs, const float rhs) noexcept -> mat3;

inline auto operator-(const mat3 &mat) noexcept -> mat3;

inline auto operator*=(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3;

inline auto operator*=(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>;

inline auto operator*=(const mat3 &lhs, const float rhs) noexcept -> mat3;

inline auto operator==(const mat3 &lhs, const mat3 &rhs) noexcept -> bool;

inline auto operator!=(const mat3 &lhs, const mat3 &rhs) noexcept -> bool;

inline auto determinant(const mat3 &mat) noexcept -> float;

inline auto qr_decompose(const mat3 &mat, vector3<float> &scale, vector3<float> &shear) noexcept -> mat3;

inline auto ptr(mat3 &mat) noexcept -> float *;

inline auto ptr(const mat3 &mat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/mat3_impl.h>
#include <aeon/math/impl/mat3_operators_impl.h>

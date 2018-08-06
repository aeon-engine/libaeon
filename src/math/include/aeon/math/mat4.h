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

#include <aeon/math/vector4.h>

namespace aeon::math
{

template <typename T>
class rectangle;

template <typename T>
class vector3;

class mat3;
class quaternion;

class alignas(16) mat4
{
public:
    mat4() noexcept;
    mat4(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
         const float m12, const float m13, const float m20, const float m21, const float m22, const float m23,
         const float m30, const float m31, const float m32, const float m33) noexcept;

    ~mat4() noexcept = default;

    explicit mat4(const mat3 &m) noexcept;
    explicit mat4(const quaternion &q) noexcept;

    mat4(const mat4 &) noexcept = default;
    auto operator=(const mat4 &) noexcept -> mat4 & = default;

    mat4(mat4 &&) noexcept = default;
    auto operator=(mat4 &&) noexcept -> mat4 & = default;

    auto operator[](const std::size_t i) noexcept -> vector4<float> &;
    auto operator[](const std::size_t i) const noexcept -> const vector4<float> &;

    auto at(const int column, const int row) const noexcept -> float;

    static auto zero() noexcept -> mat4;

    static auto indentity() noexcept -> mat4;

    static auto scale(const float xyz) noexcept -> mat4;
    static auto scale(const float x, const float y, const float z) noexcept -> mat4;
    static auto scale(const vector3<float> &vec) noexcept -> mat4;

    template <typename T>
    static auto scale(const T xyz) noexcept -> mat4;

    template <typename T>
    static auto scale(const T x, const T y, const T z) noexcept -> mat4;

    template <typename T>
    static auto scale(const vector3<T> &vec) noexcept -> mat4;

    static auto translate(const float x, const float y) noexcept -> mat4;
    static auto translate(const float x, const float y, const float z) noexcept -> mat4;
    static auto translate(const vector3<float> &vec) noexcept -> mat4;

    template <typename T>
    static auto translate(const T x, const T y) noexcept -> mat4;

    template <typename T>
    static auto translate(const T x, const T y, const T z) noexcept -> mat4;

    template <typename T>
    static auto translate(const vector3<T> &vec) noexcept -> mat4;

    static auto rotate(const float angle, const vector3<float> &vec) noexcept -> mat4;

    template <typename T, typename U>
    static auto rotate(const T angle, const vector3<U> &vec) noexcept -> mat4;

    static auto ortho(const float left, const float right, const float bottom, const float top) noexcept -> mat4;

    static auto ortho(const float left, const float right, const float bottom, const float top, const float near,
                      const float far) noexcept -> mat4;

    template <typename T>
    static auto ortho(const T left, const T right, const T bottom, const T top) noexcept -> mat4;

    template <typename T, typename U>
    static auto ortho(const T left, const T right, const T bottom, const T top, const U near, const U far) noexcept
        -> mat4;

    template <typename T>
    static auto ortho(const rectangle<T> &rect) noexcept -> mat4;

    template <typename T, typename U>
    static auto ortho(const rectangle<T> &rect, const U near, const U far) noexcept -> mat4;

    static auto projection(const float fov_y, const float aspect_ratio, const float near, const float far) noexcept
        -> mat4;

    template <typename T, typename U>
    static auto projection(const T fov_y, const T aspect_ratio, const U near, const U far) noexcept -> mat4;

    static auto projection_fov(const float fov, const float width, const float height, const float near,
                               const float far) noexcept -> mat4;

    template <typename T, typename U>
    static auto projection_fov(const T fov, const T width, const T height, const U near, const U far) noexcept -> mat4;

    vector4<float> column[4];
};

inline auto operator*(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4;

inline auto operator*(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>;

inline auto operator*(const mat4 &lhs, const float rhs) noexcept -> mat4;

inline auto operator*=(mat4 &lhs, const mat4 &rhs) noexcept -> mat4 &;

inline auto operator*=(mat4 &lhs, const float rhs) noexcept -> mat4 &;

inline auto operator==(const mat4 &lhs, const mat4 &rhs) noexcept -> bool;

inline auto operator!=(const mat4 &lhs, const mat4 &rhs) noexcept -> bool;

inline auto inverse(const mat4 &mat) noexcept -> mat4;

inline auto is_affine(const mat4 &mat) noexcept -> bool;

inline void decompose(const mat4 &mat, vector3<float> &translation, vector3<float> &scale,
                      quaternion &orientation) noexcept;

inline auto ptr(mat4 &mat) noexcept -> float *;

inline auto ptr(const mat4 &mat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/mat4_impl.h>
#include <aeon/math/impl/mat4_operators_impl.h>

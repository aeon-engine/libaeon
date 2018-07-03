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
class vector3;

class mat3;

class quaternion
{
public:
    quaternion() noexcept;

    quaternion(const float w, const float x, const float y, const float z) noexcept;

    template <typename T>
    explicit quaternion(const T w, const T x, const T y, const T z) noexcept;

    explicit quaternion(const vector3<float> &euler) noexcept;

    explicit quaternion(const mat3 &mat) noexcept;

    ~quaternion() noexcept = default;

    quaternion(const quaternion &) noexcept = default;
    auto operator=(const quaternion &) noexcept -> quaternion & = default;

    quaternion(quaternion &&) noexcept = default;
    auto operator=(quaternion &&) noexcept -> quaternion & = default;

    static auto indentity() noexcept -> quaternion;

    void set(const float new_w, const float new_x, const float new_y, const float new_z) noexcept;

    float w;
    float x;
    float y;
    float z;
};

inline auto operator+(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator-(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator*(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator*(const quaternion &lhs, const float rhs) noexcept -> quaternion;

inline auto operator/(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator/(const quaternion &lhs, const float rhs) noexcept -> quaternion;

inline auto operator+=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator-=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator*=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator*=(const quaternion &lhs, const float rhs) noexcept -> quaternion;

inline auto operator/=(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline auto operator/=(const quaternion &lhs, const float rhs) noexcept -> quaternion;

inline auto operator==(const quaternion &lhs, const quaternion &rhs) noexcept -> bool;

inline auto operator!=(const quaternion &lhs, const quaternion &rhs) noexcept -> bool;

inline auto pitch(const quaternion &quat) noexcept -> float;

inline auto yaw(const quaternion &quat) noexcept -> float;

inline auto roll(const quaternion &quat) noexcept -> float;

inline auto euler(const quaternion &quat) noexcept -> vector3<float>;

inline auto dot(const quaternion &a, const quaternion &b) noexcept -> float;

inline auto ptr(quaternion &quat) noexcept -> float *;

inline auto ptr(const quaternion &quat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/quaternion_impl.h>
#include <aeon/math/impl/quaternion_operators_impl.h>

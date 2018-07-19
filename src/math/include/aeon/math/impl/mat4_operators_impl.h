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

#if (!defined(AEON_DISABLE_AVX))
#include <xmmintrin.h>
#include <immintrin.h>
#endif

namespace aeon::math
{

namespace detail
{

inline auto mat4_mul(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
    // clang-format off
    return {
        (lhs.m00 * rhs.m00) + (lhs.m10 * rhs.m01) + (lhs.m20 * rhs.m02) + (lhs.m30 * rhs.m03),
        (lhs.m01 * rhs.m00) + (lhs.m11 * rhs.m01) + (lhs.m21 * rhs.m02) + (lhs.m31 * rhs.m03),
        (lhs.m02 * rhs.m00) + (lhs.m12 * rhs.m01) + (lhs.m22 * rhs.m02) + (lhs.m32 * rhs.m03),
        (lhs.m03 * rhs.m00) + (lhs.m13 * rhs.m01) + (lhs.m23 * rhs.m02) + (lhs.m33 * rhs.m03),

        (lhs.m00 * rhs.m10) + (lhs.m10 * rhs.m11) + (lhs.m20 * rhs.m12) + (lhs.m30 * rhs.m13),
        (lhs.m01 * rhs.m10) + (lhs.m11 * rhs.m11) + (lhs.m21 * rhs.m12) + (lhs.m31 * rhs.m13),
        (lhs.m02 * rhs.m10) + (lhs.m12 * rhs.m11) + (lhs.m22 * rhs.m12) + (lhs.m32 * rhs.m13),
        (lhs.m03 * rhs.m10) + (lhs.m13 * rhs.m11) + (lhs.m23 * rhs.m12) + (lhs.m33 * rhs.m13),

        (lhs.m00 * rhs.m20) + (lhs.m10 * rhs.m21) + (lhs.m20 * rhs.m22) + (lhs.m30 * rhs.m23),
        (lhs.m01 * rhs.m20) + (lhs.m11 * rhs.m21) + (lhs.m21 * rhs.m22) + (lhs.m31 * rhs.m23),
        (lhs.m02 * rhs.m20) + (lhs.m12 * rhs.m21) + (lhs.m22 * rhs.m22) + (lhs.m32 * rhs.m23),
        (lhs.m03 * rhs.m20) + (lhs.m13 * rhs.m21) + (lhs.m23 * rhs.m22) + (lhs.m33 * rhs.m23),

        (lhs.m00 * rhs.m30) + (lhs.m10 * rhs.m31) + (lhs.m20 * rhs.m32) + (lhs.m30 * rhs.m33),
        (lhs.m01 * rhs.m30) + (lhs.m11 * rhs.m31) + (lhs.m21 * rhs.m32) + (lhs.m31 * rhs.m33),
        (lhs.m02 * rhs.m30) + (lhs.m12 * rhs.m31) + (lhs.m22 * rhs.m32) + (lhs.m32 * rhs.m33),
        (lhs.m03 * rhs.m30) + (lhs.m13 * rhs.m31) + (lhs.m23 * rhs.m32) + (lhs.m33 * rhs.m33)};
    // clang-format on
}

#if (!defined(AEON_DISABLE_AVX))
inline void mat4_mul_column_sse(mat4 const &lhs, mat4 const &rhs, mat4 &out, const int column)
{
    const auto lhs_ptr = ptr(lhs);
    const auto rhs_ptr = ptr(rhs);

    const auto rhs_col0 = _mm_load_ps(&rhs_ptr[4 * 0]);
    const auto rhs_col1 = _mm_load_ps(&rhs_ptr[4 * 1]);
    const auto rhs_col2 = _mm_load_ps(&rhs_ptr[4 * 2]);
    const auto rhs_col3 = _mm_load_ps(&rhs_ptr[4 * 3]);

    const auto val = _mm_load_ps(&lhs_ptr[4 * column]);
    const auto e0 = _mm_shuffle_ps(val, val, _MM_SHUFFLE(0, 0, 0, 0));
    const auto e1 = _mm_shuffle_ps(val, val, _MM_SHUFFLE(1, 1, 1, 1));
    const auto e2 = _mm_shuffle_ps(val, val, _MM_SHUFFLE(2, 2, 2, 2));
    const auto e3 = _mm_shuffle_ps(val, val, _MM_SHUFFLE(3, 3, 3, 3));

    const auto m0 = _mm_mul_ps(rhs_col0, e0);
    const auto m1 = _mm_mul_ps(rhs_col1, e1);
    const auto m2 = _mm_mul_ps(rhs_col2, e2);
    const auto m3 = _mm_mul_ps(rhs_col3, e3);

    const auto a0 = _mm_add_ps(m0, m1);
    const auto a1 = _mm_add_ps(m2, m3);
    const auto a2 = _mm_add_ps(a0, a1);

    _mm_store_ps(&ptr(out)[4 * column], a2);
}

inline auto mat4_mul_sse(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
    mat4 out;
    mat4_mul_column_sse(lhs, rhs, out, 0);
    mat4_mul_column_sse(lhs, rhs, out, 1);
    mat4_mul_column_sse(lhs, rhs, out, 2);
    mat4_mul_column_sse(lhs, rhs, out, 3);
    return out;
}
#endif

} // namespace detail

inline auto operator*(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
#if (!defined(AEON_DISABLE_SSE))
    return detail::mat4_mul_sse(lhs, rhs);
#else
    return detail::mat4_mul(lhs, rhs);
#endif
}

inline auto operator*(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>
{
    // clang-format off
    return {
        (lhs.m00 * rhs.x) + (lhs.m01 * rhs.y) + (lhs.m02 * rhs.z) + (lhs.m03 * rhs.w),
        (lhs.m10 * rhs.x) + (lhs.m11 * rhs.y) + (lhs.m12 * rhs.z) + (lhs.m13 * rhs.w),
        (lhs.m20 * rhs.x) + (lhs.m21 * rhs.y) + (lhs.m22 * rhs.z) + (lhs.m23 * rhs.w),
        (lhs.m30 * rhs.x) + (lhs.m31 * rhs.y) + (lhs.m32 * rhs.z) + (lhs.m33 * rhs.w)};
    // clang-format on
}

inline auto operator*(const mat4 &lhs, const float rhs) noexcept -> mat4
{
    // clang-format off
    return {
        lhs.m00 * rhs, lhs.m01 * rhs, lhs.m02 * rhs, lhs.m03 * rhs,
        lhs.m10 * rhs, lhs.m11 * rhs, lhs.m12 * rhs, lhs.m13 * rhs,
        lhs.m20 * rhs, lhs.m21 * rhs, lhs.m22 * rhs, lhs.m23 * rhs,
        lhs.m30 * rhs, lhs.m31 * rhs, lhs.m32 * rhs, lhs.m33 * rhs};
    // clang-format on
}

inline auto operator*=(mat4 &lhs, const mat4 &rhs) noexcept -> mat4 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*=(mat4 &lhs, const float rhs) noexcept -> mat4 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator==(const mat4 &lhs, const mat4 &rhs) noexcept -> bool
{
    // clang-format off
    return
        lhs.m00 == rhs.m00 &&
        lhs.m10 == rhs.m10 &&
        lhs.m20 == rhs.m20 &&
        lhs.m30 == rhs.m30 &&
        lhs.m01 == rhs.m01 &&
        lhs.m11 == rhs.m11 &&
        lhs.m21 == rhs.m21 &&
        lhs.m31 == rhs.m31 &&
        lhs.m02 == rhs.m02 &&
        lhs.m12 == rhs.m12 &&
        lhs.m22 == rhs.m22 &&
        lhs.m32 == rhs.m32 &&
        lhs.m03 == rhs.m03 &&
        lhs.m13 == rhs.m13 &&
        lhs.m23 == rhs.m23 &&
        lhs.m33 == rhs.m33;
    // clang-format on
}

inline auto operator!=(const mat4 &lhs, const mat4 &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math

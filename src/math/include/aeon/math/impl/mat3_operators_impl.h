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

#if (!defined(AEON_DISABLE_SSE))
#include <xmmintrin.h>
#include <immintrin.h>
#endif

namespace aeon::math
{

namespace detail
{

inline auto mat3_mul(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3
{
    // clang-format off
    return {
        lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0],
        lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0],
        lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0],

        lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1],
        lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1],
        lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1],

        lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2],
        lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2],
        lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2]};
    // clang-format on
}

#if (!defined(AEON_DISABLE_SSE))
inline auto mat3_mul_sse(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3
{
    const auto rhs_col0_01 = _mm_loadu_si64(&rhs[0].x);
    const auto rhs_col0_2 = _mm_bslli_si128(_mm_loadu_si32(&rhs[0].z), 8);
    const auto rhs_col0 = _mm_castsi128_ps(_mm_or_si128(rhs_col0_01, rhs_col0_2));

    const auto rhs_col1_01 = _mm_loadu_si64(&rhs[1].x);
    const auto rhs_col1_2 = _mm_bslli_si128(_mm_loadu_si32(&rhs[1].z), 8);
    const auto rhs_col1 = _mm_castsi128_ps(_mm_or_si128(rhs_col1_01, rhs_col1_2));

    const auto rhs_col2_01 = _mm_loadu_si64(&rhs[2].x);
    const auto rhs_col2_2 = _mm_bslli_si128(_mm_loadu_si32(&rhs[2].z), 8);
    const auto rhs_col2 = _mm_castsi128_ps(_mm_or_si128(rhs_col2_01, rhs_col2_2));

    mat3 out;

    {
        const auto lhs_col_01 = _mm_loadu_si64(&lhs[0].x);
        const auto lhs_col_2 = _mm_bslli_si128(_mm_loadu_si32(&lhs[0].z), 8);
        const auto lhs_col = _mm_castsi128_ps(_mm_or_si128(lhs_col_01, lhs_col_2));
        const auto e0 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(0, 0, 0, 0));
        const auto e1 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(1, 1, 1, 1));
        const auto e2 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(2, 2, 2, 2));

        const auto m0 = _mm_mul_ps(rhs_col0, e0);
        const auto m1 = _mm_mul_ps(rhs_col1, e1);
        const auto m2 = _mm_mul_ps(rhs_col2, e2);

        const auto a0 = _mm_add_ps(m0, m1);
        const auto a1 = _mm_castps_si128(_mm_add_ps(a0, m2));

        _mm_storeu_si64(&out[0].x, a1);
        const auto a1_2 = _mm_bsrli_si128(a1, 8);
        _mm_storeu_si32(&out[0].z, a1_2);
    }

    {
        const auto lhs_col_01 = _mm_loadu_si64(&lhs[1].x);
        const auto lhs_col_2 = _mm_bslli_si128(_mm_loadu_si32(&lhs[1].z), 8);
        const auto lhs_col = _mm_castsi128_ps(_mm_or_si128(lhs_col_01, lhs_col_2));
        const auto e0 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(0, 0, 0, 0));
        const auto e1 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(1, 1, 1, 1));
        const auto e2 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(2, 2, 2, 2));

        const auto m0 = _mm_mul_ps(rhs_col0, e0);
        const auto m1 = _mm_mul_ps(rhs_col1, e1);
        const auto m2 = _mm_mul_ps(rhs_col2, e2);

        const auto a0 = _mm_add_ps(m0, m1);
        const auto a1 = _mm_castps_si128(_mm_add_ps(a0, m2));

        _mm_storeu_si64(&out[1].x, a1);
        const auto a1_2 = _mm_bsrli_si128(a1, 8);
        _mm_storeu_si32(&out[1].z, a1_2);
    }

    {
        const auto lhs_col_01 = _mm_loadu_si64(&lhs[2].x);
        const auto lhs_col_2 = _mm_bslli_si128(_mm_loadu_si32(&lhs[2].z), 8);
        const auto lhs_col = _mm_castsi128_ps(_mm_or_si128(lhs_col_01, lhs_col_2));
        const auto e0 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(0, 0, 0, 0));
        const auto e1 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(1, 1, 1, 1));
        const auto e2 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(2, 2, 2, 2));

        const auto m0 = _mm_mul_ps(rhs_col0, e0);
        const auto m1 = _mm_mul_ps(rhs_col1, e1);
        const auto m2 = _mm_mul_ps(rhs_col2, e2);

        const auto a0 = _mm_add_ps(m0, m1);
        const auto a1 = _mm_castps_si128(_mm_add_ps(a0, m2));

        _mm_storeu_si64(&out[2].x, a1);
        const auto a1_2 = _mm_bsrli_si128(a1, 8);
        _mm_storeu_si32(&out[2].z, a1_2);
    }

    return out;
}
#endif

} // namespace detail

inline auto operator*(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3
{
#if (!defined(AEON_DISABLE_SSE))
    return detail::mat3_mul_sse(lhs, rhs);
#else
    return detail::mat3_mul(lhs, rhs);
#endif
}

inline auto operator*(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>
{
    // clang-format off
    return {
        lhs[0][0] * rhs.x + lhs[0][1] * rhs.y + lhs[0][2] * rhs.z,
        lhs[1][0] * rhs.x + lhs[1][1] * rhs.y + lhs[1][2] * rhs.z,
        lhs[2][0] * rhs.x + lhs[2][1] * rhs.y + lhs[2][2] * rhs.z};
    // clang-format on
}

inline auto operator*(const mat3 &lhs, const float rhs) noexcept -> mat3
{
    // clang-format off
    return {
        lhs[0][0] * rhs, lhs[0][1] * rhs, lhs[0][2] * rhs,
        lhs[1][0] * rhs, lhs[1][1] * rhs, lhs[1][2] * rhs,
        lhs[2][0] * rhs, lhs[2][1] * rhs, lhs[2][2] * rhs};
    // clang-format on
}

inline auto operator-(const mat3 &mat) noexcept -> mat3
{
    // clang-format off
    return {
        -mat[0][0], -mat[0][1], -mat[0][2],
        -mat[1][0], -mat[1][1], -mat[1][2],
        -mat[2][0], -mat[2][1], -mat[2][2]};
    // clang-format on
}

inline auto operator*=(mat3 &lhs, const mat3 &rhs) noexcept -> mat3 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*=(mat3 &lhs, const float rhs) noexcept -> mat3 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator==(const mat3 &lhs, const mat3 &rhs) noexcept -> bool
{
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2];
}

inline auto operator!=(const mat3 &lhs, const mat3 &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math

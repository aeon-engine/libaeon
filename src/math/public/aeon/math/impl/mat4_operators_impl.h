// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/vector4.h>

#if (!defined(AEON_DISABLE_SSE))
#include <xmmintrin.h>
#include <immintrin.h>
#endif

namespace aeon::math
{

namespace detail
{

[[nodiscard]] inline auto mat4_mul(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
{
    const auto lhs_col0 = lhs[0];
    const auto lhs_col1 = lhs[1];
    const auto lhs_col2 = lhs[2];
    const auto lhs_col3 = lhs[3];

    const auto rhs_col0 = rhs[0];
    const auto rhs_col1 = rhs[1];
    const auto rhs_col2 = rhs[2];
    const auto rhs_col3 = rhs[3];

    return {
        {lhs_col0 * rhs_col0.x + lhs_col1 * rhs_col0.y + lhs_col2 * rhs_col0.z + lhs_col3 * rhs_col0.w},
        {lhs_col0 * rhs_col1.x + lhs_col1 * rhs_col1.y + lhs_col2 * rhs_col1.z + lhs_col3 * rhs_col1.w},
        {lhs_col0 * rhs_col2.x + lhs_col1 * rhs_col2.y + lhs_col2 * rhs_col2.z + lhs_col3 * rhs_col2.w},
        {lhs_col0 * rhs_col3.x + lhs_col1 * rhs_col3.y + lhs_col2 * rhs_col3.z + lhs_col3 * rhs_col3.w},
    };
}

#if (!defined(AEON_DISABLE_SSE))
inline void mat4_mul_column_sse(mat4 const &lhs, mat4 const &rhs, mat4 &out, const int column)
{
    const auto lhs_ptr = ptr(lhs);
    const auto rhs_ptr = ptr(rhs);

    const auto rhs_col0 = _mm_load_ps(&lhs_ptr[4 * 0]);
    const auto rhs_col1 = _mm_load_ps(&lhs_ptr[4 * 1]);
    const auto rhs_col2 = _mm_load_ps(&lhs_ptr[4 * 2]);
    const auto rhs_col3 = _mm_load_ps(&lhs_ptr[4 * 3]);

    const auto val = _mm_load_ps(&rhs_ptr[4 * column]);
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

[[nodiscard]] inline auto mat4_mul_sse(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4
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

inline constexpr auto operator*(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>
{
    // clang-format off
    return {
        (lhs[0][0] * rhs.x) + (lhs[1][0] * rhs.y) + (lhs[2][0] * rhs.z) + (lhs[3][0] * rhs.w),
        (lhs[0][1] * rhs.x) + (lhs[1][1] * rhs.y) + (lhs[2][1] * rhs.z) + (lhs[3][1] * rhs.w),
        (lhs[0][2] * rhs.x) + (lhs[1][2] * rhs.y) + (lhs[2][2] * rhs.z) + (lhs[3][2] * rhs.w),
        (lhs[0][3] * rhs.x) + (lhs[1][3] * rhs.y) + (lhs[2][3] * rhs.z) + (lhs[3][3] * rhs.w)};
    // clang-format on
}

inline constexpr auto operator*(const mat4 &lhs, const float rhs) noexcept -> mat4
{
    // clang-format off
    return {
        lhs[0][0] * rhs, lhs[1][0] * rhs, lhs[2][0] * rhs, lhs[3][0] * rhs,
        lhs[0][1] * rhs, lhs[1][1] * rhs, lhs[2][1] * rhs, lhs[3][1] * rhs,
        lhs[0][2] * rhs, lhs[1][2] * rhs, lhs[2][2] * rhs, lhs[3][2] * rhs,
        lhs[0][3] * rhs, lhs[1][3] * rhs, lhs[2][3] * rhs, lhs[3][3] * rhs};
    // clang-format on
}

inline auto operator*=(mat4 &lhs, const mat4 &rhs) noexcept -> mat4 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline constexpr auto operator*=(mat4 &lhs, const float rhs) noexcept -> mat4 &
{
    lhs = lhs * rhs;
    return lhs;
}

inline constexpr auto operator==(const mat4 &lhs, const mat4 &rhs) noexcept -> bool
{
    return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3];
}

inline constexpr auto operator!=(const mat4 &lhs, const mat4 &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::math

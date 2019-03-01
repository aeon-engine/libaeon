// Copyright (c) 2012-2019 Robin Degen

#pragma once

#if (!defined(AEON_DISABLE_SSE))
#include <aeon/common/intrinsics.h>
#include <xmmintrin.h>
#include <immintrin.h>
#endif

namespace aeon::math
{

namespace detail
{

[[nodiscard]] inline auto mat3_mul(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3
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
[[nodiscard]] inline auto mat3_mul_sse(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3
{
    const auto rhs_col0 = aeon_mm_load_ps96(ptr(rhs[0]));
    const auto rhs_col1 = aeon_mm_load_ps96(ptr(rhs[1]));
    const auto rhs_col2 = aeon_mm_load_ps96(ptr(rhs[2]));

    mat3 out;

    {
        const auto lhs_col = aeon_mm_load_ps96(ptr(lhs[0]));

        const auto e0 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(0, 0, 0, 0));
        const auto e1 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(1, 1, 1, 1));
        const auto e2 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(2, 2, 2, 2));

        const auto m0 = _mm_mul_ps(rhs_col0, e0);
        const auto m1 = _mm_mul_ps(rhs_col1, e1);
        const auto m2 = _mm_mul_ps(rhs_col2, e2);

        const auto a0 = _mm_add_ps(m0, m1);
        const auto a1 = _mm_add_ps(a0, m2);

        aeon_mm_store_ps96(ptr(out[0]), a1);
    }

    {
        const auto lhs_col = aeon_mm_load_ps96(ptr(lhs[1]));

        const auto e0 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(0, 0, 0, 0));
        const auto e1 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(1, 1, 1, 1));
        const auto e2 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(2, 2, 2, 2));

        const auto m0 = _mm_mul_ps(rhs_col0, e0);
        const auto m1 = _mm_mul_ps(rhs_col1, e1);
        const auto m2 = _mm_mul_ps(rhs_col2, e2);

        const auto a0 = _mm_add_ps(m0, m1);
        const auto a1 = _mm_add_ps(a0, m2);

        aeon_mm_store_ps96(ptr(out[1]), a1);
    }

    {
        const auto lhs_col = aeon_mm_load_ps96(ptr(lhs[2]));

        const auto e0 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(0, 0, 0, 0));
        const auto e1 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(1, 1, 1, 1));
        const auto e2 = _mm_shuffle_ps(lhs_col, lhs_col, _MM_SHUFFLE(2, 2, 2, 2));

        const auto m0 = _mm_mul_ps(rhs_col0, e0);
        const auto m1 = _mm_mul_ps(rhs_col1, e1);
        const auto m2 = _mm_mul_ps(rhs_col2, e2);

        const auto a0 = _mm_add_ps(m0, m1);
        const auto a1 = _mm_add_ps(a0, m2);

        aeon_mm_store_ps96(ptr(out[2]), a1);
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

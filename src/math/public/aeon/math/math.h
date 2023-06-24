// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

/*!
 * \file
 * \brief Common mathematical constants and functions.
 */

#pragma once

#include <aeon/common/concepts.h>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <array>

/*!
 * Various classes and functions for math with SSE support where applicable.
 */
namespace aeon::math
{

/*!
 * Various common constants for use in mathematical formulas.
 * There are constants available in float and double precision.
 */
template <typename T>
struct constants
{
};

template <>
struct constants<float>
{
    static constexpr auto pi = 3.14159265358979323846f;
    static constexpr auto pi_2 = 1.57079632679489661923f;
    static constexpr auto pi_4 = 0.785398163397448309616f;
    static constexpr auto tau = pi * 2.0f;
    static constexpr auto e = 2.7182818284590452353602874713526625f;
    static constexpr auto log_2e = 1.4426950408889634073599246810018921f;  // log_2(e)
    static constexpr auto log_10e = 0.4342944819032518276511289189166051f; // log_10(e)
    static constexpr auto ln_2 = 0.6931471805599453094172321214581766f;    // ln(2)
    static constexpr auto ln_10 = 2.3025850929940456840179914546843642f;   // ln(10)
    static constexpr auto sqrt_2 = 1.4142135623730950488016887242096981f;  // sqrt(2)
    static constexpr auto sqrt1_2 = 0.7071067811865475244008443621048490f; // 1/sqrt(2)
    static constexpr auto tolerance = 1.0E-05f;
};

template <>
struct constants<double>
{
    static constexpr auto pi = 3.14159265358979323846;
    static constexpr auto pi_2 = 1.57079632679489661923;
    static constexpr auto pi_4 = 0.785398163397448309616;
    static constexpr auto tau = pi * 2.0;
    static constexpr auto e = 2.7182818284590452353602874713526625;
    static constexpr auto log_2e = 1.4426950408889634073599246810018921;  // log_2(e)
    static constexpr auto log_10e = 0.4342944819032518276511289189166051; // log_10(e)
    static constexpr auto ln_2 = 0.6931471805599453094172321214581766;    // ln(2)
    static constexpr auto ln_10 = 2.3025850929940456840179914546843642;   // ln(10)
    static constexpr auto sqrt_2 = 1.4142135623730950488016887242096981;  // sqrt(2)
    static constexpr auto sqrt1_2 = 0.7071067811865475244008443621048490; // 1/sqrt(2)
    static constexpr auto tolerance = 1.0E-10;
};

/*!
 * Calculate a sigmoid function of a given value.
 * A sigmoid function is used to clip any value between 0.0 and 1.0 trough a curve.
 * This is commonly used for weights in neural networks.
 * \param[in] value - Value
 * \return Sigmoid curve value between 0 and 1.
 */
template <std::floating_point T>
[[nodiscard]] inline auto sigmoid(const T value) noexcept -> T
{
    return 1 / (1 + std::exp(-value));
}

/*!
 * Variadic version of std::min
 * \param[in] first - First value
 * \param[in] values - All other values (at least one). Must be the same type as first.
 * \return Lowest value out of all given values
 */
template <common::concepts::arithmetic T, common::concepts::arithmetic... U>
[[nodiscard]] inline auto min(const T first, const U... values) noexcept -> T
{
    auto retval = &first;
    ((retval = &std::min(*retval, values)), ...);
    return *retval;
}

/*!
 * Variadic version of std::max
 * \param[in] first - First value
 * \param[in] values - All other values (at least one). Must be the same type as first.
 * \return Highest value out of all given values
 */
template <common::concepts::arithmetic T, common::concepts::arithmetic... U>
[[nodiscard]] inline auto max(const T first, const U... values) noexcept -> T
{
    auto retval = &first;
    ((retval = &std::max(*retval, values)), ...);
    return *retval;
}

/*!
 * Constexpr version of pow (base<SUP>exponent</SUP>)
 * \param[in] base - The base value (must be arithmetic type)
 * \param[in] exponent - The exponent value
 * \return The result of base<SUP>exponent</SUP>
 */
template <common::concepts::arithmetic T, std::integral U>
[[nodiscard]] inline constexpr auto constexpr_pow(const T base, const U exponent) noexcept -> T
{
    auto val = base;

    for (auto i = U(1); i < exponent; ++i)
        val *= base;

    return val;
}

/*!
 * Calculate whether the difference between a and b is smaller than the acceptable error (epsilon),
 * determined by the larger of a or b. This means that the two values are "close enough", and we can say that they're
 * approximately equal. From The art of computer programming by Knuth
 */
template <std::floating_point T>
[[nodiscard]] inline constexpr auto approximately_equal(const T a, const T b,
                                                        const T epsilon = constants<T>::tolerance) noexcept
{
    const auto abs_a = std::abs(a);
    const auto abs_b = std::abs(b);
    return std::abs(a - b) <= ((abs_a < abs_b ? abs_b : abs_a) * epsilon);
}

/*!
 * Calculate whether the difference between a and b is smaller than the acceptable error (epsilon),
 * determined by the smaller of a or b. This means that the values differ less than the acceptable difference in any
 * calculation, so that perhaps they're not actually equal, but they're "essentially equal" (given the epsilon). From
 * The art of computer programming by Knuth
 */
template <std::floating_point T>
[[nodiscard]] inline constexpr auto essentially_equal(const T a, const T b,
                                                      const T epsilon = constants<T>::tolerance) noexcept -> bool
{
    const auto abs_a = std::abs(a);
    const auto abs_b = std::abs(b);
    return std::abs(a - b) <= ((abs_a > abs_b ? abs_b : abs_a) * epsilon);
}

/*!
 * From The art of computer programming by Knuth
 */
template <std::floating_point T>
[[nodiscard]] inline constexpr auto definitely_greater_than(const T a, const T b,
                                                            const T epsilon = constants<T>::tolerance) noexcept -> bool
{
    const auto abs_a = std::abs(a);
    const auto abs_b = std::abs(b);
    return (a - b) > ((abs_a < abs_b ? abs_b : abs_a) * epsilon);
}

/*!
 * From The art of computer programming by Knuth
 */
template <std::floating_point T>
[[nodiscard]] inline constexpr auto definitely_less_than(const T a, const T b,
                                                         const T epsilon = constants<T>::tolerance) noexcept -> bool
{
    const auto abs_a = std::abs(a);
    const auto abs_b = std::abs(b);
    return (b - a) > ((abs_a < abs_b ? abs_b : abs_a) * epsilon);
}

/*!
 * Returns true if the given value is approximately zero
 */
template <std::floating_point T>
[[nodiscard]] inline constexpr auto approximately_zero(const T a, const T epsilon = constants<T>::tolerance) noexcept
{
    return std::abs(a) < epsilon;
}

/*!
 * Calculate the binomial distribution of the given values (n choose k).
 * In other words, with N tosses, what are the chances of K heads.
 *
 * n must be <= k.
 *
 * Example from https://www.mathsisfun.com/data/binomial-distribution.html:
 * binomial(9, 5) = 126
 * For 9 coin tosses, there are 2^9 = 512 possible outcomes.
 * Out of those outcomes, 126 outcomes will have 5 heads.
 * Or 126/512 = 0.246 = ~25%
 *
 * \param[in] n - Total number
 * \param[in] k - Wanted number
 */
[[nodiscard]] inline constexpr auto binomial(const std::uint64_t n, const std::uint64_t k) noexcept
{
    auto val = 1ull;
    for (auto i = 1ull; i <= k; i++)
    {
        val *= n + 1 - i;
        val /= i;
    }
    return val;
}

/*!
 * Calculate a row on Pascal's triangle.
 * Due to the symmetrical nature of Pascal's triangle,the size of the returned array is row + 1.
 */
template <std::uint64_t row>
[[nodiscard]] inline constexpr auto pascals_triangle_row() noexcept
{
    std::array<std::uint64_t, row + 1> values;

    const auto center = row / 2ull;
    auto k = 0ull;

    while (k <= center)
    {
        values[k] = binomial(row, k);
        k++;
    }

    while (k <= row)
    {
        values[k] = values[row - k];
        k++;
    }

    return values;
}

/*!
 * Round to the nearest integer value, rounding halfway cases away from zero, is returned
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const T val) noexcept
{
    return std::round(val);
}

} // namespace aeon::math

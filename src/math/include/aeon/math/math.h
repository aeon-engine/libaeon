// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

/*!
 * \file
 * \brief Common mathematical constants and functions.
 */

#pragma once

#include <type_traits>
#include <limits>
#include <cmath>
#include <algorithm>

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
};

template <>
struct constants<double>
{
    static constexpr auto pi = 3.14159265358979323846;
    static constexpr auto pi_2 = 1.57079632679489661923;
    static constexpr auto pi_4 = 0.785398163397448309616;
    static constexpr auto tau = pi * 2.0;
};

/*!
 * Calculate a sigmoid function of a given value.
 * A sigmoid function is used to clip any value between 0.0 and 1.0 trough a curve.
 * This is commonly used for weights in neural networks.
 * \param[in] value - Value
 * \return Sigmoid curve value between 0 and 1.
 */
template <typename T>
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
template <typename T, typename... U>
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
template <typename T, typename... U>
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
template <typename T>
[[nodiscard]] inline constexpr auto constexpr_pow(const T base, const int exponent) noexcept -> T
{
    static_assert(std::is_arithmetic_v<T>, "Base must be arithmetic type.");

    auto val = base;

    for (auto i = 1; i < exponent; ++i)
        val *= base;

    return val;
}

/*!
 * Calculate whether the difference between a and b is smaller than the acceptable error (epsilon),
 * determined by the larger of a or b. This means that the two values are "close enough", and we can say that they're
 * approximately equal. From The art of computer programming by Knuth
 */
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
[[nodiscard]] inline constexpr auto approximately_equal(const T a, const T b,
                                                        const T epsilon = std::numeric_limits<T>::epsilon()) noexcept
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
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
[[nodiscard]] inline constexpr auto essentially_equal(const T a, const T b,
                                                      const T epsilon = std::numeric_limits<T>::epsilon()) noexcept
    -> bool
{
    const auto abs_a = std::abs(a);
    const auto abs_b = std::abs(b);
    return std::abs(a - b) <= ((abs_a > abs_b ? abs_b : abs_a) * epsilon);
}

} // namespace aeon::math

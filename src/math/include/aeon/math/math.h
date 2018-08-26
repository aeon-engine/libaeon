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

/*!
 * \file
 * \brief Common mathematical constants and functions.
 */

#pragma once

#include <type_traits>
#include <cmath>

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
inline auto sigmoid(const T value) noexcept -> T
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
inline auto min(const T first, const U... values) noexcept -> T
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
inline auto max(const T first, const U... values) noexcept -> T
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
inline constexpr auto constexpr_pow(const T base, const int exponent) noexcept -> T
{
    static_assert(std::is_arithmetic_v<T>, "Base must be arithmetic type.");

    auto val = base;

    for (auto i = 1; i < exponent; ++i)
        val *= base;

    return val;
}

} // namespace aeon::math

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

#include <aeon/math/math.h>
#include <aeon/math/impl/units_magnitudes_impl.h>
#include <type_traits>

namespace aeon::math
{

template <typename param1_t, typename param2_t>
template <typename value_type_t, std::enable_if_t<std::is_arithmetic_v<value_type_t>> *>
inline constexpr unit<param1_t, param2_t>::unit(const value_type_t value) noexcept
{
    set_absolute_value(static_cast<double>(value));
}

template <typename param1_t, typename param2_t>
template <typename value_type_t, std::enable_if_t<std::is_arithmetic_v<value_type_t>> *>
inline constexpr auto unit<param1_t, param2_t>::operator=(const value_type_t value) noexcept -> unit &
{
    set_absolute_value(static_cast<double>(value));
    return *this;
}

template <typename param1_t, typename param2_t>
template <typename T, typename U>
inline constexpr unit<param1_t, param2_t>::unit(const unit<T, U> &other) noexcept
    : value_{other.base_unit_count()}
{
    static_assert(unit_is_same_type_v<unit_t, unit_type_t<T, U>>, "Units must be of the same type.");
}

template <typename param1_t, typename param2_t>
template <typename T, typename U>
inline constexpr auto unit<param1_t, param2_t>::operator=(const unit<T, U> &other) noexcept -> unit &
{
    static_assert(unit_is_same_type_v<unit_t, unit_type_t<T, U>>, "Units must be of the same type.");
    value_ = other.base_unit_count();
    return *this;
}

template <typename param1_t, typename param2_t>
inline constexpr auto unit<param1_t, param2_t>::count() const noexcept -> double
{
    if constexpr (is_base_type_v<unit_t>)
    {
        return value_ / prefix_value_v<param1_t>;
    }
    else
    {
        return (value_ * unit_t::value) / prefix_value_v<param1_t>;
    }
}

template <typename param1_t, typename param2_t>
template <typename value_type_t>
inline constexpr auto unit<param1_t, param2_t>::count(std::enable_if_t<std::is_arithmetic_v<value_type_t>> *) const
    noexcept -> value_type_t
{
    return static_cast<value_type_t>(count());
}

template <typename param1_t, typename param2_t>
inline constexpr unit<param1_t, param2_t>::operator double() const noexcept
{
    return count();
}

template <typename param1_t, typename param2_t>
inline constexpr auto unit<param1_t, param2_t>::base_unit_count() const noexcept -> double
{
    return value_;
}

template <typename param1_t, typename param2_t>
inline constexpr unit<param1_t, param2_t>::unit(const double value, const internal::unit_value_placeholder_t)
    : value_{value}
{
}

template <typename param1_t, typename param2_t>
inline constexpr void unit<param1_t, param2_t>::set_absolute_value(const double value)
{
    if constexpr (is_base_type_v<unit_t>)
    {
        value_ = value;
    }
    else
    {
        value_ = value / unit_t::value;
    }

    value_ *= prefix_value_v<param1_t>;
}

template <typename T, typename U>
auto constexpr operator+(const unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U>
{
    return {lhs.value_ + rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename T, typename U>
auto constexpr operator+=(unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T, typename U, typename value_type_t>
auto constexpr operator+(const unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U>
{
    return {lhs.value_ + (static_cast<double>(rhs) * prefix_value_v<T>), internal::unit_value_placeholder_t{}};
}

template <typename T, typename U, typename value_type_t>
auto constexpr operator+=(unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T, typename U, typename V, typename W>
auto constexpr operator+(const unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U>
{
    static_assert(unit_is_same_type_v<unit_type_t<T, U>, unit_type_t<V, W>>, "Units must be of the same type.");
    return {lhs.value_ + rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename T, typename U, typename V, typename W>
auto constexpr operator+=(unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T, typename U>
auto constexpr operator-(const unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U>
{
    return {lhs.value_ - rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename T, typename U>
auto constexpr operator-=(unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T, typename U, typename value_type_t>
auto constexpr operator-(const unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U>
{
    return {lhs.value_ - (static_cast<double>(rhs) * prefix_value_v<T>), internal::unit_value_placeholder_t{}};
}

template <typename T, typename U, typename value_type_t>
auto constexpr operator-=(unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T, typename U, typename V, typename W>
auto constexpr operator-(const unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U>
{
    static_assert(unit_is_same_type_v<unit_type_t<T, U>, unit_type_t<V, W>>, "Units must be of the same type.");
    return {lhs.value_ - rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename T, typename U, typename V, typename W>
auto constexpr operator-=(unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U> &
{
    lhs = lhs - rhs;
    return lhs;
}

} // namespace aeon::math

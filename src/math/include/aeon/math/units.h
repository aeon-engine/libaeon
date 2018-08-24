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

#include <aeon/math/impl/units_prefixes.h>
#include <aeon/math/impl/units_traits_impl.h>
#include <type_traits>

namespace aeon::math
{

namespace internal
{

struct unit_value_placeholder_t
{
};

} // namespace internal

template <typename param1_t, typename param2_t = void>
class unit
{
    using unit_t = std::conditional_t<std::is_same_v<param2_t, void>, param1_t, param2_t>;
    static_assert(
        std::conditional_t<std::is_base_of_v<prefix, param1_t>, typename unit_t::has_prefix, std::true_type>(),
        "Only SI units can have a prefix.");

public:
    template <typename value_type_t, std::enable_if_t<std::is_arithmetic_v<value_type_t>> * = nullptr>
    constexpr unit(const value_type_t value) noexcept;

    template <typename value_type_t, std::enable_if_t<std::is_arithmetic_v<value_type_t>> * = nullptr>
    constexpr auto operator=(const value_type_t value) noexcept -> unit &;

    template <typename T, typename U>
    constexpr unit(const unit<T, U> &other) noexcept;

    template <typename T, typename U>
    constexpr auto operator=(const unit<T, U> &other) noexcept -> unit &;

    ~unit() = default;

    constexpr auto count() const noexcept -> double;

    template <typename value_type_t>
    constexpr auto count(std::enable_if_t<std::is_arithmetic_v<value_type_t>> * = nullptr) const noexcept
        -> value_type_t;

    constexpr operator double() const noexcept;

    constexpr auto base_unit_count() const noexcept -> double;

    constexpr unit(const unit &) = default;
    constexpr auto operator=(const unit &) -> unit & = default;

    constexpr unit(unit &&) = default;
    constexpr auto operator=(unit &&) -> unit & = default;

    template <typename T, typename U>
    friend constexpr auto operator+(const unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U>;

    template <typename T, typename U>
    friend constexpr auto operator+=(unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U> &;

    template <typename T, typename U, typename value_type_t>
    friend constexpr auto operator+(const unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U>;

    template <typename T, typename U, typename value_type_t>
    friend constexpr auto operator+=(unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U> &;

    template <typename T, typename U, typename V, typename W>
    friend constexpr auto operator+(const unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U>;

    template <typename T, typename U, typename V, typename W>
    friend constexpr auto operator+=(unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U> &;

    template <typename T, typename U>
    friend constexpr auto operator-(const unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U>;

    template <typename T, typename U>
    friend constexpr auto operator-=(unit<T, U> &lhs, const unit<T, U> &rhs) noexcept -> unit<T, U> &;

    template <typename T, typename U, typename value_type_t>
    friend constexpr auto operator-(const unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U>;

    template <typename T, typename U, typename value_type_t>
    friend constexpr auto operator-=(unit<T, U> &lhs, const value_type_t &rhs) noexcept -> unit<T, U> &;

    template <typename T, typename U, typename V, typename W>
    friend constexpr auto operator-(const unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U>;

    template <typename T, typename U, typename V, typename W>
    friend constexpr auto operator-=(unit<T, U> &lhs, const unit<V, W> &rhs) noexcept -> unit<T, U> &;

private:
    constexpr unit(const double value, const internal::unit_value_placeholder_t);

    constexpr void set_absolute_value(const double value);

    double value_;
};

} // namespace aeon::math

#include <aeon/math/impl/units_impl.h>

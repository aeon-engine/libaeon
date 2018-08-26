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

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
class unit_base
{
    static_assert(std::conditional_t<std::is_base_of_v<prefix, prefix_type_t>, typename unit_type_t::has_prefix,
                                     std::true_type>(),
                  "Only SI units can have a prefix.");

public:
    template <typename conversion_value_type_t,
              std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> * = nullptr>
    constexpr unit_base(const conversion_value_type_t value) noexcept;

    template <typename conversion_value_type_t,
              std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> * = nullptr>
    constexpr auto operator=(const conversion_value_type_t value) noexcept -> unit_base &;

    template <typename other_prefix_type_t, typename other_unit_type_t>
    constexpr unit_base(const unit_base<other_prefix_type_t, other_unit_type_t, unit_value_type_t> &other) noexcept;

    template <typename other_prefix_type_t, typename other_unit_type_t>
    constexpr auto operator=(const unit_base<other_prefix_type_t, other_unit_type_t, unit_value_type_t> &other) noexcept
        -> unit_base &;

    ~unit_base() = default;

    constexpr auto count() const noexcept -> unit_value_type_t;

    template <typename conversion_value_type_t>
    constexpr auto count(std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> * = nullptr) const noexcept
        -> conversion_value_type_t;

    constexpr operator unit_value_type_t() const noexcept;

    constexpr auto base_unit_count() const noexcept -> unit_value_type_t;

    constexpr unit_base(const unit_base &) = default;
    constexpr auto operator=(const unit_base &) -> unit_base & = default;

    constexpr unit_base(unit_base &&) = default;
    constexpr auto operator=(unit_base &&) -> unit_base & = default;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto operator+(
        const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
        const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto operator+=(
        unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
        const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
              typename operator_value_type_t>
    friend constexpr auto
        operator+(const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                  const operator_value_type_t &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
              typename operator_value_type_t>
    friend constexpr auto
        operator+=(unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                   const operator_value_type_t &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &;

    template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t,
              typename rhs_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto
        operator+(const unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                  const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t>;

    template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t,
              typename rhs_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto
        operator+=(unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                   const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto operator-(
        const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
        const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto operator-=(
        unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
        const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
              typename operator_value_type_t>
    friend constexpr auto
        operator-(const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                  const operator_value_type_t &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>;

    template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
              typename operator_value_type_t>
    friend constexpr auto
        operator-=(unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                   const operator_value_type_t &rhs) noexcept
        -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &;

    template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t,
              typename rhs_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto
        operator-(const unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                  const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t>;

    template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t,
              typename rhs_unit_type_t, typename operator_unit_value_type_t>
    friend constexpr auto
        operator-=(unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                   const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
        -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &;

private:
    constexpr unit_base(const unit_value_type_t value, const internal::unit_value_placeholder_t);

    constexpr void set_absolute_value(const unit_value_type_t value);

    unit_value_type_t value_;
};

template <typename T, typename U = void>
using unitd = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, double>;

template <typename T, typename U = void>
using unitf = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, float>;

template <typename T, typename U = void>
using uniti = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, int>;

template <typename T, typename U = void>
using unitll = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, long long>;

template <typename T, typename U = void>
using unit = unitd<T, U>;

} // namespace aeon::math

#include <aeon/math/impl/units_impl.h>

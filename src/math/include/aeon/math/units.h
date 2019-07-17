// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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

    [[nodiscard]] constexpr auto count() const noexcept -> unit_value_type_t;

    template <typename conversion_value_type_t>
    constexpr auto count(std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> * = nullptr) const noexcept
        -> conversion_value_type_t;

    constexpr operator unit_value_type_t() const noexcept;

    [[nodiscard]] constexpr auto base_unit_count() const noexcept -> unit_value_type_t;

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

/*!
 * Unit type with a double as underlying data size.
 * Recommended when using large scale units such as light-year and AU.
 */
template <typename T, typename U = void>
using unitd = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, double>;

/*!
 * Unit type with a float as underlying data size.
 * Recommended for normal use.
 */
template <typename T, typename U = void>
using unitf = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, float>;

/*!
 * Unit type with an int as underlying data size.
 * Warning: Most units will not convert well with int types. This can only realistically
 * be used with bytes (megabyte to bytes etc.)
 */
template <typename T, typename U = void>
using uniti = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, int>;

/*!
 * Unit type with a long long as underlying data size.
 * Warning: Most units will not convert well with long long types. This can only realistically
 * be used with bytes (megabyte to bytes etc.)
 */
template <typename T, typename U = void>
using unitll = unit_base<unit_prefix_t<T, U>, unit_type_t<T, U>, long long>;

/*!
 * Unit type with a double as underlying data size.
 * Recommended when using large scale units such as light-year and AU.
 */
template <typename T, typename U = void>
using unit = unitd<T, U>;

} // namespace aeon::math

#include <aeon/math/impl/units_impl.h>

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/math.h>
#include <aeon/math/impl/units_magnitudes_impl.h>
#include <type_traits>

namespace aeon::math
{

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
template <typename conversion_value_type_t, std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> *>
inline constexpr unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::unit_base(
    const conversion_value_type_t value) noexcept
{
    set_absolute_value(static_cast<unit_value_type_t>(value));
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
template <typename conversion_value_type_t, std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> *>
inline constexpr auto
    unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::operator=(const conversion_value_type_t value) noexcept
    -> unit_base &
{
    set_absolute_value(static_cast<unit_value_type_t>(value));
    return *this;
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
template <typename other_prefix_type_t, typename other_unit_type_t>
inline constexpr unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::unit_base(
    const unit_base<other_prefix_type_t, other_unit_type_t, unit_value_type_t> &other) noexcept
    : value_{other.base_unit_count()}
{
    static_assert(unit_is_same_type_v<unit_type_t, other_unit_type_t>, "Units must be of the same type.");
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
template <typename other_prefix_type_t, typename other_unit_type_t>
inline constexpr auto unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::operator=(
    const unit_base<other_prefix_type_t, other_unit_type_t, unit_value_type_t> &other) noexcept -> unit_base &
{
    static_assert(unit_is_same_type_v<unit_type_t, other_unit_type_t>, "Units must be of the same type.");
    value_ = other.base_unit_count();
    return *this;
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
inline constexpr auto unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::count() const noexcept
    -> unit_value_type_t
{
    return units_convert_magnitude<unit_type_t, unit_value_type_t>::from_base_type(value_) /
           static_cast<unit_value_type_t>(prefix_value_v<prefix_type_t>);
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
template <typename conversion_value_type_t>
inline constexpr auto unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::count(
    std::enable_if_t<std::is_arithmetic_v<conversion_value_type_t>> *) const noexcept -> conversion_value_type_t
{
    return static_cast<conversion_value_type_t>(count());
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
inline constexpr unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::operator unit_value_type_t() const noexcept
{
    return count();
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
inline constexpr auto unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::base_unit_count() const noexcept
    -> unit_value_type_t
{
    return value_;
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
inline constexpr unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::unit_base(
    const unit_value_type_t value, const internal::unit_value_placeholder_t)
    : value_{value}
{
}

template <typename prefix_type_t, typename unit_type_t, typename unit_value_type_t>
inline constexpr void
    unit_base<prefix_type_t, unit_type_t, unit_value_type_t>::set_absolute_value(const unit_value_type_t value)
{
    value_ = units_convert_magnitude<unit_type_t, unit_value_type_t>::to_base_type(value) *
             static_cast<unit_value_type_t>(prefix_value_v<prefix_type_t>);
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename unit_value_type_t>
auto constexpr operator+(const unit_base<operator_prefix_type_t, operator_unit_type_t, unit_value_type_t> &lhs,
                         const unit_base<operator_prefix_type_t, operator_unit_type_t, unit_value_type_t> &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, unit_value_type_t>
{
    return {lhs.value_ + rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename unit_value_type_t>
auto constexpr
    operator+=(unit_base<operator_prefix_type_t, operator_unit_type_t, unit_value_type_t> &lhs,
               const unit_base<operator_prefix_type_t, operator_unit_type_t, unit_value_type_t> &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, unit_value_type_t> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
          typename operator_value_type_t>
auto constexpr operator+(const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                         const operator_value_type_t &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>
{
    return {lhs.value_ + (static_cast<operator_unit_value_type_t>(rhs) * prefix_value_v<operator_prefix_type_t>),
            internal::unit_value_placeholder_t{}};
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
          typename operator_value_type_t>
auto constexpr operator+=(unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                          const operator_value_type_t &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t, typename rhs_unit_type_t,
          typename operator_unit_value_type_t>
auto constexpr operator+(const unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                         const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
    -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t>
{
    static_assert(unit_is_same_type_v<lhs_unit_type_t, rhs_unit_type_t>, "Units must be of the same type.");
    return {lhs.value_ + rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t, typename rhs_unit_type_t,
          typename operator_unit_value_type_t>
auto constexpr operator+=(unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                          const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
    -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t>
auto constexpr
    operator-(const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
              const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>
{
    return {lhs.value_ - rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t>
auto constexpr
    operator-=(unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
               const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
          typename operator_value_type_t>
auto constexpr operator-(const unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                         const operator_value_type_t &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t>
{
    return {lhs.value_ - (static_cast<operator_unit_value_type_t>(rhs) * prefix_value_v<operator_prefix_type_t>),
            internal::unit_value_placeholder_t{}};
}

template <typename operator_prefix_type_t, typename operator_unit_type_t, typename operator_unit_value_type_t,
          typename operator_value_type_t>
auto constexpr operator-=(unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &lhs,
                          const operator_value_type_t &rhs) noexcept
    -> unit_base<operator_prefix_type_t, operator_unit_type_t, operator_unit_value_type_t> &
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t, typename rhs_unit_type_t,
          typename operator_unit_value_type_t>
auto constexpr operator-(const unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                         const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
    -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t>
{
    static_assert(unit_is_same_type_v<lhs_unit_type_t, rhs_unit_type_t>, "Units must be of the same type.");
    return {lhs.value_ - rhs.value_, internal::unit_value_placeholder_t{}};
}

template <typename lhs_prefix_type_t, typename lhs_unit_type_t, typename rhs_prefix_type_t, typename rhs_unit_type_t,
          typename operator_unit_value_type_t>
auto constexpr operator-=(unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &lhs,
                          const unit_base<rhs_prefix_type_t, rhs_unit_type_t, operator_unit_value_type_t> &rhs) noexcept
    -> unit_base<lhs_prefix_type_t, lhs_unit_type_t, operator_unit_value_type_t> &
{
    lhs = lhs - rhs;
    return lhs;
}

} // namespace aeon::math

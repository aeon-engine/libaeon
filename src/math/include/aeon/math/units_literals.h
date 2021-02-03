// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/units.h>

inline constexpr auto operator"" _m(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _m(const long double val) noexcept -> aeon::math::unit<aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _mm(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::milli, aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _mm(const long double val) noexcept
    -> aeon::math::unit<aeon::math::milli, aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _cm(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::centi, aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _cm(const long double val) noexcept
    -> aeon::math::unit<aeon::math::centi, aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _km(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::kilo, aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _km(const long double val) noexcept
    -> aeon::math::unit<aeon::math::kilo, aeon::math::meter>
{
    return {val};
}

inline constexpr auto operator"" _inch(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::inch>
{
    return {val};
}

inline constexpr auto operator"" _inch(const long double val) noexcept -> aeon::math::unit<aeon::math::inch>
{
    return {val};
}

inline constexpr auto operator"" _au(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::astronomical_unit>
{
    return {val};
}

inline constexpr auto operator"" _au(const long double val) noexcept -> aeon::math::unit<aeon::math::astronomical_unit>
{
    return {val};
}

inline constexpr auto operator"" _g(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::gram>
{
    return {val};
}

inline constexpr auto operator"" _g(const long double val) noexcept -> aeon::math::unit<aeon::math::gram>
{
    return {val};
}

inline constexpr auto operator"" _kg(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::kilo, aeon::math::gram>
{
    return {val};
}

inline constexpr auto operator"" _kg(const long double val) noexcept
    -> aeon::math::unit<aeon::math::kilo, aeon::math::gram>
{
    return {val};
}

inline constexpr auto operator"" _lbs(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::pound>
{
    return {val};
}

inline constexpr auto operator"" _lbs(const long double val) noexcept -> aeon::math::unit<aeon::math::pound>
{
    return {val};
}

inline constexpr auto operator"" _bytes(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _bytes(const long double val) noexcept -> aeon::math::unit<aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _KiB(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::kibi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _KiB(const long double val) noexcept
    -> aeon::math::unit<aeon::math::kibi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _MiB(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::mebi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _MiB(const long double val) noexcept
    -> aeon::math::unit<aeon::math::mebi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _GiB(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::gibi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _GiB(const long double val) noexcept
    -> aeon::math::unit<aeon::math::gibi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _TiB(const unsigned long long val) noexcept
    -> aeon::math::unit<aeon::math::tebi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _TiB(const long double val) noexcept
    -> aeon::math::unit<aeon::math::tebi, aeon::math::byte>
{
    return {val};
}

inline constexpr auto operator"" _K(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::kelvin>
{
    return {val};
}

inline constexpr auto operator"" _K(const long double val) noexcept -> aeon::math::unit<aeon::math::kelvin>
{
    return {val};
}

inline constexpr auto operator"" _C(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::celsius>
{
    return {val};
}

inline constexpr auto operator"" _C(const long double val) noexcept -> aeon::math::unit<aeon::math::celsius>
{
    return {val};
}

inline constexpr auto operator"" _F(const unsigned long long val) noexcept -> aeon::math::unit<aeon::math::fahrenheit>
{
    return {val};
}

inline constexpr auto operator"" _F(const long double val) noexcept -> aeon::math::unit<aeon::math::fahrenheit>
{
    return {val};
}

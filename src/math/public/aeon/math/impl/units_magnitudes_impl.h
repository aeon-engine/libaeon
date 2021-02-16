// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/impl/units_tags_impl.h>
#include <aeon/math/math.h>
#include <type_traits>

namespace aeon::math
{

struct meter
{
    using type = unit_distance_tag;
    using has_prefix = std::true_type;
};

struct angstrom
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 10000000000.0;
};

struct micron
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 1000000.0;
};

struct mil
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 39370.0787;
};

struct inch
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 39.3700787;
};

struct mile
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 1.0 / 16093.440;
};

struct nautical_mile
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 1.0 / 1852.0;
};

struct lightyear
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 1.0 / 9.4605284e15;
};

struct astronomical_unit
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 1.0 / 149597870700.0;
};

struct gram
{
    using type = unit_mass_tag;
    using has_prefix = std::true_type;
};

struct pound
{
    using type = unit_mass_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 1.0 / 453.59237;
};

struct kelvin
{
    using type = unit_temperature_tag;
    using has_prefix = std::false_type;
};

struct celsius
{
    using type = unit_temperature_tag;
    using has_prefix = std::false_type;
    static constexpr auto offset = -273.15;
};

struct fahrenheit
{
    using type = unit_temperature_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 9.0 / 5.0;
    static constexpr auto offset = -459.67;
};

struct radian
{
    using type = unit_angle_tag;
    using has_prefix = std::false_type;
};

struct degree
{
    using type = unit_angle_tag;
    using has_prefix = std::false_type;
    static constexpr auto multiplier = 180.0 / constants<double>::pi;
};

struct byte
{
    using type = computer_storage_tag;
    using has_prefix = std::true_type;
};

template <typename unit_t, typename unit_value_type_t>
struct units_convert_magnitude
{
    static constexpr auto to_base_type(const unit_value_type_t value) noexcept -> unit_value_type_t
    {
        if constexpr (is_base_type_v<unit_t>)
        {
            return value;
        }
        else
        {
            auto val = value;

            if constexpr (type_has_offset_value_v<unit_t>)
                val -= static_cast<unit_value_type_t>(unit_t::offset);

            if constexpr (type_has_multiplier_value_v<unit_t>)
                val /= static_cast<unit_value_type_t>(unit_t::multiplier);

            return val;
        }
    }

    static constexpr auto from_base_type(const unit_value_type_t value) noexcept -> unit_value_type_t
    {
        if constexpr (is_base_type_v<unit_t>)
        {
            return value;
        }
        else
        {
            auto val = value;

            if constexpr (type_has_multiplier_value_v<unit_t>)
                val *= static_cast<unit_value_type_t>(unit_t::multiplier);

            if constexpr (type_has_offset_value_v<unit_t>)
                val += static_cast<unit_value_type_t>(unit_t::offset);

            return val;
        }
    }
};

} // namespace aeon::math

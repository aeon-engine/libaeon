// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::math
{

struct meter;

struct unit_distance_tag
{
    using base_type = meter;
};

struct gram;

struct unit_mass_tag
{
    using base_type = gram;
};

struct kelvin;

struct unit_temperature_tag
{
    using base_type = kelvin;
};

struct radian;

struct unit_angle_tag
{
    using base_type = radian;
};

struct byte;

struct computer_storage_tag
{
    using base_type = byte;
};

} // namespace aeon::math

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

#include <aeon/math/impl/units_tags_impl.h>
#include <type_traits>

namespace aeon::math
{

struct meter
{
    using type = unit_distance_tag;
    using has_prefix = std::true_type;
    static constexpr auto value = 1.0;
};

struct angstrom
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 10000000000.0;
};

struct micron
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 1000000.0;
};

struct mil
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 39370.0787;
};

struct inch
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 39.3700787;
};

struct mile
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 1.0 / 16093.440;
};

struct nautical_mile
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 1.0 / 1852.0;
};

struct lightyear
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 1.0 / 9.4605284e15;
};

struct astronomical_unit
{
    using type = unit_distance_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 1.0 / 149597870700.0;
};

struct gram
{
    using type = unit_mass_tag;
    using has_prefix = std::true_type;
    static constexpr auto value = 1.0;
};

struct pound
{
    using type = unit_mass_tag;
    using has_prefix = std::false_type;
    static constexpr auto value = 1.0 / 453.59237;
};

struct byte
{
    using type = computer_storage_tag;
    using has_prefix = std::true_type;
    static constexpr auto value = 1.0;
};

} // namespace aeon::math

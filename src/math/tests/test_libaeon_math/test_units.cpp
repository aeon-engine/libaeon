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

#include <gtest/gtest.h>
#include <aeon/math/units.h>
#include <aeon/math/units_literals.h>
#include <aeon/math/vector2.h>

using namespace aeon;

TEST(test_units, test_units_something)
{
    EXPECT_TRUE((math::unit_is_same_type_v<math::meter, math::inch>));
    EXPECT_FALSE((math::unit_is_same_type_v<math::meter, math::gram>));
    EXPECT_TRUE((math::unit_is_same_type_v<math::pound, math::gram>));
}

TEST(test_units, test_units_length_conversion)
{
    const math::unit<math::meter> a = 3;
    const math::unit<math::inch> b = a;

    EXPECT_DOUBLE_EQ(b.count(), 118.11023610000001);

    const math::unit<math::astronomical_unit> distance_to_sun = 1;
    const math::unit<math::meter> distance_to_sun_in_meters = distance_to_sun;

    // 1 AU = 149.597.870.700 meters exact.
    EXPECT_DOUBLE_EQ(distance_to_sun_in_meters.count(), 149597870700.0);

    const math::unit<math::kilo, math::meter> distance_to_sun_in_kilometers = distance_to_sun;
    EXPECT_DOUBLE_EQ(distance_to_sun_in_kilometers.count(), 149597870.7);

    const math::unit<math::gram> kg = 1000;
    const math::unit<math::pound> kg_in_pound = kg;
    EXPECT_DOUBLE_EQ(kg_in_pound.count(), 2.2046226218487757);
}

TEST(test_units, test_units_length_conversion_prefixes)
{
    const math::unit<math::kilo, math::meter> a = 3;
    const math::unit<math::meter> b = a;

    EXPECT_DOUBLE_EQ(b.count(), 3000.0);

    const math::unit<math::centi, math::meter> c = 100.0;
    const math::unit<math::meter> d = c;

    EXPECT_DOUBLE_EQ(d.count(), 1.0);

    const math::unit<math::kilo, math::meter> e = d;
    EXPECT_DOUBLE_EQ(e.count(), 0.001);

    const math::unit<math::centi, math::meter> c2 = e;
    EXPECT_DOUBLE_EQ(c2.count(), 100.0);
}

TEST(test_units, test_units_storage_prefixes)
{
    const auto kilobyte = 1_KiB;
    EXPECT_DOUBLE_EQ(math::unit<math::byte>{kilobyte}, 1024.0);
}

TEST(test_units, test_units_km_to_cm)
{
    const math::unit<math::kilo, math::meter> a = 1;
    const math::unit<math::centi, math::meter> b = a;

    EXPECT_DOUBLE_EQ(b.count(), 100000.0);

    const math::unit<math::kilo, math::meter> c = b;

    EXPECT_DOUBLE_EQ(c.count(), 1.0);
}

TEST(test_units, test_units_kg_to_g_to_pounds)
{
    const auto a = 100_kg;
    const math::unit<math::gram> b = a;
    EXPECT_DOUBLE_EQ(b, 100000.0);

    const math::unit<math::pound> c = b;
    EXPECT_DOUBLE_EQ(c, 220.46226218487757);

    const auto d = 50_lbs;
    const math::unit<math::kilo, math::gram> e = d;
    EXPECT_DOUBLE_EQ(e, 22.6796185);
}

TEST(test_units, test_units_bytes_conversion_prefixes)
{
    const math::unit<math::kibi, math::byte> a = 3;
    const math::unit<math::byte> b = a;

    EXPECT_DOUBLE_EQ(b.count(), 3072.0);

    const math::unit<math::mebi, math::byte> c = 1;
    const math::unit<math::kibi, math::byte> d = c;

    EXPECT_DOUBLE_EQ(d.count(), 1024.0);
}

TEST(test_units, test_units_km_to_cm_assignment)
{
    math::unit<math::kilo, math::meter> a = 99999;
    a = 1.0;

    math::unit<math::centi, math::meter> b = 99999;
    b = a;

    EXPECT_DOUBLE_EQ(b.count(), 100000.0);

    const math::unit<math::kilo, math::meter> c = b;

    EXPECT_DOUBLE_EQ(c.count(), 1.0);
}

TEST(test_units, test_units_convert_count)
{
    const math::unit<math::kilo, math::meter> a = 1.0;
    const math::unit<math::centi, math::meter> b = a;

    EXPECT_FLOAT_EQ(b.count<float>(), 100000.0f);
    EXPECT_EQ(b.count<int>(), 100000);
}

TEST(test_units, test_units_convert_to_pod)
{
    const math::unit<math::kilo, math::meter> a = 1.0;
    const math::unit<math::centi, math::meter> b = a;

    const double c = b;
    EXPECT_DOUBLE_EQ(c, 100000.0);
}

TEST(test_units, test_units_convert_from_pod)
{
    const math::unit<math::kilo, math::meter> a = 1;
    const math::unit<math::centi, math::meter> b = a;

    EXPECT_DOUBLE_EQ(b.count(), 100000.0);

    const math::unit<math::kilo, math::meter> c = 1.0f;
    const math::unit<math::centi, math::meter> d = c;

    EXPECT_DOUBLE_EQ(d.count(), 100000.0);

    math::unit<math::kilo, math::meter> e = 9999;
    e = 1.0f;
    const math::unit<math::centi, math::meter> f = e;
    EXPECT_DOUBLE_EQ(f.count(), 100000.0);
}

TEST(test_units, test_units_addition)
{
    const math::unit<math::kilo, math::meter> a = 1.0;
    const math::unit<math::kilo, math::meter> b = 3.5;

    const auto c = a + b;

    EXPECT_DOUBLE_EQ(c.count(), 4.5);

    const math::unit<math::meter> d = c;
    EXPECT_DOUBLE_EQ(d, 4500.0);

    auto e = a + b;
    e += math::unit<math::kilo, math::meter>{1.0};
    // 3937 inch is about 100 meter
    e += math::unit<math::inch>{3937.0};
    e += 5.0;
    e += 2;
    e += 1.0f;

    EXPECT_DOUBLE_EQ(e, 13.5999998001019993);
}

TEST(test_units, test_units_subtraction)
{
    const math::unit<math::kilo, math::meter> a = 10.0;
    const math::unit<math::kilo, math::meter> b = 2.5;

    const auto c = a - b;

    EXPECT_DOUBLE_EQ(c.count(), 7.5);

    const math::unit<math::meter> d = c;
    EXPECT_DOUBLE_EQ(d, 7500.0);

    auto e = a - b;
    e -= math::unit<math::kilo, math::meter>{1.0};
    // 3937 inch is about 100 meter
    e -= math::unit<math::inch>{3937.0};
    e -= 0.5;
    e -= 2;
    e -= 1.0f;

    EXPECT_DOUBLE_EQ(e, 2.9000001998980007);
}

TEST(test_units, test_units_other_math_types)
{
    const math::vector2 vec{4.0_km, 5.0_km};
    const auto vector_length = math::length(vec);
    EXPECT_DOUBLE_EQ(vector_length, 6.4031242374328485);

    const math::vector2<math::unit<math::kilo, math::meter>> vec2{6.0, 7.0};
    const auto vec3 = vec + vec2;

    EXPECT_DOUBLE_EQ(vec3.x, 10.0);
    EXPECT_DOUBLE_EQ(vec3.y, 12.0);

    const math::vector2<math::unit<math::meter>> vec4{vec3};

    EXPECT_DOUBLE_EQ(vec4.x, 10000.0);
    EXPECT_DOUBLE_EQ(vec4.y, 12000.0);
}

TEST(test_units, test_units_literals)
{
    const auto meters = 10.0_m;
    EXPECT_DOUBLE_EQ(meters, 10.0);
}

TEST(test_units, test_units_offset_multiplier)
{
    const auto celsius_temperature = 30.0_C;
    const math::unit<math::kelvin> kelvin_temperature = celsius_temperature;
    EXPECT_DOUBLE_EQ(kelvin_temperature, 303.15);

    const math::unit<math::fahrenheit> fahrenheit_temperature = celsius_temperature;
    EXPECT_DOUBLE_EQ(fahrenheit_temperature, 86.0);

    const auto a = 300_K;
    const math::unit<math::fahrenheit> b = a;
    EXPECT_DOUBLE_EQ(b, 80.33);
}

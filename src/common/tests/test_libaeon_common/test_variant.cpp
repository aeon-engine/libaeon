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
#include <aeon/common/variant.h>

TEST(test_variant, test_variant_default_create)
{
    aeon::common::variant v;

    ASSERT_EQ(0, v.int_value());
    ASSERT_EQ(false, v.bool_value());
    ASSERT_EQ("", v.string_value());
    ASSERT_FLOAT_EQ(0.0f, v.float_value());
    ASSERT_EQ(aeon::common::variant::variant_type::variant_nil, v.type());
}

TEST(test_variant, test_variant_create_int_type)
{
    aeon::common::variant v = 42;

    ASSERT_EQ(42, v.int_value());
    ASSERT_EQ(true, v.bool_value());
    ASSERT_EQ("42", v.string_value());
    ASSERT_FLOAT_EQ(42.0f, v.float_value());
    ASSERT_EQ(aeon::common::variant::variant_type::variant_int, v.type());
}

TEST(test_variant, test_variant_create_bool_true_type)
{
    aeon::common::variant v = true;

    ASSERT_EQ(1, v.int_value());
    ASSERT_EQ(true, v.bool_value());
    ASSERT_EQ("true", v.string_value());
    ASSERT_FLOAT_EQ(1.0f, v.float_value());
    ASSERT_EQ(aeon::common::variant::variant_type::variant_bool, v.type());
}

TEST(test_variant, test_variant_create_bool_false_type)
{
    aeon::common::variant v = false;

    ASSERT_EQ(0, v.int_value());
    ASSERT_EQ(false, v.bool_value());
    ASSERT_EQ("false", v.string_value());
    ASSERT_FLOAT_EQ(0.0f, v.float_value());
    ASSERT_EQ(aeon::common::variant::variant_type::variant_bool, v.type());
}

// TODO: Improve unittests for variant.

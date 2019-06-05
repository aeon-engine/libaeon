// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/variant.h>
#include <gtest/gtest.h>

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

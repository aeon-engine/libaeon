// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#define AEON_IGNORE_DEPRECATED
#include <aeon/common/optional.h>
#include <aeon/common/unused.h>
#include <aeon/common/compilers.h>

AEON_IGNORE_VS_WARNING(4189)

TEST(test_optional, test_optional_create_int)
{
    aeon::common::optional<int> test;
    ASSERT_FALSE(test.has_value());
}

TEST(test_optional, test_optional_create_float)
{
    aeon::common::optional<float> test;
    ASSERT_FALSE(test.has_value());
}

TEST(test_optional, test_optional_create_string)
{
    aeon::common::optional<std::string> test;
    ASSERT_FALSE(test.has_value());
}

TEST(test_optional, test_optional_create_int_with_value)
{
    aeon::common::optional test = 1337;
    ASSERT_TRUE(test.has_value());

    int testvalue = test;
    ASSERT_EQ(1337, testvalue);
}

TEST(test_optional, test_optional_create_float_with_value)
{
    aeon::common::optional test = 1337.0f;
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_create_string_with_value)
{
    aeon::common::optional test = std::string("1337!");
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_change_int_value)
{
    aeon::common::optional test = 1337;
    ASSERT_TRUE(test.has_value());

    test = 1338;
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_change_int_value2)
{
    aeon::common::optional<int> test;
    ASSERT_FALSE(test.has_value());

    test = 1338;
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_change_float_value)
{
    aeon::common::optional test = 1337.0f;
    ASSERT_TRUE(test.has_value());

    test = 1338.1f;
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_change_float_value2)
{
    aeon::common::optional<float> test;
    ASSERT_FALSE(test.has_value());

    test = 1338.1f;
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_change_string_value)
{
    aeon::common::optional test = std::string("1337!");
    ASSERT_TRUE(test.has_value());

    test = std::string("42?");
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_change_string_value2)
{
    aeon::common::optional<std::string> test;
    ASSERT_FALSE(test.has_value());

    test = std::string("42?");
    ASSERT_TRUE(test.has_value());
}

TEST(test_optional, test_optional_reset_int)
{
    aeon::common::optional test = 3;
    ASSERT_TRUE(test.has_value());

    test.reset();
    ASSERT_FALSE(test.has_value());
}

TEST(test_optional, test_optional_reset_float)
{
    aeon::common::optional test = 3.0f;
    ASSERT_TRUE(test.has_value());

    test.reset();
    ASSERT_FALSE(test.has_value());
}

TEST(test_optional, test_optional_exception_int)
{
    aeon::common::optional<int> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(int value = test; UNUSED(value);, aeon::common::optional_value_exception);
}

TEST(test_optional, test_optional_exception_int2)
{
    aeon::common::optional<int> test;

    ASSERT_FALSE(test.has_value());

    ASSERT_THROW(int value = test; UNUSED(value);, aeon::common::optional_value_exception);

    test = 1337;
    ASSERT_TRUE(test.has_value());
    int value = test;
    ASSERT_EQ(1337, value);
}

TEST(test_optional, test_optional_exception_float)
{
    aeon::common::optional<float> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(float value = test; UNUSED(value);, aeon::common::optional_value_exception);
}

TEST(test_optional, test_optional_exception_float2)
{
    aeon::common::optional<float> test;

    ASSERT_FALSE(test.has_value());

    ASSERT_THROW(float value = test; UNUSED(value);, aeon::common::optional_value_exception);

    test = 1337.0f;
    ASSERT_TRUE(test.has_value());
    float value = test;
    ASSERT_EQ(1337.0f, value);
}

TEST(test_optional, test_optional_exception_string)
{
    aeon::common::optional<std::string> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(std::string value = test, aeon::common::optional_value_exception);
}

TEST(test_optional, test_optional_exception_string2)
{
    aeon::common::optional<std::string> test;

    ASSERT_FALSE(test.has_value());
    ASSERT_THROW(std::string value = test, aeon::common::optional_value_exception);

    test = std::string("Hello!");
    ASSERT_TRUE(test.has_value());
    std::string value = test;
    ASSERT_EQ(std::string("Hello!"), value);
}

TEST(test_optional, test_optional_compare_int)
{
    const aeon::common::optional test = 3;

    ASSERT_TRUE(test == 3);
}

TEST(test_optional, test_optional_compare_float)
{
    const aeon::common::optional test = 3.1f;
    ASSERT_TRUE(test == 3.1f);
}

TEST(test_optional, test_optional_compare_string)
{
    const aeon::common::optional test = std::string("Testing");
    ASSERT_TRUE(std::string(test) == std::string("Testing"));
}

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/variant/converting_variant.h>
#include <aeon/common/string.h>
#include <gtest/gtest.h>
#include <vector>

using namespace aeon;

TEST(test_converting_variant, default_create)
{
    variant::converting_variant v;
    EXPECT_TRUE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_FALSE(v.is_user_type());
}

TEST(test_converting_variant, create_with_string)
{
    common::string test = "Hello";
    variant::converting_variant v{std::move(test)};
    EXPECT_FALSE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::string, v.type());
}

TEST(test_converting_variant, create_with_const_char)
{
    const auto test = "Hello";
    variant::converting_variant v{test};
    EXPECT_FALSE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::string, v.type());
}

TEST(test_converting_variant, create_with_int8)
{
    variant::converting_variant v{static_cast<std::int8_t>(5)};
    EXPECT_FALSE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::int8, v.type());
}

TEST(test_converting_variant, create_with_int32)
{
    variant::converting_variant v{static_cast<std::int32_t>(5)};
    EXPECT_FALSE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::int32, v.type());
}

TEST(test_converting_variant, create_with_vector)
{
    variant::converting_variant v{std::vector{1, 2, 3}};
    EXPECT_FALSE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_TRUE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::user, v.type());
}

TEST(test_converting_variant, convert_float_to_int32)
{
    variant::converting_variant v{5.0f};
    EXPECT_FALSE(v.is_null());
    EXPECT_EQ(0, v.user_index());
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::float_t, v.type());
    EXPECT_EQ(5, v.get_value<std::int32_t>());
}

TEST(test_converting_variant, convert_string_to_int32)
{
    variant::converting_variant v{common::string{"1234"}};
    EXPECT_EQ(1234, v.get_value<std::int32_t>());
}

TEST(test_converting_variant, convert_string_to_float)
{
    variant::converting_variant v{common::string{"1234.567"}};
    EXPECT_FLOAT_EQ(1234.567f, v.get_value<float>());
}

TEST(test_converting_variant, convert_string_to_bool)
{
    variant::converting_variant v{common::string{"true"}};
    EXPECT_TRUE(v.get_value<bool>());
    variant::converting_variant v2{common::string{"false"}};
    EXPECT_FALSE(v2.get_value<bool>());
}

TEST(test_converting_variant, convert_float_to_string_to_int_to_bool)
{
    variant::converting_variant v{1.0f};
    v.convert_value<common::string>();
    v.convert_value<int>();
    v.convert_value<bool>();
    EXPECT_TRUE(v.get_value<bool>());
}

TEST(test_converting_variant, convert_string_to_int8)
{
    variant::converting_variant v{common::string{"-50"}};
    EXPECT_EQ(-50, v.get_value<std::int8_t>());
}

TEST(test_converting_variant, convert_int8_to_string)
{
    variant::converting_variant v{std::int8_t{-50}};
    EXPECT_EQ("-50", v.get_value<common::string>());
}

TEST(test_converting_variant, convert_string_to_int16)
{
    variant::converting_variant v{common::string{"-500"}};
    EXPECT_EQ(-500, v.get_value<std::int16_t>());
}

TEST(test_converting_variant, convert_string_to_uint8)
{
    variant::converting_variant v{common::string{"128"}};
    EXPECT_EQ(128, v.get_value<std::uint8_t>());
}

TEST(test_converting_variant, convert_string_to_uint16)
{
    variant::converting_variant v{common::string{"65535"}};
    EXPECT_EQ(65535, v.get_value<std::uint16_t>());
}

struct custom_user_type
{
    int value = 1337;

    custom_user_type(int value)
        : value{value}
    {
    }

    operator common::string() const
    {
        return "The value is: " + std::to_string(value);
    }
};

TEST(test_converting_variant, create_with_custom_type)
{
    custom_user_type t{5};
    variant::converting_variant v{t};
    EXPECT_EQ(5, v.get_value<custom_user_type>().value);
}

TEST(test_converting_variant, convert_with_custom_type)
{
    custom_user_type t{5};
    variant::converting_variant v{t};
    EXPECT_EQ("The value is: 5", (v.get_value<custom_user_type, common::string>()));
}

TEST(test_converting_variant, convert_with_custom_type_with_convert_value)
{
    custom_user_type t{5};
    variant::converting_variant v{t};
    EXPECT_TRUE(v.is_user_type());
    v.convert_value<custom_user_type, common::string>();
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ("The value is: 5", (v.get_value<common::string>()));
}

TEST(test_converting_variant, convert_to_custom_type)
{
    variant::converting_variant v{static_cast<std::uint32_t>(42)};
    EXPECT_EQ(42, (v.get_value<std::uint32_t, custom_user_type>().value));
}

TEST(test_converting_variant, convert_to_custom_type_with_convert_value)
{
    variant::converting_variant v{static_cast<std::uint32_t>(42)};
    EXPECT_FALSE(v.is_user_type());
    v.convert_value<std::uint32_t, custom_user_type>();
    EXPECT_TRUE(v.is_user_type());
    EXPECT_EQ(42, (v.get_value<custom_user_type>().value));
}

TEST(test_converting_variant, datetime_variant)
{
    variant::converting_variant v{std::chrono::system_clock::now()};
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::calendar, v.type());
    ASSERT_NO_THROW(v.convert_value<common::string>());
    EXPECT_EQ(variant::converting_variant::type::string, v.type());
}

TEST(test_converting_variant, datetime_variant_to_string_is_iso8601)
{
    variant::converting_variant v{chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 2015, 1, 7, 12, 32, 21}};
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::calendar, v.type());
    ASSERT_NO_THROW(v.convert_value<common::string>());
    EXPECT_EQ(v.get_value<common::string>(), "2015-01-07T12:32:21.000-02:00");
}

TEST(test_converting_variant, iso8601_string_to_datetime)
{
    variant::converting_variant v{"2015-01-07T12:32:21.000-02:00"};
    EXPECT_FALSE(v.is_user_type());
    EXPECT_EQ(variant::converting_variant::type::string, v.type());
    ASSERT_NO_THROW(v.convert_value<chrono::calendar>());
    EXPECT_EQ(variant::converting_variant::type::calendar, v.type());
    EXPECT_EQ(v.get_value<chrono::calendar>(),
              (chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 2015, 1, 7, 12, 32, 21}));
}

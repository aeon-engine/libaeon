// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/from_chars.h>
#include <gtest/gtest.h>
#include <string_view>

using namespace aeon;
using namespace std::literals;

template <typename T>
void test_basic_value(const std::string_view str, const T expected_value)
{
    T value{};
    const auto result = common::from_chars(str, value);
    EXPECT_EQ(value, expected_value);
    EXPECT_EQ(result.ec, std::errc{});
    EXPECT_EQ(result.ptr, std::data(str) + std::size(str));
}

template <typename T>
void test_basic_value(const std::string_view str, const T expected_value, const int base)
{
    T value{};
    const auto result = common::from_chars(str, value, base);
    EXPECT_EQ(value, expected_value);
    EXPECT_EQ(result.ec, std::errc{});
    EXPECT_EQ(result.ptr, std::data(str) + std::size(str));
}

TEST(test_from_chars, test_parse_basic_integers)
{
    test_basic_value<int32_t>("0"sv, 0);
    test_basic_value<int32_t>("1"sv, 1);
    test_basic_value<int32_t>("1234"sv, 1234);
    test_basic_value<int32_t>("-1"sv, -1);
    test_basic_value<int32_t>("-1234"sv, -1234);

    test_basic_value<int64_t>("0"sv, 0);
    test_basic_value<int64_t>("1"sv, 1);
    test_basic_value<int64_t>("1234"sv, 1234);
    test_basic_value<int64_t>("-1"sv, -1);
    test_basic_value<int64_t>("-1234"sv, -1234);

    test_basic_value<uint32_t>("0"sv, 0u);
    test_basic_value<uint32_t>("1"sv, 1u);
    test_basic_value<uint32_t>("1234"sv, 1234u);

    test_basic_value<uint64_t>("0"sv, 0u);
    test_basic_value<uint64_t>("1"sv, 1u);
    test_basic_value<uint64_t>("1234"sv, 1234u);
}

TEST(test_from_chars, test_parse_basic_floats)
{
    test_basic_value<float>("0"sv, 0.0f);
    test_basic_value<float>("0.0"sv, 0.0f);
    test_basic_value<float>("1"sv, 1.0f);
    test_basic_value<float>("1.0"sv, 1.0f);
    test_basic_value<float>("1.000"sv, 1.0f);
    test_basic_value<float>("1234"sv, 1234.0f);
    test_basic_value<float>("-1.0"sv, -1.0f);
    test_basic_value<float>("-1234.0"sv, -1234.0f);
}

TEST(test_from_chars, test_parse_basic_doubles)
{
    test_basic_value<double>("0"sv, 0.0);
    test_basic_value<double>("0.0"sv, 0.0);
    test_basic_value<double>("1"sv, 1.0);
    test_basic_value<double>("1.0"sv, 1.0);
    test_basic_value<double>("1.000"sv, 1.0);
    test_basic_value<double>("1234"sv, 1234.0);
    test_basic_value<double>("-1.0"sv, -1.0);
    test_basic_value<double>("-1234.0"sv, -1234.0);
}

TEST(test_from_chars, test_parse_basic_long_doubles)
{
    test_basic_value<long double>("0"sv, 0.0L);
    test_basic_value<long double>("0.0"sv, 0.0L);
    test_basic_value<long double>("1"sv, 1.0L);
    test_basic_value<long double>("1.0"sv, 1.0L);
    test_basic_value<long double>("1.000"sv, 1.0L);
    test_basic_value<long double>("1234"sv, 1234.0L);
    test_basic_value<long double>("-1.0"sv, -1.0L);
    test_basic_value<long double>("-1234.0"sv, -1234.0L);
}

TEST(test_from_chars, test_parse_basic_integers_hex)
{
    test_basic_value<int32_t>("0"sv, 0, 16);
    test_basic_value<int32_t>("1"sv, 1, 16);
    test_basic_value<int32_t>("ff"sv, 255, 16);
    test_basic_value<int32_t>("100"sv, 256, 16);
    test_basic_value<int32_t>("-ff"sv, -255, 16);

    test_basic_value<int64_t>("0"sv, 0, 16);
    test_basic_value<int64_t>("1"sv, 1, 16);
    test_basic_value<int64_t>("ff"sv, 255, 16);
    test_basic_value<int64_t>("100"sv, 256, 16);
    test_basic_value<int64_t>("-ff"sv, -255, 16);
}
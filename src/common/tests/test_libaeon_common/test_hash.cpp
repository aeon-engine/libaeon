// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/hash.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_hash, test_hash_combine)
{
    std::size_t hash = 0;
    common::hash_combine(hash, 0);
    EXPECT_NE(0, hash);

    const auto previous_value = hash;
    common::hash_combine(hash, 0);
    EXPECT_NE(previous_value, hash);
    EXPECT_NE(0, hash);
}

TEST(test_hash, test_hash_combined)
{
    std::size_t hash = 0;
    common::hash_combine(hash, 0);
    EXPECT_NE(0, hash);
    EXPECT_EQ(common::hash_combined(0), hash);

    const auto previous_value = hash;
    common::hash_combine(hash, 0);
    EXPECT_NE(previous_value, hash);
    EXPECT_NE(0, hash);
    EXPECT_EQ(common::hash_combined(0, 0), hash);
}

TEST(test_hash, test_hash_combined_lvalue)
{
    const auto value1 = 1;
    const auto value2 = 2;
    EXPECT_EQ(common::hash_combined(1, 2), common::hash_combined(value1, value2));
}

TEST(test_hash, test_variadic_hash_combine)
{
    std::size_t hash = 0;
    common::hash_combine(hash, 0);
    const auto result1 = hash;

    hash = 0;
    common::hash_combine(hash, 0, 0);
    const auto result2 = hash;

    hash = 0;
    common::hash_combine(hash, 0, 0, 0);
    const auto result3 = hash;

    EXPECT_NE(result1, result2);
    EXPECT_NE(result2, result3);
    EXPECT_NE(result1, result3);
}

TEST(test_hash, test_hash_pair)
{
    std::pair<int, float> value1{1, 2.0f};
    EXPECT_NE(0u, std::hash<decltype(value1)>{}(value1));

    std::pair<float, int> value2{2.0f, 1};
    EXPECT_NE(0u, std::hash<decltype(value2)>{}(value2));

    EXPECT_NE(std::hash<decltype(value1)>{}(value1), std::hash<decltype(value2)>{}(value2));
}

TEST(test_hash, test_hash_tuple)
{
    std::tuple<int, float> value1{1, 2.0f};
    EXPECT_NE(0u, std::hash<decltype(value1)>{}(value1));

    std::tuple<float, int> value2{2.0f, 1};
    EXPECT_NE(0u, std::hash<decltype(value2)>{}(value2));

    EXPECT_NE(std::hash<decltype(value1)>{}(value1), std::hash<decltype(value2)>{}(value2));
}

TEST(test_hash, test_hash_pair_equal_to_tuple)
{
    std::pair<int, float> pair_value{1, 2.0f};
    std::tuple<int, float> tuple_value{1, 2.0f};
    EXPECT_EQ(std::hash<decltype(pair_value)>{}(pair_value), std::hash<decltype(tuple_value)>{}(tuple_value));

    std::pair<float, int> pair_value2{2.0f, 1};
    std::tuple<float, int> tuple_value2{2.0f, 1};
    EXPECT_EQ(std::hash<decltype(pair_value2)>{}(pair_value2), std::hash<decltype(tuple_value2)>{}(tuple_value2));
}

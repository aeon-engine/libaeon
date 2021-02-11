// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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

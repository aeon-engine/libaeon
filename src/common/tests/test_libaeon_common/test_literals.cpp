// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/literals.h>
#include <gtest/gtest.h>
#include <type_traits>

TEST(test_literals, test_literals_zero)
{
    auto value = 0_size_t;
    EXPECT_EQ(0u, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_one)
{
    auto value = 1_size_t;
    EXPECT_EQ(1u, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_various_numbers1)
{
    auto value = 42_size_t;
    EXPECT_EQ(42u, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_various_numbers2)
{
    auto value = 1337_size_t;
    EXPECT_EQ(1337u, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_various_numbers3)
{
    auto value = 0xffff_size_t;
    EXPECT_EQ(0xffffu, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

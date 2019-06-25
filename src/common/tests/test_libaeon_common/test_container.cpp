// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/container.h>
#include <gtest/gtest.h>
#include <array>
#include <string>

using namespace aeon;
using namespace std::string_literals;

TEST(test_container, test_adjacent_execute)
{
    std::array data{1, 2, 3, 4, 5, 6, 7, 8};
    common::container::adjacent_execute(std::begin(data), std::end(data), [](const auto first, const auto second) {
        EXPECT_EQ(1, second - first);
        return true;
    });
}

TEST(test_container, test_contains_int)
{
    std::array data{1, 2, 3, 4, 5, 6, 7, 8};
    EXPECT_TRUE(common::container::contains(std::begin(data), std::end(data), 1));
    EXPECT_TRUE(common::container::contains(std::begin(data), std::end(data), 5));
    EXPECT_TRUE(common::container::contains(std::begin(data), std::end(data), 8));

    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), 9));
    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), -1));
    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), 1337));
}

TEST(test_container, test_contains_string)
{
    std::array data{"1"s, "2"s, "3"s, "4"s, "5"s, "6"s, "7"s, "8"s};
    EXPECT_TRUE(common::container::contains(std::begin(data), std::end(data), "1"s));
    EXPECT_TRUE(common::container::contains(std::begin(data), std::end(data), "5"s));
    EXPECT_TRUE(common::container::contains(std::begin(data), std::end(data), "8"s));

    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), "9"s));
    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), "-1"s));
    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), "1337"s));
    EXPECT_FALSE(common::container::contains(std::begin(data), std::end(data), "one"s));
}

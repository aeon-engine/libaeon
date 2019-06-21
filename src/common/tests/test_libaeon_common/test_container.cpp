// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/container.h>
#include <gtest/gtest.h>
#include <array>

using namespace aeon;

TEST(test_container, test_adjacent_execute)
{
    std::array data{1, 2, 3, 4, 5, 6, 7, 8};
    common::container::adjacent_execute(std::begin(data), std::end(data), [](const auto first, const auto second) {
        EXPECT_EQ(1, second - first);
        return true;
    });
}

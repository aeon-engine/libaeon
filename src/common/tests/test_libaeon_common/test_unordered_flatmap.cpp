// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/unordered_flatmap.h>
#include <gtest/gtest.h>

using namespace aeon;

struct test_fixture_unordered_flatmap_default_data : ::testing::Test
{
    test_fixture_unordered_flatmap_default_data()
    {
        unordered_flatmap_["One"] = 1;
        unordered_flatmap_["Two"] = 2;
        unordered_flatmap_["Three"] = 3;
        unordered_flatmap_["Four"] = 4;
        unordered_flatmap_["Five"] = 5;
    }

    void SetUp() override
    {
        ASSERT_EQ(5u, std::size(unordered_flatmap_));
    }

    common::unordered_flatmap<std::string, int> unordered_flatmap_;
};

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_at)
{
    const auto at_one = unordered_flatmap_.at("One");
    const auto at_two = unordered_flatmap_.at("Two");
    const auto at_three = unordered_flatmap_.at("Three");
    const auto at_four = unordered_flatmap_.at("Four");
    const auto at_five = unordered_flatmap_.at("Five");

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(3, at_three);
    ASSERT_EQ(4, at_four);
    ASSERT_EQ(5, at_five);
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_index_operator)
{
    const auto at_one = unordered_flatmap_["One"];
    const auto at_two = unordered_flatmap_["Two"];
    const auto at_three = unordered_flatmap_["Three"];
    const auto at_four = unordered_flatmap_["Four"];
    const auto at_five = unordered_flatmap_["Five"];

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(3, at_three);
    ASSERT_EQ(4, at_four);
    ASSERT_EQ(5, at_five);
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_index_operator_overwrite)
{
    unordered_flatmap_["Three"] = 42;
    unordered_flatmap_["Four"] = 32;

    const auto at_one = unordered_flatmap_["One"];
    const auto at_two = unordered_flatmap_["Two"];
    const auto at_three = unordered_flatmap_["Three"];
    const auto at_four = unordered_flatmap_["Four"];
    const auto at_five = unordered_flatmap_["Five"];

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(42, at_three);
    ASSERT_EQ(32, at_four);
    ASSERT_EQ(5, at_five);

    ASSERT_EQ(5u, std::size(unordered_flatmap_));
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_push_back)
{
    unordered_flatmap_.push_back("Three", 15);
    auto at_three = unordered_flatmap_["Three"];
    ASSERT_EQ(3, at_three);
    unordered_flatmap_.insert("Three", 15);
    at_three = unordered_flatmap_["Three"];
    ASSERT_EQ(15, at_three);
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_index_operator_default)
{
    const auto cant_find = unordered_flatmap_["Something! 123"];

    ASSERT_EQ(0, cant_find);
    ASSERT_EQ(6u, std::size(unordered_flatmap_));
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_empty_and_clear)
{
    ASSERT_FALSE(unordered_flatmap_.empty());
    unordered_flatmap_.clear();
    ASSERT_TRUE(unordered_flatmap_.empty());
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_find)
{
    const auto result = unordered_flatmap_.find("Three");

    ASSERT_EQ("Three", result->first);
    ASSERT_EQ(3, result->second);
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_not_found)
{
    const auto result = unordered_flatmap_.find("Something! 123");

    ASSERT_TRUE(result == unordered_flatmap_.end());
    ASSERT_EQ(5u, std::size(unordered_flatmap_));
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_iterate)
{
    auto loop_times = 0;
    for (const auto &[key, value] : unordered_flatmap_)
    {
        if (key == "One")
            ASSERT_EQ(1, value);

        if (key == "Two")
            ASSERT_EQ(2, value);

        if (key == "Three")
            ASSERT_EQ(3, value);

        if (key == "Four")
            ASSERT_EQ(4, value);

        if (key == "Five")
            ASSERT_EQ(5, value);

        ++loop_times;
    }

    ASSERT_EQ(5u, std::size(unordered_flatmap_));
    ASSERT_EQ(5, loop_times);
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_erase_by_key)
{
    unordered_flatmap_.erase("Something! 123");
    ASSERT_EQ(5u, std::size(unordered_flatmap_));

    unordered_flatmap_.erase("Three");
    ASSERT_EQ(4u, std::size(unordered_flatmap_));

    unordered_flatmap_.erase("Two");
    ASSERT_EQ(3u, std::size(unordered_flatmap_));
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_erase_by_iterator)
{
    ASSERT_EQ(5u, std::size(unordered_flatmap_));

    auto result = unordered_flatmap_.find("Three");
    unordered_flatmap_.erase(result);

    ASSERT_EQ(4u, std::size(unordered_flatmap_));

    result = unordered_flatmap_.find("Two");
    unordered_flatmap_.erase(result);

    ASSERT_EQ(3u, std::size(unordered_flatmap_));
}

TEST_F(test_fixture_unordered_flatmap_default_data, test_unordered_flatmap_erase_if)
{
    ASSERT_EQ(5u, std::size(unordered_flatmap_));
    unordered_flatmap_.erase_if([](const auto &pair) { return (pair.first == "Two" || pair.first == "Four"); });
    ASSERT_EQ(3u, std::size(unordered_flatmap_));
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_different_size)
{
    const common::unordered_flatmap<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const common::unordered_flatmap<std::string, int> map2{{"hello", 3}, {"bye", 4}, {"another", 6}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_different_key)
{
    const common::unordered_flatmap<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const common::unordered_flatmap<std::string, int> map2{{"hello", 3}, {"bye2", 4}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_different_value)
{
    const common::unordered_flatmap<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const common::unordered_flatmap<std::string, int> map2{{"hello", 3}, {"bye", 5}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_unordered_flatmap, test_unordered_flatmap_compare_equal)
{
    const common::unordered_flatmap<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const common::unordered_flatmap<std::string, int> map2{{"hello", 3}, {"bye", 4}};
    EXPECT_TRUE(map1 == map2);
    EXPECT_FALSE(map1 != map2);
}

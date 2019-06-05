// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/utility/linear_map.h>
#include <gtest/gtest.h>

using namespace aeon;

struct test_fixture_linear_map_default_data : ::testing::Test
{
    test_fixture_linear_map_default_data()
    {
        linear_map_["One"] = 1;
        linear_map_["Two"] = 2;
        linear_map_["Three"] = 3;
        linear_map_["Four"] = 4;
        linear_map_["Five"] = 5;
    }

    void SetUp() override
    {
        ASSERT_EQ(5, linear_map_.size());
    }

    utility::linear_map<std::string, int> linear_map_;
};

TEST_F(test_fixture_linear_map_default_data, test_linear_map_at)
{
    const auto at_one = linear_map_.at("One");
    const auto at_two = linear_map_.at("Two");
    const auto at_three = linear_map_.at("Three");
    const auto at_four = linear_map_.at("Four");
    const auto at_five = linear_map_.at("Five");

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(3, at_three);
    ASSERT_EQ(4, at_four);
    ASSERT_EQ(5, at_five);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_index_operator)
{
    const auto at_one = linear_map_["One"];
    const auto at_two = linear_map_["Two"];
    const auto at_three = linear_map_["Three"];
    const auto at_four = linear_map_["Four"];
    const auto at_five = linear_map_["Five"];

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(3, at_three);
    ASSERT_EQ(4, at_four);
    ASSERT_EQ(5, at_five);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_index_operator_overwrite)
{
    linear_map_["Three"] = 42;
    linear_map_["Four"] = 32;

    const auto at_one = linear_map_["One"];
    const auto at_two = linear_map_["Two"];
    const auto at_three = linear_map_["Three"];
    const auto at_four = linear_map_["Four"];
    const auto at_five = linear_map_["Five"];

    ASSERT_EQ(1, at_one);
    ASSERT_EQ(2, at_two);
    ASSERT_EQ(42, at_three);
    ASSERT_EQ(32, at_four);
    ASSERT_EQ(5, at_five);

    ASSERT_EQ(5, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_push_back)
{
    linear_map_.push_back("Three", 15);
    auto at_three = linear_map_["Three"];
    ASSERT_EQ(3, at_three);
    linear_map_.insert("Three", 15);
    at_three = linear_map_["Three"];
    ASSERT_EQ(15, at_three);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_index_operator_default)
{
    const auto cant_find = linear_map_["Something! 123"];

    ASSERT_EQ(0, cant_find);
    ASSERT_EQ(6, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_empty_and_clear)
{
    ASSERT_FALSE(linear_map_.empty());
    linear_map_.clear();
    ASSERT_TRUE(linear_map_.empty());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_find)
{
    const auto result = linear_map_.find("Three");

    ASSERT_EQ("Three", result->first);
    ASSERT_EQ(3, result->second);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_not_found)
{
    const auto result = linear_map_.find("Something! 123");

    ASSERT_TRUE(result == linear_map_.end());
    ASSERT_EQ(5, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_iterate)
{
    auto loop_times = 0;
    for (const auto &[key, value] : linear_map_)
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

    ASSERT_EQ(5, linear_map_.size());
    ASSERT_EQ(5, loop_times);
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_erase_by_key)
{
    linear_map_.erase("Something! 123");
    ASSERT_EQ(5, linear_map_.size());

    linear_map_.erase("Three");
    ASSERT_EQ(4, linear_map_.size());

    linear_map_.erase("Two");
    ASSERT_EQ(3, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_erase_by_iterator)
{
    ASSERT_EQ(5, linear_map_.size());

    auto result = linear_map_.find("Three");
    linear_map_.erase(result);

    ASSERT_EQ(4, linear_map_.size());

    result = linear_map_.find("Two");
    linear_map_.erase(result);

    ASSERT_EQ(3, linear_map_.size());
}

TEST_F(test_fixture_linear_map_default_data, test_linear_map_erase_if)
{
    ASSERT_EQ(5, linear_map_.size());
    linear_map_.erase_if([](const auto &pair) { return (pair.first == "Two" || pair.first == "Four"); });
    ASSERT_EQ(3, linear_map_.size());
}

TEST(test_fixture_linear_map, test_linear_map_compare_different_size)
{
    const utility::linear_map<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const utility::linear_map<std::string, int> map2{{"hello", 3}, {"bye", 4}, {"another", 6}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_linear_map, test_linear_map_compare_different_key)
{
    const utility::linear_map<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const utility::linear_map<std::string, int> map2{{"hello", 3}, {"bye2", 4}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_linear_map, test_linear_map_compare_different_value)
{
    const utility::linear_map<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const utility::linear_map<std::string, int> map2{{"hello", 3}, {"bye", 5}};
    EXPECT_FALSE(map1 == map2);
    EXPECT_TRUE(map1 != map2);
}

TEST(test_fixture_linear_map, test_linear_map_compare_equal)
{
    const utility::linear_map<std::string, int> map1{{"hello", 3}, {"bye", 4}};
    const utility::linear_map<std::string, int> map2{{"hello", 3}, {"bye", 4}};
    EXPECT_TRUE(map1 == map2);
    EXPECT_FALSE(map1 != map2);
}

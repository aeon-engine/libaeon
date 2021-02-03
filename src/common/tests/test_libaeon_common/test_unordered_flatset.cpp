// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/unordered_flatset.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_unordered_flatset, test_unordered_flatset_unique_insert)
{
    common::unordered_flatset<std::string> set;

    EXPECT_EQ(0u, std::size(set));
    EXPECT_TRUE(std::empty(set));

    set.insert("A");
    EXPECT_EQ(1u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("B");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("A");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("B");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("C");
    EXPECT_EQ(3u, std::size(set));
    EXPECT_FALSE(std::empty(set));
}

TEST(test_unordered_flatset, test_unordered_flatset_unique_emplace)
{
    common::unordered_flatset<std::string> set;

    EXPECT_EQ(0u, std::size(set));
    EXPECT_TRUE(std::empty(set));

    set.emplace("A");
    EXPECT_EQ(1u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.emplace("B");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.emplace("A");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.emplace("B");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.emplace("C");
    EXPECT_EQ(3u, std::size(set));
    EXPECT_FALSE(std::empty(set));
}

TEST(test_unordered_flatset, test_unordered_flatset_unique_insert_emplace_mixed)
{
    common::unordered_flatset<std::string> set;

    EXPECT_EQ(0u, std::size(set));
    EXPECT_TRUE(std::empty(set));

    set.emplace("A");
    EXPECT_EQ(1u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.emplace("B");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("A");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("B");
    EXPECT_EQ(2u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.emplace("C");
    EXPECT_EQ(3u, std::size(set));
    EXPECT_FALSE(std::empty(set));

    set.insert("C");
    EXPECT_EQ(3u, std::size(set));
    EXPECT_FALSE(std::empty(set));
}

TEST(test_unordered_flatset, test_unordered_flatset_remove_by_value)
{
    common::unordered_flatset<std::string> set;
    set.emplace("A");
    set.emplace("B");
    set.emplace("C");
    set.emplace("D");

    EXPECT_EQ(4u, std::size(set));

    EXPECT_TRUE(set.contains("B"));
    set.erase("B");
    EXPECT_EQ(3u, std::size(set));
    EXPECT_FALSE(set.contains("B"));

    set.erase("ABCD");
    EXPECT_EQ(3u, std::size(set));
}

TEST(test_unordered_flatset, test_unordered_flatset_remove_by_iterator)
{
    common::unordered_flatset<std::string> set;
    set.emplace("A");
    set.emplace("B");
    set.emplace("C");
    set.emplace("D");

    EXPECT_EQ(4u, std::size(set));

    EXPECT_TRUE(set.contains("A"));
    set.erase(std::begin(set));
    EXPECT_FALSE(set.contains("A"));
    EXPECT_EQ(3u, std::size(set));

    EXPECT_TRUE(set.contains("B"));
    set.erase(std::begin(set));
    EXPECT_FALSE(set.contains("B"));
    EXPECT_EQ(2u, std::size(set));

    EXPECT_TRUE(set.contains("C"));
    set.erase(std::begin(set));
    EXPECT_FALSE(set.contains("C"));
    EXPECT_EQ(1u, std::size(set));

    EXPECT_TRUE(set.contains("D"));
    set.erase(std::begin(set));
    EXPECT_FALSE(set.contains("D"));
    EXPECT_EQ(0u, std::size(set));
}

TEST(test_unordered_flatset, test_unordered_flatset_compare)
{
    common::unordered_flatset<std::string> set;
    set.emplace("A");
    set.emplace("B");
    set.emplace("C");

    common::unordered_flatset<std::string> set2;
    set2.emplace("A");
    set2.emplace("B");
    set2.emplace("C");

    EXPECT_TRUE(set == set2);
    EXPECT_FALSE(set != set2);

    set.emplace("D");
    EXPECT_FALSE(set == set2);
    EXPECT_TRUE(set != set2);
}

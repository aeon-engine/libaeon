// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/general_tree.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_general_tree, test_create_empty)
{
    common::general_tree tree{123};
    common::general_tree<std::string> tree2{"hello"};
}

TEST(test_general_tree, test_tree_interface)
{
    common::general_tree<char> tree{'R'};
    auto root = tree.root();
    auto a_chd = root.emplace_child('A');
    auto b_chd = root.emplace_child('B');
    a_chd.add_child('C');
    a_chd.add_child('D');
    a_chd.add_child('E');
    auto f = b_chd.emplace_child('F');

    EXPECT_TRUE(root.is_root());
    EXPECT_FALSE(a_chd.is_root());
    EXPECT_FALSE(b_chd.is_root());
    EXPECT_FALSE(f.is_root());

    EXPECT_ANY_THROW([[maybe_unused]] auto parent = root.parent());
    EXPECT_NO_THROW([[maybe_unused]] auto a_parent = a_chd.parent());
    EXPECT_NO_THROW([[maybe_unused]] auto b_parent = b_chd.parent());

    EXPECT_EQ(*a_chd, 'A');
    EXPECT_EQ(*b_chd, 'B');
    EXPECT_EQ(*f, 'F');

    EXPECT_EQ(2u, root.child_count());
    EXPECT_EQ(3u, a_chd.child_count());
    EXPECT_EQ(1u, b_chd.child_count());
    EXPECT_EQ(0u, f.child_count());

    EXPECT_EQ(*root.at(0), 'A');
    EXPECT_EQ(*root.at(1), 'B');

    EXPECT_EQ(*a_chd.at(0), 'C');
    EXPECT_EQ(*a_chd.at(1), 'D');
    EXPECT_EQ(*a_chd.at(2), 'E');
}

// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/singleton.h>
#include <gtest/gtest.h>

class test_singleton : public aeon::common::singleton<test_singleton>
{
};

TEST(test_singleton, test_singleton_create)
{
    EXPECT_NE(nullptr, &test_singleton::get_singleton());
}

TEST(test_singleton, test_singleton_is_same)
{
    const auto singleton_ptr = &test_singleton::get_singleton();
    const auto singleton_ptr2 = &test_singleton::get_singleton();
    const auto singleton_ptr3 = &test_singleton::get_singleton();

    EXPECT_EQ(singleton_ptr, singleton_ptr2);
    EXPECT_EQ(singleton_ptr, singleton_ptr3);
}

TEST(test_singleton, test_singleton_ptr_is_same)
{
    const auto singleton_ptr = &test_singleton::get_singleton();
    const auto singleton_ptr2 = test_singleton::get_singleton_ptr();
    const auto singleton_ptr3 = test_singleton::get_singleton_ptr();

    EXPECT_EQ(singleton_ptr, singleton_ptr2);
    EXPECT_EQ(singleton_ptr, singleton_ptr3);
}

/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gtest/gtest.h>
#include <aeon/common/singleton.h>

class test_singleton : public aeon::common::singleton<test_singleton>
{
};

aeon_utility_initialize_singleton(test_singleton);

TEST(test_singleton, test_singleton_create)
{
    EXPECT_NE(nullptr, test_singleton::create());
    ASSERT_NO_THROW(test_singleton::dispose());
}

TEST(test_singleton, test_singleton_create_multiple_throws)
{
    EXPECT_NE(nullptr, test_singleton::create());
    ASSERT_ANY_THROW(test_singleton::create());
    ASSERT_ANY_THROW(test_singleton::create());
    ASSERT_ANY_THROW(test_singleton::create());
    ASSERT_NO_THROW(test_singleton::dispose());
}

TEST(test_singleton, test_singleton_ptr_is_same_as_create)
{
    auto singleton = test_singleton::create();
    EXPECT_NE(nullptr, singleton);
    EXPECT_EQ(singleton, test_singleton::get_singleton_ptr());
    ASSERT_NO_THROW(test_singleton::dispose());
}

TEST(test_singleton, test_singleton_ref_is_same_as_ptr)
{
    EXPECT_NE(nullptr, test_singleton::create());
    auto &singleton_ref = test_singleton::get_singleton();
    EXPECT_EQ(&singleton_ref, test_singleton::get_singleton_ptr());
    ASSERT_NO_THROW(test_singleton::dispose());
}

TEST(test_singleton, test_singleton_null_after_dispose)
{
    EXPECT_NE(nullptr, test_singleton::create());
    EXPECT_NE(nullptr, test_singleton::get_singleton_ptr());
    ASSERT_NO_THROW(test_singleton::dispose());
    EXPECT_EQ(nullptr, test_singleton::get_singleton_ptr());
}

TEST(test_singleton, test_singleton_ref_throws_on_empty)
{
    EXPECT_ANY_THROW(test_singleton::get_singleton());
}

TEST(test_singleton, test_singleton_ref_throws_after_dispose)
{
    EXPECT_NE(nullptr, test_singleton::create());
    ASSERT_NO_THROW(test_singleton::get_singleton());
    ASSERT_NO_THROW(test_singleton::dispose());
    ASSERT_ANY_THROW(test_singleton::get_singleton());
}

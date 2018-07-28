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

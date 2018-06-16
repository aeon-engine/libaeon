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

#include <aeon/common/flags.h>
#include <gtest/gtest.h>

enum class test_flags
{
    flag_1 = 0x01,
    flag_2 = 0x02,
    flag_3 = 0x04,
    flag_4 = 0x08,
    flag_5 = 0x10
};

aeon_declare_flag_operators(test_flags)

    TEST(test_flags, test_flags_create)
{
    aeon::common::flags<test_flags> test;
    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_is_set)
{
    aeon::common::flags<test_flags> test = test_flags::flag_1 | test_flags::flag_4;
    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));

    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_set_unset)
{
    aeon::common::flags<test_flags> test;

    test.set(test_flags::flag_1);

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.set(test_flags::flag_2);

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_FALSE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.set(test_flags::flag_4);

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.unset(test_flags::flag_1);

    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_TRUE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));

    test.unset(test_flags::flag_2);

    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_5));
}

TEST(test_flags, test_flags_operators)
{
    aeon::common::flags<test_flags> test = test_flags::flag_1 | test_flags::flag_4;

    test |= test_flags::flag_5;
    test ^= test_flags::flag_1;

    ASSERT_FALSE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_5));

    test ^= test_flags::flag_1;

    ASSERT_TRUE(test.is_set(test_flags::flag_1));
    ASSERT_FALSE(test.is_set(test_flags::flag_2));
    ASSERT_TRUE(test.is_set(test_flags::flag_4));
    ASSERT_FALSE(test.is_set(test_flags::flag_3));
    ASSERT_TRUE(test.is_set(test_flags::flag_5));
}

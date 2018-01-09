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
#include <aeon/common/literals.h>

#include <type_traits>

TEST(test_literals, test_literals_zero)
{
    auto value = 0_size_t;
    EXPECT_EQ(0, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_one)
{
    auto value = 1_size_t;
    EXPECT_EQ(1, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_various_numbers1)
{
    auto value = 42_size_t;
    EXPECT_EQ(42, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_various_numbers2)
{
    auto value = 1337_size_t;
    EXPECT_EQ(1337, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

TEST(test_literals, test_literals_various_numbers3)
{
    auto value = 0xffff_size_t;
    EXPECT_EQ(0xffff, value);
    EXPECT_TRUE((std::is_same<std::size_t, decltype(value)>::value));
}

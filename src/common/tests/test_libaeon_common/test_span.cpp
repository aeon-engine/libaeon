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

#include <aeon/common/span.h>
#include <gtest/gtest.h>
#include <vector>

using namespace aeon;

TEST(test_span, test_span_empty)
{
    common::span<int> s;

    EXPECT_EQ(nullptr, s.data());
    EXPECT_EQ(0, s.size());
}

TEST(test_span, test_span_memory_buffer)
{
    const auto *test = "ABCDE";

    common::span s{test, 5};

    EXPECT_EQ(5, s.size());
    EXPECT_EQ('A', s.front());
    EXPECT_EQ('E', s.back());

    char expected = 'A';
    int amount = 0;

    for (const auto c : s)
    {
        EXPECT_EQ(c, expected++);
        ++amount;
    }

    EXPECT_EQ(amount, s.size());
}

TEST(test_span, test_span_pointers)
{
    const std::vector<int> test{1, 2, 3, 4, 5};

    common::span s{&test.front(), &test.back()};

    // According to c++20 spec this ctor must be span(firstElem, lastElem - firstElem)
    EXPECT_EQ(4, s.size());
    EXPECT_EQ(1, s.front());
    EXPECT_EQ(4, s.back());

    int expected = 1;
    int amount = 0;

    for (const auto c : s)
    {
        EXPECT_EQ(c, expected++);
        ++amount;
    }

    EXPECT_EQ(amount, s.size());
}

TEST(test_span, test_span_container)
{
    const std::vector<int> test{1, 2, 3, 4, 5};

    common::span s{test};

    EXPECT_EQ(5, s.size());
    EXPECT_EQ(1, s.front());
    EXPECT_EQ(5, s.back());

    int expected = 1;
    int amount = 0;

    for (const auto c : s)
    {
        EXPECT_EQ(c, expected++);
        ++amount;
    }

    EXPECT_EQ(amount, s.size());
}

TEST(test_span, test_span_std_array)
{
    const std::array<int, 5> test{1, 2, 3, 4, 5};

    common::span s{test};

    EXPECT_EQ(5, s.size());
    EXPECT_EQ(1, s.front());
    EXPECT_EQ(5, s.back());

    int expected = 1;
    int amount = 0;

    for (const auto c : s)
    {
        EXPECT_EQ(c, expected++);
        ++amount;
    }

    EXPECT_EQ(amount, s.size());
}

TEST(test_span, test_span_std_array_non_const)
{
    std::array<int, 5> test{1, 2, 3, 4, 5};

    common::span s{test};

    EXPECT_EQ(5, s.size());
    EXPECT_EQ(1, s.front());
    EXPECT_EQ(5, s.back());

    int expected = 1;
    int amount = 0;

    for (const auto c : s)
    {
        EXPECT_EQ(c, expected++);
        ++amount;
    }

    EXPECT_EQ(amount, s.size());
}

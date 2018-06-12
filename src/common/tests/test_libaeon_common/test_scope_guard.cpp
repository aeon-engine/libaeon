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

#include <aeon/common/scope_guard.h>
#include <gtest/gtest.h>

TEST(test_scope_guard, test_scope_guard_fail_discard)
{
    int a = 3;
    {
        aeon_scope_fail
        {
            a = 4;
        };
    }

    ASSERT_EQ(a, 3);
}

TEST(test_scope_guard, test_scope_guard_fail_exception)
{
    int a = 3;

    try
    {
        aeon_scope_fail
        {
            a = 4;
        };

        throw std::runtime_error("fail.");
    }
    catch (...)
    {
    }

    ASSERT_EQ(a, 4);
}

TEST(test_scope_guard, test_scope_guard_fail_exception_multiple)
{
    int a = 3;
    bool second_called = false;
    bool third_called = false;

    try
    {
        aeon_scope_fail
        {
            a = 4;
        };

        aeon_scope_fail
        {
            a = 5;
            second_called = true;
        };

        aeon_scope_fail
        {
            a = 6;
            third_called = true;
        };

        throw std::runtime_error("fail.");
    }
    catch (...)
    {
    }

    ASSERT_EQ(a, 4);
    ASSERT_TRUE(second_called);
    ASSERT_TRUE(third_called);
}

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
#include <aeon/tracelog/tracelog.h>

static void test_func3(float a, const char *str)
{
    aeon_tracelog_scoped();
}

static void test_func2(int arg)
{
    aeon_tracelog_scoped();

    test_func3(static_cast<float>(arg), "Hello");
    test_func3(static_cast<float>(arg + 10), "Bye");
}

static void test_func1(int arg1, float arg2)
{
    aeon_tracelog_scoped();

    for (int i = 0; i < 100; ++i)
    {
        test_func2(arg1);
    }
}

TEST(test_tracelog, test_tracelog_basic_stack)
{
    aeon::tracelog::initialize();

    for (int i = 0; i < 100; ++i)
    {
        test_func1(1, 1.0f);
    }

    aeon::tracelog::write("test.trace");
}

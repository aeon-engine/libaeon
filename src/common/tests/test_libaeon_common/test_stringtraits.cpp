/*
 * Copyright (c) 2012-2017 Robin Degen
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
#include <aeon/common/string_traits.h>

static void check_string(const std::string &value)
{
    EXPECT_EQ(value, aeon::common::string::convert<std::string>::from(value));
    EXPECT_EQ(value, aeon::common::string::convert<std::string>::to(value));
}

static void check_int(const std::string &value, const int int_value)
{
    EXPECT_EQ(int_value, aeon::common::string::convert<int>::from(value));
    EXPECT_EQ(value, aeon::common::string::convert<int>::to(int_value));
}

static void check_bool(const std::string &value, const bool bool_value)
{
    EXPECT_EQ(bool_value, aeon::common::string::convert<bool>::from(value));
    EXPECT_EQ(value, aeon::common::string::convert<bool>::to(bool_value));
}

TEST(test_stringtraits, test_stringtraits_to_string)
{
    check_string("");
    check_string(" ");
    check_string("abc");
    check_string("123");
    check_string("\n");
}

TEST(test_stringtraits, test_stringtraits_to_int)
{
    check_int("0", 0);
    check_int("1", 1);
    check_int("42", 42);
    check_int("1337", 1337);
    check_int("-1", -1);
    check_int("-42", -42);
    check_int("-1337", -1337);
}

TEST(test_stringtraits, test_stringtraits_to_bool)
{
    check_bool("0", false);
    check_bool("1", true);
}

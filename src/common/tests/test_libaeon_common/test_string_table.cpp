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

#include <aeon/common/string_table.h>
#include <gtest/gtest.h>

struct name1_tag
{
};
struct name2_tag
{
};
struct name3_tag
{
};

using name1 = aeon::common::string_table<name1_tag>;
using name2 = aeon::common::string_table<name2_tag>;
using name3 = aeon::common::string_table<name3_tag>;

// Since the string table uses static variables, we can't split up in multiple tests
// since they would fail when ran out of order.
TEST(test_string_table, test_string_table_all)
{
    name1 str("Hello");
    name1 str2("Hello2");
    name2 str3("Bye");

    EXPECT_EQ(name1::size(), 2);
    EXPECT_EQ(name2::size(), 1);
    EXPECT_EQ(name3::size(), 0);

    EXPECT_EQ("Hello", str.str());
    EXPECT_EQ("Hello2", str2.str());
    EXPECT_EQ("Bye", str3.str());

    name1 str4("Hello2");
    EXPECT_EQ(name1::size(), 2);
    EXPECT_EQ("Hello2", str4.str());

    str2 = "Hello3";
    EXPECT_EQ(name1::size(), 3);
    EXPECT_EQ("Hello3", str2.str());
    EXPECT_EQ("Hello2", str4.str());
    EXPECT_EQ(name3::size(), 0);

    name3 str5("AnotherString");
    EXPECT_EQ(name1::size(), 3);
    EXPECT_EQ(name2::size(), 1);
    EXPECT_EQ(name3::size(), 1);

    name1 str_empty;
    EXPECT_EQ(name1::size(), 3);
    EXPECT_EQ("", str_empty.str());

    str_empty = "testing";
    EXPECT_EQ(name1::size(), 4);
    EXPECT_EQ("testing", str_empty.str());

    str_empty = "";
    EXPECT_EQ(name1::size(), 4);
    EXPECT_EQ("", str_empty.str());
}

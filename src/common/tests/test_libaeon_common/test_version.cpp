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
#include <aeon/common/version.h>

TEST(test_version, test_version_create)
{
    aeon::common::version v;
    EXPECT_EQ(v.major, 0);
    EXPECT_EQ(v.minor, 0);
    EXPECT_EQ(v.patch, 0);
    EXPECT_EQ(v.build, 0);
}

TEST(test_version, test_version_create_major_minor)
{
    aeon::common::version v{2, 3};
    EXPECT_EQ(v.major, 2);
    EXPECT_EQ(v.minor, 3);
    EXPECT_EQ(v.patch, 0);
    EXPECT_EQ(v.build, 0);
}

TEST(test_version, test_version_create_major_minor_patch)
{
    aeon::common::version v{2, 3, 4};
    EXPECT_EQ(v.major, 2);
    EXPECT_EQ(v.minor, 3);
    EXPECT_EQ(v.patch, 4);
    EXPECT_EQ(v.build, 0);
}

TEST(test_version, test_version_create_major_minor_patch_build)
{
    aeon::common::version v{2, 3, 4, 5};
    EXPECT_EQ(v.major, 2);
    EXPECT_EQ(v.minor, 3);
    EXPECT_EQ(v.patch, 4);
    EXPECT_EQ(v.build, 5);
}

TEST(test_version, test_version_equals)
{
    aeon::common::version v{2, 3, 4, 5};
    aeon::common::version v2{3, 3, 4, 5};
    aeon::common::version v3{2, 3, 4, 5};

    EXPECT_FALSE(v == v2);
    EXPECT_TRUE(v != v2);
    EXPECT_TRUE(v == v3);
    EXPECT_FALSE(v != v3);
}

TEST(test_version, test_version_compare)
{
    aeon::common::version v{2, 3, 4, 5};
    aeon::common::version v2{2, 3, 4, 6};
    aeon::common::version v3{3, 3, 4, 5};
    aeon::common::version v4{3, 3, 4, 5};

    EXPECT_TRUE(v < v2);
    EXPECT_FALSE(v > v2);
    EXPECT_TRUE(v < v3);
    EXPECT_FALSE(v > v3);
    EXPECT_TRUE(v2 < v3);
    EXPECT_FALSE(v2 > v3);

    EXPECT_FALSE(v3 < v4);
    EXPECT_FALSE(v3 > v4);
    EXPECT_TRUE(v3 <= v4);
    EXPECT_TRUE(v3 >= v4);
}

TEST(test_version, test_version_string)
{
    aeon::common::version v{2, 3, 4, 5};
    aeon::common::version v2{2, 3, 4, 6};
    aeon::common::version v3{3, 3, 4, 5};

    EXPECT_EQ("2.3.4.5", v.str());
    EXPECT_EQ("2.3.4.6", v2.str());
    EXPECT_EQ("3.3.4.5", v3.str());
}

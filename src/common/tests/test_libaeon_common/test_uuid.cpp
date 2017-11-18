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
#include <aeon/common/uuid.h>

TEST(test_common, test_uuid_default_nil)
{
    aeon::common::uuid uuid;
    ASSERT_TRUE(uuid.is_nil());
}

TEST(test_common, test_uuid_is_nil)
{
    aeon::common::uuid uuid;
    ASSERT_TRUE(uuid.is_nil());

    uuid.data[0] = 1;
    ASSERT_FALSE(uuid.is_nil());

    uuid.data[0] = 0;
    ASSERT_TRUE(uuid.is_nil());
}

TEST(test_common, test_uuid_random)
{
    auto uuid = aeon::common::uuid::generate();
    ASSERT_FALSE(uuid.is_nil());

    for (int i = 0; i < 100; ++i)
    {
        auto uuid2 = aeon::common::uuid::generate();
        ASSERT_NE(uuid, uuid2);
    }
}

TEST(test_common, test_uuid_nil_string)
{
    ASSERT_TRUE(aeon::common::uuid("00000000-0000-0000-0000-000000000000").is_nil());
    ASSERT_TRUE(aeon::common::uuid("{00000000-0000-0000-0000-000000000000}").is_nil());
    ASSERT_TRUE(aeon::common::uuid("00000000000000000000000000000000").is_nil());
    ASSERT_TRUE(aeon::common::uuid("{00000000000000000000000000000000}").is_nil());
    ASSERT_ANY_THROW(aeon::common::uuid("0").is_nil());
}

TEST(test_common, test_uuid_from_and_to_string)
{
    auto str = "00000000-0000-0000-0000-000000000000";
    auto uuid = aeon::common::uuid("00000000-0000-0000-0000-000000000000");
    ASSERT_EQ(str, uuid.str());
}

TEST(test_common, test_uuid_from_and_to_string_random)
{
    for (int i = 0; i < 100; ++i)
    {
        auto uuid = aeon::common::uuid::generate();
        auto str = uuid.str();

        auto uuid2 = aeon::common::uuid(str);

        ASSERT_EQ(uuid, uuid2);
        ASSERT_EQ(str, uuid2.str());
    }
}

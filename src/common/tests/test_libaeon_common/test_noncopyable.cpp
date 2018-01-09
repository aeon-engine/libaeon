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
#include <aeon/common/noncopyable.h>

#include <type_traits>

TEST(test_noncopyable, test_noncopyable_create)
{
    ASSERT_NO_THROW(aeon::common::noncopyable a;);
}

TEST(test_noncopyable, test_noncopyable_move_create)
{
    ASSERT_NO_THROW(auto a = aeon::common::noncopyable());
}

TEST(test_noncopyable, test_noncopyable_has_virtual_destructor)
{
    auto is_non_copyable = std::has_virtual_destructor<aeon::common::noncopyable>::value;
    EXPECT_TRUE(is_non_copyable);
}

TEST(test_noncopyable, test_noncopyable_is_not_copy_constructable)
{
    auto is_copy_constructible = std::is_copy_constructible<aeon::common::noncopyable>::value;
    EXPECT_FALSE(is_copy_constructible);

    auto is_trivially_copy_constructible = std::is_trivially_copy_constructible<aeon::common::noncopyable>::value;
    EXPECT_FALSE(is_trivially_copy_constructible);

    auto is_nothrow_copy_constructible = std::is_nothrow_copy_constructible<aeon::common::noncopyable>::value;
    EXPECT_FALSE(is_nothrow_copy_constructible);
}

TEST(test_noncopyable, test_noncopyable_is_not_copy_assignable)
{
    auto is_copy_assignable = std::is_copy_assignable<aeon::common::noncopyable>::value;
    EXPECT_FALSE(is_copy_assignable);

    auto is_trivially_copy_assignable = std::is_trivially_copy_assignable<aeon::common::noncopyable>::value;
    EXPECT_FALSE(is_trivially_copy_assignable);

    auto is_nothrow_copy_assignable = std::is_nothrow_copy_assignable<aeon::common::noncopyable>::value;
    EXPECT_FALSE(is_nothrow_copy_assignable);
}

TEST(test_noncopyable, test_noncopyable_is_move_assignable)
{
    auto is_move_assignable = std::is_move_assignable<aeon::common::noncopyable>::value;
    EXPECT_TRUE(is_move_assignable);

    auto is_nothrow_move_assignable = std::is_nothrow_move_assignable<aeon::common::noncopyable>::value;
    EXPECT_TRUE(is_nothrow_move_assignable);
}

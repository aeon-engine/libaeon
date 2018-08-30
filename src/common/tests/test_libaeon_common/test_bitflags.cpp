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
#include <aeon/common/bitflags.h>

using namespace aeon;

template <typename T>
static void check_get_bit(const T input, const unsigned int bit, const T expected)
{
    EXPECT_EQ(expected, common::get_bit<T>(input, bit));
}

TEST(test_bitflags, test_bitflags_get_bit)
{
    check_get_bit(0x00, 0, 0);
    check_get_bit(0x00, 1, 0);
    check_get_bit(0x00, 8, 0);
    check_get_bit(0x00, 15, 0);

    check_get_bit(0x0001, 0, 1);
    check_get_bit(0x0001, 1, 0);
    check_get_bit(0x0001, 2, 0);
    check_get_bit(0x0001, 8, 0);

    check_get_bit(0xAAAA, 0, 0);
    check_get_bit(0xAAAA, 1, 1);
    check_get_bit(0xAAAA, 2, 0);
    check_get_bit(0xAAAA, 3, 1);
    check_get_bit(0xAAAA, 4, 0);
    check_get_bit(0xAAAA, 5, 1);
    check_get_bit(0xAAAA, 6, 0);
    check_get_bit(0xAAAA, 7, 1);
}

TEST(test_bitflags, test_bitflags_mask)
{
    const auto val = 0x12345678abcdef01u;
    EXPECT_EQ(0x01, common::mask_u8(val));
    EXPECT_EQ(0xef01, common::mask_u16(val));
    EXPECT_EQ(0xabcdef01, common::mask_u32(val));
    EXPECT_EQ(val, common::mask_u64(val));
}

// TODO: Add more unittests for bitflags.

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
#include <aeon/common/endianness.h>

static void check_swap8(std::uint8_t value, std::uint8_t expected)
{
    EXPECT_EQ(expected, aeon::common::endianness::swap(value));
}

static void check_swap16(std::uint16_t value, std::uint16_t expected)
{
    EXPECT_EQ(expected, aeon::common::endianness::swap(value));
    EXPECT_EQ(expected, aeon::common::endianness::swap16(value));
}

static void check_swap32(std::uint32_t value, std::uint32_t expected)
{
    EXPECT_EQ(expected, aeon::common::endianness::swap(value));
    EXPECT_EQ(expected, aeon::common::endianness::swap32(value));
}

static void check_swap64(std::uint64_t value, std::uint64_t expected)
{
    EXPECT_EQ(expected, aeon::common::endianness::swap(value));
    EXPECT_EQ(expected, aeon::common::endianness::swap64(value));
}

TEST(test_endianness, test_endianness_swap8)
{
    check_swap8(0x00, 0x00);
    check_swap8(0x01, 0x01);
    check_swap8(0xAB, 0xAB);
    check_swap8(0xFF, 0xFF);
}

TEST(test_endianness, test_endianness_swap16)
{
    check_swap16(0x0000, 0x0000);
    check_swap16(0x0001, 0x0100);
    check_swap16(0x0101, 0x0101);
    check_swap16(0xABCD, 0xCDAB);
    check_swap16(0xEF12, 0x12EF);
    check_swap16(0xFFFF, 0xFFFF);
}

TEST(test_endianness, test_endianness_swap32)
{
    check_swap32(0x00000000, 0x00000000);
    check_swap32(0x00000001, 0x01000000);
    check_swap32(0x01010101, 0x01010101);
    check_swap32(0x12ABCDEF, 0xEFCDAB12);
    check_swap32(0x3456789A, 0x9A785634);
    check_swap32(0xFFFFFFFF, 0xFFFFFFFF);
}

TEST(test_endianness, test_endianness_swap64)
{
    check_swap64(0x0000000000000000, 0x0000000000000000);
    check_swap64(0x0000000000000001, 0x0100000000000000);
    check_swap64(0x0101010101010101, 0x0101010101010101);
    check_swap64(0x0123456789ABCDEF, 0xEFCDAB8967452301);
    check_swap64(0x12ABCDEF12ABCDEF, 0xEFCDAB12EFCDAB12);
    check_swap64(0x3456789A3456789A, 0x9A7856349A785634);
    check_swap64(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
}

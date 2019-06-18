// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/bits.h>
#include <gtest/gtest.h>

using namespace aeon;

template <typename T>
static void check_get_bit(const T input, const unsigned int bit, const T expected)
{
    EXPECT_EQ(expected, common::bits::get<T>(input, bit));
}

TEST(test_bits, test_bitflags_get_bit)
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

TEST(test_bits, test_bitflags_mask)
{
    const auto val = 0x12345678abcdef01u;
    EXPECT_EQ(0x01, common::bits::mask_u8(val));
    EXPECT_EQ(0xef01, common::bits::mask_u16(val));
    EXPECT_EQ(0xabcdef01, common::bits::mask_u32(val));
    EXPECT_EQ(val, common::bits::mask_u64(val));
}

// TODO: Add more unittests for bits.

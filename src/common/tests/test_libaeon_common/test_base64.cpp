// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/base64.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_bits, test_base64_encode)
{
    EXPECT_EQ(common::base64::encode(""), "");
    EXPECT_EQ(common::base64::encode(" "), "IA==");
    EXPECT_EQ(common::base64::encode("  "), "ICA=");
    EXPECT_EQ(common::base64::encode("   "), "ICAg");
    EXPECT_EQ(common::base64::encode("This is a test"), "VGhpcyBpcyBhIHRlc3Q=");
}

void check_decode(const std::string_view input)
{
    const auto result = common::base64::encode(input);
    EXPECT_EQ(common::base64::decode_string(result), input);
}

TEST(test_bits, test_base64_decode)
{
    check_decode("");
    check_decode(" ");
    check_decode("  ");
    check_decode("   ");
    check_decode("This is a test");
}

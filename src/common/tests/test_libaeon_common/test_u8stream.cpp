// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/common/u8_stream.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>

TEST(test_u8stream, test_u8stream_stringstream)
{
    std::stringstream ss;
    ss << std::u8string_view{u8"This is a string"};
    EXPECT_EQ(ss.str(), "This is a string");
}

TEST(test_u8stream, test_u8stream_iostream)
{
    std::cout << std::u8string_view{u8"This is a string.\n"};
    std::cout << std::u8string_view{u8"らき☆すた, Raki☆Suta.\n"};
}

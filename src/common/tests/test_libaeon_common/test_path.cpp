// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/common/path.h>
#include <aeon/common/platform.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_path, test_relative_to_basepath)
{
#if (AEON_PLATFORM_OS_WINDOWS)
    EXPECT_EQ("C:\\MyDir\\Data\\Test.txt", common::path::absolute_path("C:\\MyDir", "Data\\Test.txt"));
#else
    EXPECT_EQ("/MyDir/Data/Test.txt", common::path::absolute_path("/MyDir", "Data/Test.txt"));
#endif
}

TEST(test_path, test_relative_to_basepath_higher)
{
#if (AEON_PLATFORM_OS_WINDOWS)
    EXPECT_EQ("C:\\MyDir\\Test.txt", common::path::absolute_path("C:\\MyDir\\Data", "..\\Test.txt"));
#else
    EXPECT_EQ("/MyDir/Test.txt", common::path::absolute_path("/MyDir/Data", "../Test.txt"));
#endif
}

TEST(test_path, test_already_absolute)
{
#if (AEON_PLATFORM_OS_WINDOWS)
    EXPECT_EQ("C:\\Data\\Test.txt", common::path::absolute_path("C:\\MyDir", "C:\\Data\\Test.txt"));
#else
    EXPECT_EQ("/Data/Test.txt", common::path::absolute_path("/MyDir", "/Data/Test.txt"));
#endif
}

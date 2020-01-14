// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/version.h>
#include <gtest/gtest.h>

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

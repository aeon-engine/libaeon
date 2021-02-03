// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/chrono/timezone.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_chrono, timezone_enumerate)
{
    const auto timezones = chrono::timezone::enumerate();
    EXPECT_FALSE(std::empty(timezones));
}

TEST(test_chrono, timezone_compare)
{
    const auto tz1 = chrono::timezone::create("Europe/Amsterdam");
    const auto tz2 = chrono::timezone::create("Europe/London");
    EXPECT_FALSE(tz1 == tz2);
    EXPECT_TRUE(tz1 != tz2);

    const auto tz3 = chrono::timezone::create("Europe/Amsterdam");
    EXPECT_TRUE(tz1 == tz3);
    EXPECT_FALSE(tz1 != tz3);

    const auto tz4 = chrono::timezone::create("Etc/GMT");
    const auto tz5 = chrono::timezone::create("Etc/GMT+0");
    const auto tz6 = chrono::timezone::create("Etc/UTC");
    EXPECT_TRUE(tz4 == tz5);
    EXPECT_FALSE(tz4 != tz5);
    EXPECT_TRUE(tz4 == tz6);
    EXPECT_FALSE(tz4 != tz6);
    EXPECT_TRUE(tz5 == tz6);
    EXPECT_FALSE(tz5 != tz6);
}

TEST(test_chrono, timezone_uses_dst)
{
    const auto tz1 = chrono::timezone::create("Europe/Amsterdam");
    EXPECT_TRUE(tz1.uses_dst());

    const auto tz2 = chrono::timezone::create("Etc/UTC");
    EXPECT_FALSE(tz2.uses_dst());

    const auto tz3 = chrono::timezone::create("Etc/GMT");
    EXPECT_FALSE(tz3.uses_dst());
}

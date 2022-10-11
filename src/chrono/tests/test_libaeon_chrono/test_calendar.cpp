// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/chrono/calendar.h>
#include <aeon/common/platform.h>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace aeon;
using namespace std::chrono_literals;

void test_calendar_systemclock_now(chrono::timezone timezone)
{
    const auto expected = std::chrono::system_clock::now();
    const chrono::calendar c{std::move(timezone), expected};

    // The calendar has millisecond precision, but system_clock::now() can return a value with higher precision,
    // which is lost inside the calendar class. We must cast to milliseconds to compare the values properly.
    EXPECT_EQ(std::chrono::duration_cast<std::chrono::milliseconds>(expected.time_since_epoch()),
              std::chrono::duration_cast<std::chrono::milliseconds>(c.get().time_since_epoch()));
}

TEST(test_chrono, test_calendar_get_utc)
{
    test_calendar_systemclock_now(chrono::timezone::gmt());
    test_calendar_systemclock_now(chrono::timezone::local_time());
    test_calendar_systemclock_now(chrono::timezone::create("Europe/Amsterdam"));
    test_calendar_systemclock_now(chrono::timezone::create("America/New_York"));
}

TEST(test_chrono, test_calendar_get_parts_utc)
{
    const auto expected = std::chrono::system_clock::now();
    const chrono::calendar c{chrono::timezone::gmt(), expected};

    const auto expected_time_t = std::chrono::system_clock::to_time_t(expected);
    tm expected_tm{};

#if (AEON_PLATFORM_OS_WINDOWS)
    gmtime_s(&expected_tm, &expected_time_t);
#else
    gmtime_r(&expected_time_t, &expected_tm);
#endif

    EXPECT_EQ(expected_tm.tm_year + 1900, c.get_year());
    EXPECT_EQ(expected_tm.tm_mon + 1, c.get_month());
    EXPECT_EQ(expected_tm.tm_mday, c.get_date());
    EXPECT_EQ(expected_tm.tm_hour, c.get_hour());
    EXPECT_EQ(expected_tm.tm_min, c.get_minute());
}

TEST(test_chrono, test_calendar_get_parts_local)
{
    const auto expected = std::chrono::system_clock::now();
    const chrono::calendar c{chrono::timezone::local_time(), expected};

    const auto expected_time_t = std::chrono::system_clock::to_time_t(expected);
    tm expected_tm{};

#if (AEON_PLATFORM_OS_WINDOWS)
    localtime_s(&expected_tm, &expected_time_t);
#else
    localtime_r(&expected_time_t, &expected_tm);
#endif

    EXPECT_EQ(expected_tm.tm_year + 1900, c.get_year());
    EXPECT_EQ(expected_tm.tm_mon + 1, c.get_month());
    EXPECT_EQ(expected_tm.tm_mday, c.get_date());
    EXPECT_EQ(expected_tm.tm_hour, c.get_hour());
    EXPECT_EQ(expected_tm.tm_min, c.get_minute());
}

TEST(test_chrono, test_calendar_set_time_manual)
{
    const chrono::calendar c{chrono::timezone::local_time(), 1987, 9, 8, 13, 37};

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(13, c.get_hour());
    EXPECT_EQ(37, c.get_minute());
}

TEST(test_chrono, test_calendar_add_time)
{
    chrono::calendar c{chrono::timezone::local_time(), 1987, 9, 8, 13, 37};

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(13, c.get_hour());
    EXPECT_EQ(37, c.get_minute());

    c += 60s;

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(13, c.get_hour());
    EXPECT_EQ(38, c.get_minute());

    c += 10h;

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(23, c.get_hour());
    EXPECT_EQ(38, c.get_minute());

    c += 1h;

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(9, c.get_date());
    EXPECT_EQ(0, c.get_hour());
    EXPECT_EQ(38, c.get_minute());
}

TEST(test_chrono, test_calendar_change_timezone)
{
    // Note that +2 here means it's behind GMT. In the "Etc" area, zones west of GMT have a positive sign and those east
    // have a negative sign in their name (e.g "Etc/GMT-14" is 14 hours ahead of GMT).
    EXPECT_FALSE(chrono::timezone::create("Etc/GMT+2").uses_dst());
    EXPECT_FALSE(chrono::timezone::create("Etc/GMT").uses_dst());

    chrono::calendar c{chrono::timezone::create("Etc/GMT+2"), 1987, 9, 8, 13, 37};

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(13, c.get_hour());
    EXPECT_EQ(37, c.get_minute());

    c.set_timezone(chrono::timezone::create("Etc/GMT"));

    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(15, c.get_hour());
    EXPECT_EQ(37, c.get_minute());
}

TEST(test_chrono, test_equal)
{
    const auto date1 = chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 1987, 9, 8, 13, 37};
    const auto date2 = date1;

    EXPECT_TRUE(date1 == date2);
    EXPECT_FALSE(date1 != date2);

    const auto date3 = chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 1988, 9, 8, 13, 37};

    EXPECT_FALSE(date1 == date3);
    EXPECT_TRUE(date1 != date3);
    EXPECT_FALSE(date2 == date3);
    EXPECT_TRUE(date2 != date3);

    const auto date4 = chrono::calendar{chrono::timezone::create("Etc/GMT"), 1987, 9, 8, 15, 37};

    EXPECT_TRUE(date1 == date4);
    EXPECT_FALSE(date1 != date4);
    EXPECT_TRUE(date2 == date4);
    EXPECT_FALSE(date2 != date4);
    EXPECT_FALSE(date3 == date4);
    EXPECT_TRUE(date3 != date4);
}

TEST(test_chrono, test_calendar_sorting)
{
    const auto date1 = chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 1987, 9, 8, 13, 37};
    const auto date2 = chrono::calendar{chrono::timezone::create("Etc/GMT"), 1987, 9, 8, 15, 38};
    const auto date3 = chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 2003, 12, 3, 14, 0};
    const auto date4 = chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 2003, 12, 3, 15, 42};
    const auto date5 = chrono::calendar{chrono::timezone::create("Etc/GMT+2"), 2015, 1, 7, 1, 32};

    std::vector<chrono::calendar> dates;
    dates.push_back(date5);
    dates.push_back(date4);
    dates.push_back(date1);
    dates.push_back(date3);
    dates.push_back(date2);
    std::sort(std::begin(dates), std::end(dates));

    EXPECT_EQ(dates[0], date1);
    EXPECT_EQ(dates[1], date2);
    EXPECT_EQ(dates[2], date3);
    EXPECT_EQ(dates[3], date4);
    EXPECT_EQ(dates[4], date5);

    std::sort(std::begin(dates), std::end(dates), [](const auto &lhs, const auto &rhs) { return lhs > rhs; });

    EXPECT_EQ(dates[0], date5);
    EXPECT_EQ(dates[1], date4);
    EXPECT_EQ(dates[2], date3);
    EXPECT_EQ(dates[3], date2);
    EXPECT_EQ(dates[4], date1);
}

TEST(test_chrono, test_to_iso8601_string)
{
    const chrono::calendar c{chrono::timezone::gmt(), 1987, 9, 8, 13, 37};
    EXPECT_EQ("1987-09-08T13:37:00.000Z", c.to_string());

    const chrono::calendar c2{chrono::timezone::create("Etc/GMT+2"), 1987, 9, 8, 13, 37};
    EXPECT_EQ("1987-09-08T13:37:00.000-02:00", c2.to_string());

    const chrono::calendar c3{chrono::timezone::create("Etc/GMT-2"), 1987, 9, 8, 13, 37};
    EXPECT_EQ("1987-09-08T13:37:00.000+02:00", c3.to_string());
}

TEST(test_chrono, test_from_iso8601_string)
{
    const chrono::calendar c{"1987-09-08T13:37:00.000Z"};
    EXPECT_EQ(1987, c.get_year());
    EXPECT_EQ(9, c.get_month());
    EXPECT_EQ(8, c.get_date());
    EXPECT_EQ(13, c.get_hour());
    EXPECT_EQ(37, c.get_minute());
    EXPECT_EQ("Etc/GMT", c.get_timezone().id());

    const chrono::calendar c2{"1987-09-08T13:37:00.000-02:00"};
    EXPECT_EQ(1987, c2.get_year());
    EXPECT_EQ(9, c2.get_month());
    EXPECT_EQ(8, c2.get_date());
    EXPECT_EQ(13, c2.get_hour());
    EXPECT_EQ(37, c2.get_minute());
    EXPECT_EQ("GMT-02:00", c2.get_timezone().id());

    const chrono::calendar c3{"1987-09-08T13:37:00.000+02:00"};
    EXPECT_EQ(1987, c3.get_year());
    EXPECT_EQ(9, c3.get_month());
    EXPECT_EQ(8, c3.get_date());
    EXPECT_EQ(13, c3.get_hour());
    EXPECT_EQ(37, c3.get_minute());
    EXPECT_EQ("GMT+02:00", c3.get_timezone().id());

    const chrono::calendar c4{chrono::timezone::create("Etc/GMT+2"), 1987, 9, 8, 13, 37};
    const chrono::calendar c5{c4.to_string()};
    EXPECT_EQ(c4, c5);

    const chrono::calendar c6{chrono::timezone::create("Etc/GMT-2"), 1987, 9, 8, 13, 37};
    const chrono::calendar c7{c6.to_string()};
    EXPECT_EQ(c6, c7);

    EXPECT_ANY_THROW(chrono::calendar{"blah blah blah"});
}

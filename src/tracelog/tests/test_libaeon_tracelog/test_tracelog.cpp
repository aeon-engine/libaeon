// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/tracelog/tracelog.h>
#include <thread>
#include <chrono>

static void test_func3(float a, const char *str)
{
    aeon_tracelog_scoped();
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
}

static void test_func2(int arg)
{
    aeon_tracelog_scoped();

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    test_func3(static_cast<float>(arg), "Hello");
    test_func3(static_cast<float>(arg + 10), "Bye");
}

static void test_func1(int arg1, float arg2)
{
    aeon_tracelog_scoped();

    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    for (int i = 0; i < 10; ++i)
    {
        test_func2(arg1);
    }
}

TEST(test_tracelog, test_tracelog_basic_stack)
{
    aeon::tracelog::initialize();

    for (int i = 0; i < 10; ++i)
    {
        test_func1(1, 1.0f);
    }

    aeon::tracelog::write("test.trace");
}

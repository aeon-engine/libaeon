// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/dispatcher.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_dispatcher, test_dispatcher_basic_run)
{
    common::dispatcher dispatcher;

    std::thread t([&]() { dispatcher.run(); });

    bool called1 = false;
    dispatcher.post([&called1]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        called1 = true;
    });

    bool called2 = false;
    dispatcher.post([&called2]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        called2 = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    dispatcher.stop();

    t.join();

    EXPECT_TRUE(called1);
    EXPECT_TRUE(called2);
}

TEST(test_dispatcher, test_dispatcher_call_void)
{
    common::dispatcher dispatcher;

    std::thread t([&]() { dispatcher.run(); });

    bool called = false;
    dispatcher.call([&called]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        called = true;
    });

    EXPECT_TRUE(called);

    dispatcher.stop();
    t.join();
}

TEST(test_dispatcher, test_dispatcher_call_int)
{
    common::dispatcher dispatcher;

    std::thread t([&]() { dispatcher.run(); });

    auto called = false;
    const auto value = dispatcher.call<int>([&called]() {
        called = true;
        return 1337;
    });

    EXPECT_TRUE(called);
    EXPECT_EQ(1337, value);

    dispatcher.stop();
    t.join();
}

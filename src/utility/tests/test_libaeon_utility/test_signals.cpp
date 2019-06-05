// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/utility/signals.h>
#include <gtest/gtest.h>
#include <array>
#include <thread>

TEST(test_signals, test_signals_connect)
{
    aeon::utility::signal<> signal;
    auto connection = signal.connect([]() {});
    EXPECT_GT(connection.get_handle(), 0);
}

TEST(test_signals, test_signals_connection_default_zero)
{
    aeon::utility::signal_connection<> connection;
    EXPECT_EQ(0, connection.get_handle());
}

TEST(test_signals, test_signals_connect_parameters)
{
    aeon::utility::signal<int, int> signal;
    auto connection = signal.connect([](int, int) {});
    EXPECT_GT(connection.get_handle(), 0);
}

TEST(test_signals, test_signals_connect_one_and_call)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    auto connection = signal.connect([&signal_called]() { signal_called = true; });

    signal();

    EXPECT_TRUE(signal_called);
}

TEST(test_signals, test_signals_connect_multiple_and_call)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    auto connection1 = signal.connect([&signal_called]() { signal_called = true; });
    auto connection2 = signal.connect([&signal_called2]() { signal_called2 = true; });
    auto connection3 = signal.connect([&signal_called3]() { signal_called3 = true; });

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_TRUE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_connect_one_and_call_parameters)
{
    aeon::utility::signal<int, int> signal;

    bool signal_called = false;
    int value1 = 0;
    int value2 = 0;
    auto connection = signal.connect([&signal_called, &value1, &value2](int val1, int val2) {
        signal_called = true;
        value1 = val1;
        value2 = val2;
    });

    signal(42, 1337);

    EXPECT_TRUE(signal_called);
    EXPECT_EQ(42, value1);
    EXPECT_EQ(1337, value2);
}

TEST(test_signals, test_signals_connect_multiple_and_call_with_disconnect)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    auto connection1 = signal.connect([&signal_called]() { signal_called = true; });
    auto connection2 = signal.connect([&signal_called2]() { signal_called2 = true; });
    auto connection3 = signal.connect([&signal_called3]() { signal_called3 = true; });

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_TRUE(signal_called2);
    EXPECT_TRUE(signal_called3);

    signal_called = false;
    signal_called2 = false;
    signal_called3 = false;

    signal.disconnect(connection2);

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_FALSE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_connect_multiple_and_call_scoped_disconnect)
{
    aeon::utility::signal<> signal;

    bool signal_called = false;
    bool signal_called2 = false;
    bool signal_called3 = false;

    aeon::utility::scoped_signal_connection<> connection1;
    aeon::utility::scoped_signal_connection<> connection3;

    {
        connection1 = signal.connect([&signal_called]() { signal_called = true; });
        auto connection2 = signal.connect([&signal_called2]() { signal_called2 = true; });
        connection3 = signal.connect([&signal_called3]() { signal_called3 = true; });

        signal();

        EXPECT_TRUE(signal_called);
        EXPECT_TRUE(signal_called2);
        EXPECT_TRUE(signal_called3);

        signal_called = false;
        signal_called2 = false;
        signal_called3 = false;
    }

    signal();

    EXPECT_TRUE(signal_called);
    EXPECT_FALSE(signal_called2);
    EXPECT_TRUE(signal_called3);
}

TEST(test_signals, test_signals_mt_sync_execution)
{
    aeon::utility::signal_mt<> signal;
    std::array<int, 200> destination{};

    int index = 0;
    auto connection = signal.connect([&index, &destination] { destination[index++]++; });

    std::vector<std::thread> threads;
    auto thread_func = [&signal] {
        for (int i = 0; i < 100; ++i)
        {
            signal();
            std::this_thread::sleep_for(std::chrono::microseconds(0));
        }
    };
    threads.emplace_back(thread_func);
    threads.emplace_back(thread_func);

    for (auto &itr : threads)
        itr.join();

    for (auto &itr : destination)
        EXPECT_EQ(itr, 1);
}

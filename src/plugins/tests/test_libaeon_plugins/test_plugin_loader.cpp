// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/plugins/plugin_loader.h>
#include <itestplugin1.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace aeon;

#ifdef _DEBUG
static constexpr auto plugin_name = "testplugin1_d";
#else
static constexpr auto plugin_name = "testplugin1";
#endif

TEST(test_libaeon_plugins, test_load_non_existent_plugin)
{
    plugins::plugin_loader loader;
    plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>("something_that_doesnt_exist");
    ASSERT_FALSE(plugin.valid());
    ASSERT_FALSE(plugin);
}

TEST(test_libaeon_plugins, test_load_simple_plugin)
{
    plugins::plugin_loader loader;

    bool unloaded_called = false;

    {
        plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>(plugin_name);

        ASSERT_TRUE(plugin.valid());
        ASSERT_TRUE(plugin);

        ASSERT_TRUE(plugin->was_loaded());
        ASSERT_EQ(1337, plugin->test_func1());
        ASSERT_EQ(43, plugin->test_func2(1));

        ASSERT_FALSE(unloaded_called);
        plugin->set_unload_callback([&unloaded_called]() { unloaded_called = true; });
        ASSERT_FALSE(unloaded_called);
    }

    ASSERT_TRUE(unloaded_called);
}

TEST(test_libaeon_plugins, test_load_plugin_cache)
{
    plugins::plugin_loader loader;

    int unload_called_times = 0;

    {
        plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>(plugin_name);
        plugins::scoped_plugin<itestplugin1> plugin2 = loader.load<itestplugin1>(plugin_name);
        plugins::scoped_plugin<itestplugin1> plugin3 = loader.load<itestplugin1>(plugin_name);

        ASSERT_TRUE(plugin);
        ASSERT_TRUE(plugin2);
        ASSERT_TRUE(plugin3);

        ASSERT_EQ(plugin.get(), plugin2.get());
        ASSERT_EQ(plugin2.get(), plugin3.get());

        ASSERT_TRUE(plugin->was_loaded());
        ASSERT_TRUE(plugin2->was_loaded());
        ASSERT_TRUE(plugin3->was_loaded());

        ASSERT_EQ(0, unload_called_times);
        plugin->set_unload_callback([&unload_called_times]() { ++unload_called_times; });
        ASSERT_EQ(0, unload_called_times);
    }

    ASSERT_EQ(1, unload_called_times);
}

TEST(test_libaeon_plugins, test_dll_heap)
{
    plugins::plugin_loader loader;
    plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>(plugin_name);

    ASSERT_TRUE(plugin);

    const auto dll_heap_test_count = 100;
    int dll_heap_delete_count = 0;
    for (auto i = 0; i < dll_heap_test_count; ++i)
    {
        auto heap = plugin->test_dll_heap();
        ASSERT_EQ("Test", heap->a);
        ASSERT_THAT(heap->b, ::testing::ElementsAreArray({1, 3, 3, 7}));

        heap->deleted_callback = [&dll_heap_delete_count]() { ++dll_heap_delete_count; };
    }

    EXPECT_EQ(dll_heap_test_count, dll_heap_delete_count);
}

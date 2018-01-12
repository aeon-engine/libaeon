/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <aeon/plugins/plugin_loader.h>
#include <itestplugin1.h>

using namespace aeon;

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
        plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>("testplugin1");

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
        plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>("testplugin1");
        plugins::scoped_plugin<itestplugin1> plugin2 = loader.load<itestplugin1>("testplugin1");
        plugins::scoped_plugin<itestplugin1> plugin3 = loader.load<itestplugin1>("testplugin1");

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
    plugins::scoped_plugin<itestplugin1> plugin = loader.load<itestplugin1>("testplugin1");

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

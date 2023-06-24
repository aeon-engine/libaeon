// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/size_filter.h>
#include <aeon/streams/filters/seek_offset_filter.h>
#include <aeon/streams/stream_writer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

using namespace aeon;

TEST(test_streams, test_aggregate_device_filter_select)
{
    auto pipeline = streams::memory_device{} | streams::seek_offset_filter<10>{} | streams::size_filter<10>{};
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.device())>, streams::memory_device<std::vector<char>>>));
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.filter<0>())>, streams::seek_offset_filter<10>>));
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.filter<1>())>, streams::size_filter<10>>));
    EXPECT_EQ(2, pipeline.filter_count());
}

TEST(test_streams, test_aggregate_device_filter_select_const)
{
    const auto pipeline = streams::memory_device{} | streams::seek_offset_filter<10>{} | streams::size_filter<10>{};
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.device())>, streams::memory_device<std::vector<char>>>));
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.filter<0>())>, streams::seek_offset_filter<10>>));
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.filter<1>())>, streams::size_filter<10>>));
    EXPECT_EQ(2, pipeline.filter_count());
}

TEST(test_streams, test_aggregate_device_filter_split)
{
    auto pipeline = streams::memory_device{} | streams::seek_offset_filter<10>{} | streams::size_filter<10>{};
    auto pipeline2 = streams::make_split<1>(pipeline) | streams::size_filter<20>{};

    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline2.filter<0>())>, streams::size_filter<20>>));
    EXPECT_EQ(2, pipeline.filter_count());
    EXPECT_EQ(1, pipeline2.filter_count());

    auto pipeline3 = streams::make_split(pipeline) | streams::size_filter<30>{};
    EXPECT_EQ(1, pipeline3.filter_count());
}

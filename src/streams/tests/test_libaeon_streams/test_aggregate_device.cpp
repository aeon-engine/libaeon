// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/zlib_filter.h>
#include <aeon/streams/filters/seek_offset_filter.h>
#include <aeon/streams/stream_writer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

using namespace aeon;

TEST(test_streams, test_aggregate_device_filter_select)
{
    auto pipeline = streams::zlib_decompress_filter{} | (streams::seek_offset_filter<10>{} | streams::memory_device{});
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.device())>, streams::memory_device<std::vector<char>>>));
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.filter<0>())>, streams::zlib_decompress_filter<256>>));
    EXPECT_TRUE((std::is_same_v<std::decay_t<decltype(pipeline.filter<1>())>, streams::seek_offset_filter<10>>));
}

// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/length_prefix_string.h>
#include <aeon/common/signed_sizeof.h>
#include <gtest/gtest.h>
#include <fstream>
#include <utility>
#include <cstring>

using namespace aeon;

TEST(test_streams, test_streams_stream_writer_pod)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    ASSERT_EQ(0, std::size(device));
    writer << 5;
    ASSERT_EQ(aeon_signed_sizeof(int), std::size(device));

    writer << 1.0f;

    ASSERT_EQ(aeon_signed_sizeof(int) + aeon_signed_sizeof(float), device.size());
}

TEST(test_streams, test_streams_stream_writer_stdstring)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    ASSERT_EQ(0, std::size(device));
    writer << "Hello! 12345";
    ASSERT_EQ(12, std::size(device));
}

TEST(test_streams, test_streams_stream_writer_stdstring_prefixed)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    ASSERT_EQ(0, std::size(device));

    std::string val = "Hello! 12345";

    writer << streams::length_prefix_string{val};
    ASSERT_EQ(static_cast<std::streamoff>(std::size(val)) + aeon_signed_sizeof(std::uint32_t), std::size(device));
}

TEST(test_streams, test_streams_stream_writer_vector)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    const std::vector<std::uint32_t> test{1, 2, 3, 4, 5};
    writer << test;

    ASSERT_EQ(static_cast<std::streamoff>(std::size(test)) * aeon_signed_sizeof(std::uint32_t), std::size(device));
}

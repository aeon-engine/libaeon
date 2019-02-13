// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/length_prefix_string.h>
#include <gtest/gtest.h>
#include <fstream>
#include <utility>
#include <cstring>

using namespace aeon;

TEST(test_streams, test_streams_stream_reader_pod)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    writer << 5;
    writer << 1.0f;

    streams::stream_reader reader{device};

    int int_val = 0;
    reader >> int_val;

    float float_val = 0.0f;
    reader >> float_val;

    EXPECT_EQ(5, int_val);
    EXPECT_EQ(1.0f, float_val);
}

TEST(test_streams, test_streams_stream_reader_read_line)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    writer << "Hello! 12345\n";

    streams::stream_reader reader{device};
    std::string line;
    reader >> line;

    EXPECT_EQ("Hello! 12345", line);
}

TEST(test_streams, test_streams_stream_reader_read_vector)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    writer << "Hello! 12345";

    streams::stream_reader reader{device};
    const auto vec = reader.read_to_vector();

    EXPECT_EQ(12, std::size(vec));
}

TEST(test_streams, test_streams_stream_reader_read_string)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    writer << "Hello! 12345";

    streams::stream_reader reader{device};
    const auto str = reader.read_to_string();

    EXPECT_EQ(12, std::size(str));
    EXPECT_EQ("Hello! 12345", str);
}

TEST(test_streams, test_streams_stream_reader_stdstring_prefixed)
{
    auto device = streams::memory_device<char>{};
    streams::stream_writer writer{device};

    ASSERT_EQ(0, std::size(device));

    std::string val = "Hello! 12345";
    writer << streams::length_prefix_string{val};
    ASSERT_EQ(static_cast<std::streamoff>(std::size(val)) + aeon_signed_sizeof(std::uint32_t), std::size(device));

    streams::stream_reader reader{device};

    std::string val2;
    reader >> streams::length_prefix_string{val2};

    EXPECT_EQ(val, val2);
}

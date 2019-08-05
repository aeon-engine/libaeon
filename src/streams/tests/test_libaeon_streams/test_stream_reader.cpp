// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/length_prefix_string.h>
#include <aeon/streams/varint.h>
#include <gtest/gtest.h>
#include <fstream>
#include <utility>
#include <cstring>

using namespace aeon;

TEST(test_streams, test_streams_stream_reader_pod)
{
    auto device = streams::memory_device<std::vector<char>>{};
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
    auto device = streams::memory_device<std::vector<char>>{};
    streams::stream_writer writer{device};

    writer << "Hello! 12345\n";

    streams::stream_reader reader{device};
    std::string line;
    reader >> line;

    EXPECT_EQ("Hello! 12345", line);
}

TEST(test_streams, test_streams_stream_reader_read_vector)
{
    auto device = streams::memory_device<std::vector<char>>{};
    streams::stream_writer writer{device};

    writer << "Hello! 12345";

    streams::stream_reader reader{device};
    const auto vec = reader.read_to_vector<char>();

    EXPECT_EQ(12u, std::size(vec));
}

TEST(test_streams, test_streams_stream_reader_read_string)
{
    auto device = streams::memory_device<std::vector<char>>{};
    streams::stream_writer writer{device};

    writer << "Hello! 12345";

    streams::stream_reader reader{device};
    const auto str = reader.read_to_string();

    EXPECT_EQ(12u, std::size(str));
    EXPECT_EQ("Hello! 12345", str);
}

TEST(test_streams, test_streams_stream_reader_stdstring_prefixed)
{
    auto device = streams::memory_device<std::vector<char>>{};
    streams::stream_writer writer{device};

    ASSERT_EQ(0u, std::size(device));

    std::string val = "Hello! 12345";
    writer << streams::length_prefix_string{val};
    ASSERT_EQ(static_cast<std::streamoff>(std::size(val)) + aeon_signed_sizeof(std::uint32_t), device.tellp());

    streams::stream_reader reader{device};

    std::string val2;
    reader >> streams::length_prefix_string{val2};

    EXPECT_EQ(val, val2);
}

void test_varint(const std::uint64_t value, const int expected_encoding_length)
{
    std::array<char, sizeof(std::uint64_t) + 1> data;
    auto device = streams::span_device<char>{common::span{data}};
    streams::stream_writer writer{device};

    writer << streams::varint{value};

    EXPECT_EQ(device.tellp(), expected_encoding_length);

    streams::stream_reader reader{device};

    std::uint64_t read_value = 0;
    reader >> streams::varint{read_value};

    EXPECT_EQ(value, read_value);
}

TEST(test_streams, test_streams_stream_reader_varint)
{
    test_varint(0, 1);
    test_varint(127, 1);
    test_varint(128, 2);
    test_varint(16383, 2);
    test_varint(16384, 3);
    test_varint(2097151, 3);
    test_varint(2097152, 4);
    test_varint(268435455, 4);
    test_varint(268435456, 5);
}

void test_prefixed_varint_string(const std::string &str)
{
    auto device = streams::memory_device<std::vector<char>>{};
    streams::stream_writer writer{device};

    ASSERT_EQ(0u, std::size(device));

    std::string val = str;
    writer << streams::length_prefix_string<streams::varint>{val};
    ASSERT_EQ(static_cast<std::streamoff>(std::size(val)) + 1, device.tellp());

    streams::stream_reader reader{device};

    std::string val2;
    reader >> streams::length_prefix_string<streams::varint>{val2};

    EXPECT_EQ(val, val2);
}

TEST(test_streams, test_streams_stream_reader_stdstring_varint_prefixed)
{
    test_prefixed_varint_string("hello");
    test_prefixed_varint_string("12345678901234567890123456789012345678901234567890" // 50
                                "12345678901234567890123456789012345678901234567890" // 50
                                "12345678901234567890123456");                       // 26
    test_prefixed_varint_string("12345678901234567890123456789012345678901234567890" // 50
                                "12345678901234567890123456789012345678901234567890" // 50
                                "123456789012345678901234567");                      // 27
}

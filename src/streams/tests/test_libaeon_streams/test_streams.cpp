// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/devices/iostream_device.h>
#include <aeon/streams/tags.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/devices/span_device.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/streams/devices/stdio_device.h>
#include <aeon/streams/filters/filter.h>
#include <aeon/common/type_traits.h>
#include <gtest/gtest.h>
#include <fstream>
#include <utility>
#include <cstring>

using namespace aeon;

struct test_output_filter : streams::filter
{
    struct category : streams::output
    {
    };

    template <typename sink_t>
    auto write(sink_t &sink, const char *data, const std::streamsize size) const -> std::streamsize
    {
        common::span data_span{data, size};
        std::string new_data = "[PREFIX]";
        new_data.insert(std::end(new_data), std::begin(data_span), std::end(data_span));
        new_data += "[POSTFIX]";
        return sink.write(std::data(new_data), std::size(new_data));
    }

    bool test1() const noexcept
    {
        return true;
    }
};

struct test_output_filter2 : streams::filter
{
    struct category : streams::output, streams::input
    {
    };

    template <typename sink_t>
    auto write(sink_t &sink, const char *data, const std::streamsize size) const -> std::streamsize
    {
        common::span data_span{data, size};
        std::string new_data = "<<<";
        new_data.insert(std::end(new_data), std::begin(data_span), std::end(data_span));
        new_data += ">>>";
        return sink.write(std::data(new_data), std::size(new_data));
    }

    template <typename source_t>
    auto read(source_t &sink, char *data, const std::streamsize size) const -> std::streamsize
    {
        auto result = sink.read(data, size);
        data[0] = 'A';
        return result;
    }

    bool test2() const noexcept
    {
        return true;
    }
};

TEST(test_streams, test_streams_stringstream_device)
{
    std::stringstream ss;
    auto pipeline = streams::iostream_device{ss} | test_output_filter2{} | test_output_filter{};

    EXPECT_EQ(2, pipeline.filter_count());
    ASSERT_TRUE(pipeline.filter<1>().test1());
    ASSERT_TRUE(pipeline.filter<0>().test2());

    auto &d = pipeline.device();
    ASSERT_TRUE(d.good());

    if (!pipeline.good())
        FAIL();

    const auto result = pipeline.write("blah", 4);
    EXPECT_EQ("<<<[PREFIX]blah[POSTFIX]>>>", ss.str());

    char test[4];
    pipeline.read(test, 4);
    EXPECT_EQ(0, std::memcmp("A<<[", test, 4));

    pipeline.read(test, 4);
    EXPECT_EQ(0, std::memcmp("AREF", test, 4));
}

TEST(test_streams, test_streams_span_device)
{
    std::array<char, 20> test_array;
    auto device = streams::span_device{common::span{test_array}};

    ASSERT_EQ(5, device.write("12345", 5));
    ASSERT_EQ(5, device.write("67890", 5));
    ASSERT_EQ(5, device.write("abcde", 5));
    ASSERT_EQ(5, device.write("fghijk", 6));

    device.seekp(0, streams::seek_direction::begin);
    ASSERT_EQ(3, device.write("abc", 3));

    std::array<char, 5> read;
    ASSERT_EQ(5, device.read(std::data(read), std::size(read)));
    EXPECT_EQ(0, std::memcmp("abc45", std::data(read), std::size(read)));

    device.seekp(0, streams::seek_direction::begin);
    ASSERT_EQ(4, device.write("9876", 4));

    ASSERT_EQ(5, device.read(std::data(read), std::size(read)));
    EXPECT_EQ(0, std::memcmp("67890", std::data(read), std::size(read)));

    device.seekg(0, streams::seek_direction::begin);
    ASSERT_EQ(5, device.read(std::data(read), std::size(read)));
    EXPECT_EQ(0, std::memcmp("98765", std::data(read), std::size(read)));
}

TEST(test_streams, test_streams_circular_buffer_filter)
{
    std::array<char, 20> test_array;
    auto device = streams::span_device{common::span{test_array}} | streams::circular_buffer_filter{};

    ASSERT_EQ(5, device.write("12345", 5));
    ASSERT_EQ(5, device.write("67890", 5));
    ASSERT_EQ(5, device.write("abcde", 5));
    ASSERT_EQ(5, device.write("ghijk", 5));

    ASSERT_TRUE(device.eof());

    std::array<char, 5> read;
    ASSERT_EQ(5, device.read(std::data(read), std::size(read)));
    EXPECT_EQ(0, std::memcmp("12345", std::data(read), std::size(read)));

    ASSERT_FALSE(device.eof());
}

TEST(test_streams, test_streams_memory_device)
{
    auto device = streams::memory_device<std::vector<char>>{};
    ASSERT_EQ(0, device.size());
    ASSERT_EQ(5, device.write("12345", 5));
    ASSERT_EQ(5, device.size());

    std::array<char, 5> read;
    ASSERT_EQ(5, device.read(std::data(read), std::size(read)));
    EXPECT_EQ(0, std::memcmp("12345", std::data(read), std::size(read)));
}

TEST(test_streams, test_streams_stdio_device)
{
    auto device = streams::stdio_device{};
    device.set_color(streams::color::yellow);
    ASSERT_EQ(15, device.write("This is yellow\n", 15));
    device.set_color(streams::color::red);
    ASSERT_EQ(12, device.write("This is red\n", 12));
    device.set_color(streams::color::blue);
    ASSERT_EQ(13, device.write("This is blue\n", 13));
    device.reset_color();
}

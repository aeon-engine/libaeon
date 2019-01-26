// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>

#include <array>

struct test_fixture_stream_reader_default_data : public ::testing::Test
{
    test_fixture_stream_reader_default_data()
        : fixture_data({{'A', 'B', 'C', 'D', 'E', '\r', '\n', '1', '2', '3', '4'}})
        , fixture_data_written(0)
    {
        fixture_data_written = stream.write(&fixture_data[0], fixture_data.size());
    }

    void SetUp() override
    {
        ASSERT_EQ(fixture_data.size(), fixture_data_written);
        ASSERT_EQ(stream.tell(), fixture_data_written);
        ASSERT_LE(fixture_data_written, stream.size());

        stream.seek(0, aeon::streams::stream::seek_direction::begin);
    }

    aeon::streams::memory_stream stream;
    std::array<std::uint8_t, 11> fixture_data;
    std::size_t fixture_data_written;
};

TEST_F(test_fixture_stream_reader_default_data, test_stream_reader_read_line)
{
    aeon::streams::stream_reader reader(stream);
    ASSERT_EQ("ABCDE", reader.read_line());
    ASSERT_EQ("1234", reader.read_line());
}

TEST_F(test_fixture_stream_reader_default_data, test_stream_reader_read_as_string)
{
    aeon::streams::stream_reader reader(stream);
    ASSERT_EQ("ABCDE\r\n1234", reader.read_as_string());
}

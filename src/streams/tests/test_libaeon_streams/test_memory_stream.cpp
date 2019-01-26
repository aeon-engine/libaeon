// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <aeon/streams/memory_stream.h>

#include <array>

struct test_fixture_memory_stream_default_data : public ::testing::Test
{
    test_fixture_memory_stream_default_data()
        : fixture_data({{'A', 'B', 'C', 'D', 'E'}})
        , fixture_data_written(0)
    {
        fixture_data_written = stream.write(&fixture_data[0], fixture_data.size());
    }

    void SetUp() override
    {
        ASSERT_EQ(fixture_data.size(), fixture_data_written);
        ASSERT_EQ(stream.tell(), fixture_data_written);
        ASSERT_LE(fixture_data_written, stream.size());
    }

    aeon::streams::memory_stream stream;
    std::array<std::uint8_t, 5> fixture_data;
    std::size_t fixture_data_written;
};

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_default_access_mode)
{
    const auto access_mode = stream.get_access_mode();

    ASSERT_TRUE(access_mode.is_set(aeon::streams::access_mode::read_write));
    ASSERT_TRUE(stream.is_readable());
    ASSERT_TRUE(stream.is_writable());
}

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_write)
{
    std::uint8_t data[] = {'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    const auto data_written = stream.write(data, sizeof(data));

    ASSERT_EQ(sizeof(data), data_written);
    ASSERT_EQ(fixture_data_written + sizeof(data), stream.tell());
    ASSERT_LE(stream.size(), fixture_data_written + sizeof(data));
}

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_write_read)
{
    std::vector<std::uint8_t> readbackdata;
    readbackdata.resize(fixture_data_written);

    ASSERT_TRUE(stream.seek(0, aeon::streams::stream::seek_direction::begin));

    const auto data_read = stream.read(&readbackdata[0], readbackdata.size());

    ASSERT_EQ(fixture_data_written, data_read);
    ASSERT_EQ(5, stream.tell());

    ASSERT_THAT(fixture_data, ::testing::ElementsAreArray(readbackdata));
}

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_peek)
{
    bool result = stream.seek(-1, aeon::streams::stream::seek_direction::current);
    ASSERT_TRUE(result);

    std::uint8_t peek_data = 0;
    std::size_t peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('E', peek_data);

    result = stream.seek(-1, aeon::streams::stream::seek_direction::current);
    ASSERT_TRUE(result);

    peek_data = 0;
    peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('D', peek_data);
}

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_seek_begin)
{
    bool result = stream.seek(0, aeon::streams::stream::seek_direction::begin);
    ASSERT_TRUE(result);

    std::uint8_t peek_data = 0;
    std::size_t peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('A', peek_data);

    result = stream.seek(2, aeon::streams::stream::seek_direction::begin);
    ASSERT_TRUE(result);

    peek_data = 0;
    peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('C', peek_data);

    result = stream.seek(fixture_data_written, aeon::streams::stream::seek_direction::begin);

    ASSERT_FALSE(result);
}

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_seek_current)
{
    bool result = stream.seek(-3, aeon::streams::stream::seek_direction::current);
    ASSERT_TRUE(result);

    std::uint8_t peek_data = 0;
    std::size_t peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('C', peek_data);

    result = stream.seek(2, aeon::streams::stream::seek_direction::current);
    ASSERT_TRUE(result);

    peek_data = 0;
    peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('E', peek_data);

    result = stream.seek(-10, aeon::streams::stream::seek_direction::current);

    ASSERT_FALSE(result);

    result = stream.seek(10, aeon::streams::stream::seek_direction::current);

    ASSERT_FALSE(result);
}

TEST_F(test_fixture_memory_stream_default_data, test_memory_stream_seek_end)
{
    bool result = stream.seek(0, aeon::streams::stream::seek_direction::end);
    ASSERT_TRUE(result);

    std::uint8_t peek_data = 0;
    std::size_t peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('E', peek_data);

    result = stream.seek(3, aeon::streams::stream::seek_direction::end);
    ASSERT_TRUE(result);

    peek_data = 0;
    peek_size = stream.peek(&peek_data, 1);

    ASSERT_EQ(1, peek_size);
    ASSERT_EQ('B', peek_data);

    result = stream.seek(10, aeon::streams::stream::seek_direction::end);

    ASSERT_FALSE(result);

    result = stream.seek(-10, aeon::streams::stream::seek_direction::current);

    ASSERT_FALSE(result);
}

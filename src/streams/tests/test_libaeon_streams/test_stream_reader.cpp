/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/streams/memory_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/stream_writer.h>

#include <array>

struct test_fixture_stream_reader_default_data : public ::testing::Test
{
    test_fixture_stream_reader_default_data()
        : fixture_data({{'A', 'B', 'C', 'D', 'E', '\n', '1', '2', '3', '4'}})
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
    std::array<std::uint8_t, 10> fixture_data;
    std::size_t fixture_data_written;
};

TEST_F(test_fixture_stream_reader_default_data, test_stream_reader_read_line)
{
    aeon::streams::stream_reader<aeon::streams::memory_stream> reader(stream);
    ASSERT_EQ("ABCDE", reader.read_line());
    ASSERT_EQ("1234", reader.read_line());
}

TEST_F(test_fixture_stream_reader_default_data, test_stream_reader_read_as_string)
{
    aeon::streams::stream_reader<aeon::streams::memory_stream> reader(stream);
    ASSERT_EQ("ABCDE\n1234", reader.read_as_string());
}

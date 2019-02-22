// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/zlib_filter.h>
#include <aeon/streams/stream_writer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace aeon;

static void test_decompress_data(const std::vector<char> &buffer, const int read_chunk_size,
                                 const std::string &expected)
{
    auto decompress_pipeline = streams::zlib_decompress_filter{} | streams::memory_device{buffer};

    std::string read_data;
    read_data.resize(read_chunk_size);

    std::streamsize offset = 0;
    std::streamsize result = 0;

    std::string total_string;

    do
    {
        result = decompress_pipeline.read(std::data(read_data), std::size(read_data));
        ASSERT_EQ(read_data.substr(0, result), expected.substr(offset, result));
        offset += result;

        total_string += read_data.substr(0, result);
    } while (result == read_chunk_size);

    EXPECT_EQ(total_string, expected);
}

TEST(test_streams, test_zlib_compress_filter_read_write_basic)
{
    auto pipeline = streams::zlib_compress_filter{} | streams::memory_device<std::vector<char>>{};
    EXPECT_EQ(pipeline.size(), 0);

    const std::string data =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut "
        "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
        "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
        "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
        "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut "
        "labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco "
        "laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in "
        "voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat "
        "non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

    streams::stream_writer writer{pipeline};
    writer << data;

    EXPECT_LT(pipeline.size(), static_cast<std::streamoff>(std::size(data)));

    test_decompress_data(pipeline.device().data(), 1, data);
    test_decompress_data(pipeline.device().data(), 2, data);
    test_decompress_data(pipeline.device().data(), 16, data);
    test_decompress_data(pipeline.device().data(), 32, data);
    test_decompress_data(pipeline.device().data(), 128, data);
    test_decompress_data(pipeline.device().data(), 200, data);
    test_decompress_data(pipeline.device().data(), static_cast<int>(std::size(data)), data);
    test_decompress_data(pipeline.device().data(), static_cast<int>(std::size(data) * 2), data);
}

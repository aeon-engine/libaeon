// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/common/signed_sizeof.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

using namespace aeon;

TEST(test_streams, test_circular_buffer_filter_read_write_basic)
{
    auto pipeline = streams::memory_device<std::vector<char>>{100} | streams::circular_buffer_filter{};

    const char data1[] = {'A', 'B', 'C', 'D', 'E'};
    auto result = pipeline.write(data1, sizeof(data1));
    ASSERT_EQ(aeon_signed_sizeof(data1), result);
    ASSERT_EQ(aeon_signed_sizeof(data1), pipeline.size());

    char data1_readback[sizeof(data1)] = {0};
    result = pipeline.read(data1_readback, sizeof(data1_readback));
    ASSERT_EQ(aeon_signed_sizeof(data1_readback), result);
    ASSERT_EQ(0, pipeline.size());

    ASSERT_THAT(data1_readback, ::testing::ElementsAreArray(data1));

    const char data2[] = {'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
    result = pipeline.write(data2, sizeof(data2));
    ASSERT_EQ(aeon_signed_sizeof(data2), result);
    ASSERT_EQ(aeon_signed_sizeof(data2), pipeline.size());

    char data2_readback[sizeof(data2)] = {0};
    result = pipeline.read(data2_readback, sizeof(data2_readback));
    ASSERT_EQ(aeon_signed_sizeof(data2_readback), result);
    ASSERT_EQ(0, pipeline.size());

    ASSERT_THAT(data2_readback, ::testing::ElementsAreArray(data2));
}

TEST(test_streams, test_circular_buffer_filter_read_write)
{
    auto pipeline = streams::memory_device<std::vector<char>>{100} | streams::circular_buffer_filter{};

    char magic_data[100];
    std::memset(magic_data, 'A', sizeof(magic_data));
    auto result = pipeline.write(magic_data, sizeof(magic_data));

    ASSERT_EQ(aeon_signed_sizeof(magic_data), result);
    ASSERT_EQ(aeon_signed_sizeof(magic_data), pipeline.size());

    char readbackdata[sizeof(magic_data)];
    result = pipeline.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(aeon_signed_sizeof(readbackdata), result);
    ASSERT_EQ(0, pipeline.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(magic_data));
}

TEST(test_streams, test_circular_buffer_filter_write_too_big)
{
    auto pipeline = streams::memory_device<std::vector<char>>{100} | streams::circular_buffer_filter{};

    char magic_data[100];
    std::memset(magic_data, 'A', sizeof(magic_data));
    auto result = pipeline.write(magic_data, sizeof(magic_data));

    ASSERT_EQ(aeon_signed_sizeof(magic_data), result);
    ASSERT_EQ(aeon_signed_sizeof(magic_data), pipeline.size());

    // Write data that is too big.
    char fake_data[101];
    std::memset(fake_data, 'B', sizeof(fake_data));
    result = pipeline.write(fake_data, sizeof(fake_data));

    ASSERT_EQ(0, result);
    ASSERT_EQ(aeon_signed_sizeof(magic_data), pipeline.size());

    // Now read back the original data and see if it's untouched
    char readbackdata[sizeof(magic_data)];
    result = pipeline.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(aeon_signed_sizeof(readbackdata), result);
    ASSERT_EQ(0, pipeline.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(magic_data));
}

TEST(test_streams, test_circular_buffer_filter_read_too_big)
{
    auto pipeline = streams::memory_device<std::vector<char>>{100} | streams::circular_buffer_filter{};

    char data[101];
    const auto result = pipeline.read(data, sizeof(data));

    // The read should have failed.
    ASSERT_EQ(0, result);
    ASSERT_EQ(0, pipeline.size());
}

TEST(test_streams, test_circular_buffer_filter_write_wrap_around)
{
    auto pipeline = streams::memory_device<std::vector<char>>{100} | streams::circular_buffer_filter{};

    char magic_data[50];
    std::memset(magic_data, 'A', sizeof(magic_data));

    auto result = pipeline.write(magic_data, sizeof(magic_data));

    ASSERT_EQ(aeon_signed_sizeof(magic_data), result);
    ASSERT_EQ(aeon_signed_sizeof(magic_data), pipeline.size());

    // Now write some more data that would cause an exception
    char magic_data2[60];
    std::memset(magic_data2, 'B', sizeof(magic_data2));

    ASSERT_THROW(pipeline.write(magic_data2, sizeof(magic_data2)), aeon::streams::stream_exception);

    ASSERT_EQ(aeon_signed_sizeof(magic_data), pipeline.size());

    // Try to read back the 50 bytes we wrote earlier
    char readbackdata2[sizeof(magic_data)];
    result = pipeline.read(readbackdata2, sizeof(readbackdata2));

    ASSERT_EQ(aeon_signed_sizeof(readbackdata2), result);
    ASSERT_EQ(0, pipeline.size());

    ASSERT_THAT(readbackdata2, ::testing::ElementsAreArray(magic_data));
}

TEST(test_streams, test_circular_buffer_filter_read_write_multiple)
{
    auto pipeline = streams::memory_device<std::vector<char>>{50} | streams::circular_buffer_filter{};

    const auto base_character = 'A';

    for (int i = 0; i < 26; ++i)
    {
        char magic_data[28];
        std::memset(magic_data, base_character + i, sizeof(magic_data));
        auto result = pipeline.write(magic_data, sizeof(magic_data));

        ASSERT_EQ(aeon_signed_sizeof(magic_data), result);
        ASSERT_EQ(aeon_signed_sizeof(magic_data), pipeline.size());

        char readbackdata[sizeof(magic_data)];
        result = pipeline.read(readbackdata, sizeof(readbackdata));

        ASSERT_EQ(aeon_signed_sizeof(readbackdata), result);
        ASSERT_EQ(0, pipeline.size());

        ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(magic_data));
    }
}

TEST(test_streams, test_circular_buffer_filter_overread)
{
    auto pipeline = streams::memory_device<std::vector<char>>{50} | streams::circular_buffer_filter{};
    ASSERT_EQ(0, pipeline.size());

    char data[5];
    auto result = pipeline.read(data, sizeof(data));

    ASSERT_EQ(0, result);
    ASSERT_EQ(0, pipeline.size());
}

TEST(test_streams, test_circular_buffer_filter_default_size)
{
    auto pipeline = streams::memory_device<std::vector<char>>{10} | streams::circular_buffer_filter{};
    ASSERT_EQ(0, pipeline.size());
}

TEST(test_streams, test_circular_buffer_filter_move_assignment)
{
    auto pipeline = streams::memory_device<std::vector<char>>{10} | streams::circular_buffer_filter{};

    const char data[] = {'A', 'B', 'C', 'D', 'E'};
    auto result = pipeline.write(data, sizeof(data));

    ASSERT_EQ(aeon_signed_sizeof(data), result);
    ASSERT_EQ(aeon_signed_sizeof(data), pipeline.size());

    auto pipeline2 = streams::memory_device<std::vector<char>>{10} | streams::circular_buffer_filter{};
    ASSERT_EQ(0u, pipeline2.size());

    pipeline2 = std::move(pipeline);

    ASSERT_EQ(aeon_signed_sizeof(data), pipeline2.size());

    char readbackdata[sizeof(data)];
    result = pipeline2.read(readbackdata, sizeof(readbackdata));

    ASSERT_EQ(aeon_signed_sizeof(readbackdata), result);
    ASSERT_EQ(0u, pipeline2.size());

    ASSERT_THAT(readbackdata, ::testing::ElementsAreArray(data));
}

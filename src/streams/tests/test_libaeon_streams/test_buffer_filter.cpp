// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/buffer_filter.h>
#include <aeon/common/signed_sizeof.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <array>

using namespace aeon;

template <typename pipeline_t, std::size_t size>
void expect_buffer(pipeline_t &pipeline, const std::array<char, size> &expected)
{
    std::array<char, size> data_readback{};

    const auto result =
        pipeline.read(reinterpret_cast<std::byte *>(std::data(data_readback)), aeon_signed_sizeof(data_readback));
    EXPECT_EQ(static_cast<std::size_t>(result), size);
    EXPECT_THAT(data_readback, ::testing::ElementsAreArray(expected));
    pipeline.seekg(0, streams::seek_direction::begin);
}

template <typename pipeline_t, int size>
void expect_zero_buffer(pipeline_t &pipeline)
{
    std::array<char, size> expected{};
    expect_buffer(pipeline, expected);
}

TEST(test_streams, test_sink_buffer_filter_write)
{
    auto pipeline = streams::memory_device<std::vector<char>>{100} | streams::sink_buffer_filter<10>{};

    const char data1[] = {'A', 'B', 'C', 'D', 'E'};
    auto result = pipeline.write(reinterpret_cast<const std::byte *>(data1), sizeof(data1));
    EXPECT_EQ(result, aeon_signed_sizeof(data1));

    expect_zero_buffer<decltype(pipeline), 5>(pipeline);

    const char data2[] = {'F', 'G', 'H', 'I', 'J'};
    result = pipeline.write(reinterpret_cast<const std::byte *>(data2), sizeof(data2));
    EXPECT_EQ(result, aeon_signed_sizeof(data2));

    const std::array expected_data{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    expect_buffer(pipeline, expected_data);

    const char data3[] = {'K', 'L', 'M', 'N', 'O'};
    result = pipeline.write(reinterpret_cast<const std::byte *>(data3), sizeof(data3));
    EXPECT_EQ(result, aeon_signed_sizeof(data3));

    const std::array expected_data2{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', '\0', '\0', '\0', '\0', '\0'};
    expect_buffer(pipeline, expected_data2);

    pipeline.flush();

    const std::array expected_data3{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};
    expect_buffer(pipeline, expected_data3);
}

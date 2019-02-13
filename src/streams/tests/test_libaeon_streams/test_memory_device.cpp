// Copyright (c) 2012-2019 Robin Degen

#include <aeon/streams/stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/common/signed_sizeof.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace aeon;

struct test_fixture_memory_device_default_data : public ::testing::Test
{
    test_fixture_memory_device_default_data()
        : fixture_data({{'A', 'B', 'C', 'D', 'E'}})
        , fixture_data_written(0)
    {
        fixture_data_written = device.write(std::data(fixture_data), std::size(fixture_data));
    }

    void SetUp() override
    {
        ASSERT_EQ(static_cast<std::streamoff>(fixture_data.size()), fixture_data_written);
        ASSERT_EQ(device.tellp(), fixture_data_written);
        ASSERT_LE(fixture_data_written, device.size());
    }

    streams::memory_device<std::vector<char>> device;
    std::array<char, 5> fixture_data;
    std::streamoff fixture_data_written;
};

TEST_F(test_fixture_memory_device_default_data, test_memory_device_write)
{
    char data[] = {'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    const auto data_written = device.write(data, sizeof(data));

    ASSERT_EQ(aeon_signed_sizeof(data), data_written);
    ASSERT_EQ(fixture_data_written + aeon_signed_sizeof(data), device.tellp());
    ASSERT_LE(device.size(), fixture_data_written + aeon_signed_sizeof(data));
}

TEST_F(test_fixture_memory_device_default_data, test_memory_device_write_read)
{
    std::vector<char> readbackdata;
    readbackdata.resize(fixture_data_written);

    const auto data_read = device.read(std::data(readbackdata), std::size(readbackdata));

    ASSERT_EQ(fixture_data_written, data_read);
    ASSERT_EQ(5, device.tellg());

    ASSERT_THAT(fixture_data, ::testing::ElementsAreArray(readbackdata));
}

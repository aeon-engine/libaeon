// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/crypto/stream_filters/sha256_filter.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <aeon/streams/stream.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <gtest/gtest.h>
#include <vector>

using namespace aeon;
using namespace std::string_literals;

TEST(test_sha256, test_sha256_stream_filter)
{
    const auto expected_part1 = "We are the Borg. Existence, as you know it, "s;
    const auto expected_part2 = "is over. We will add your biological and technological "s;
    const auto expected_part3 = "distinctiveness to our own. Resistance is futile."s;

    std::vector<std::uint8_t> data;
    auto stream = streams::memory_view_device{data} | crypto::stream_filters::sha256_filter{};

    streams::stream_writer writer{stream};
    writer << expected_part1;
    writer << expected_part2;
    writer << expected_part3;

    const std::array<std::uint8_t, 32> expected = {0xd0, 0x55, 0x87, 0x33, 0xd5, 0x7d, 0x8b, 0xf4, 0x22, 0xeb, 0x25,
                                                   0x20, 0xed, 0x93, 0x63, 0x0f, 0x40, 0xba, 0x51, 0x99, 0x34, 0x68,
                                                   0xe0, 0xb2, 0x54, 0x35, 0x98, 0xef, 0xd3, 0x11, 0x68, 0x0a};

    const auto f = stream.filter<0>().finalize();
    EXPECT_EQ(f, expected);

    streams::stream_reader reader{stream};
    EXPECT_EQ(reader.read_to_string(), expected_part1 + expected_part2 + expected_part3);
}

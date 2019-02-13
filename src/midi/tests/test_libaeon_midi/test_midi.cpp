// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <aeon/midi/midi_file_reader.h>
#include <aeon/streams/devices/memory_device.h>
#include <utility>

using namespace aeon;

class test_midi_file_reader : public midi::midi_file_reader
{
public:
    test_midi_file_reader() = default;
    virtual ~test_midi_file_reader() = default;

    std::uint32_t read_vtime(streams::memory_device<std::vector<std::uint8_t>> &stream)
    {
        return midi::midi_file_reader::read_vtime(stream);
    }
};

TEST(test_midi_file, test_read_vtime)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x00};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0u, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime2)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x40};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x40u, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime3)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x7f};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x7fu, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime4)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x81, 0x00};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x80u, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime5)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xC0, 0x00};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x2000u, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime6)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xff, 0x7f};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x3fffu, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime7)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0x81, 0x80, 0x00};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x4000u, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime8)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xff, 0xff, 0x7f};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x1fffffu, reader.read_vtime(mem_stream));
}

TEST(test_midi_file, test_read_vtime9)
{
    test_midi_file_reader reader;
    std::vector<std::uint8_t> data{0xff, 0xff, 0xff, 0x7f};
    streams::memory_device mem_stream{data};

    ASSERT_EQ(0x0fffffffu, reader.read_vtime(mem_stream));
}

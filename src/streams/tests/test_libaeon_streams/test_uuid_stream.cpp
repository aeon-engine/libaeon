// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/common/uuid.h>
#include <aeon/streams/uuid_stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_uuid_stream, test_write_to_stream)
{
    auto uuid = common::uuid::generate();

    streams::memory_device<std::vector<char>> memstream;
    streams::stream_writer writer{memstream};

    writer << uuid;

    ASSERT_EQ(static_cast<std::streamoff>(uuid.size()), memstream.size());
}

TEST(test_uuid_stream, test_read_from_stream)
{
    auto uuid = common::uuid::generate();

    streams::memory_device<std::vector<char>> memstream;
    memstream.write(reinterpret_cast<const char *>(uuid.data.data()), uuid.size());

    streams::stream_reader reader(memstream);

    common::uuid uuid2;
    reader >> uuid2;

    ASSERT_EQ(uuid, uuid2);
}

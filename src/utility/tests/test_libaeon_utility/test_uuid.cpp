// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>
#include <aeon/utility/uuid.h>
#include <aeon/utility/uuid_stream.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/stream_writer.h>

TEST(test_uuid, test_uuid_default_nil)
{
    aeon::utility::uuid uuid;
    ASSERT_TRUE(uuid.is_nil());
}

TEST(test_uuid, test_uuid_is_nil)
{
    aeon::utility::uuid uuid;
    ASSERT_TRUE(uuid.is_nil());

    uuid.data[0] = 1;
    ASSERT_FALSE(uuid.is_nil());

    uuid.data[0] = 0;
    ASSERT_TRUE(uuid.is_nil());
}

TEST(test_uuid, test_uuid_create_nil_is_nil)
{
    auto uuid = aeon::utility::uuid::nil();
    aeon::utility::uuid uuid2;
    ASSERT_TRUE(uuid.is_nil());
    ASSERT_EQ(uuid, uuid2);
}

TEST(test_uuid, test_uuid_random)
{
    auto uuid = aeon::utility::uuid::generate();
    ASSERT_FALSE(uuid.is_nil());

    for (int i = 0; i < 100; ++i)
    {
        auto uuid2 = aeon::utility::uuid::generate();
        ASSERT_NE(uuid, uuid2);
    }
}

TEST(test_uuid, test_uuid_nil_string)
{
    ASSERT_TRUE(aeon::utility::uuid("00000000-0000-0000-0000-000000000000").is_nil());
    ASSERT_TRUE(aeon::utility::uuid("{00000000-0000-0000-0000-000000000000}").is_nil());
    ASSERT_TRUE(aeon::utility::uuid("00000000000000000000000000000000").is_nil());
    ASSERT_TRUE(aeon::utility::uuid("{00000000000000000000000000000000}").is_nil());
    ASSERT_ANY_THROW(aeon::utility::uuid("0").is_nil());
}

TEST(test_uuid, test_uuid_from_and_to_string)
{
    auto str = "00000000-0000-0000-0000-000000000000";
    auto uuid = aeon::utility::uuid("00000000-0000-0000-0000-000000000000");
    ASSERT_EQ(str, uuid.str());
}

TEST(test_uuid, test_uuid_from_and_to_string_random)
{
    for (int i = 0; i < 100; ++i)
    {
        auto uuid = aeon::utility::uuid::generate();
        auto str = uuid.str();

        auto uuid2 = aeon::utility::uuid(str);

        ASSERT_EQ(uuid, uuid2);
        ASSERT_EQ(str, uuid2.str());
    }
}

TEST(test_uuid, test_write_to_stream)
{
    auto uuid = aeon::utility::uuid::generate();

    aeon::streams::memory_device<char> memstream;
    aeon::streams::stream_writer writer{memstream};

    writer << uuid;

    ASSERT_EQ(static_cast<std::streamoff>(uuid.size()), memstream.size());
}

TEST(test_uuid, test_read_from_stream)
{
    auto uuid = aeon::utility::uuid::generate();

    aeon::streams::memory_device<char> memstream;
    memstream.write(reinterpret_cast<const char *>(uuid.data.data()), uuid.size());

    aeon::streams::stream_reader reader(memstream);

    aeon::utility::uuid uuid2;
    reader >> uuid2;

    ASSERT_EQ(uuid, uuid2);
}

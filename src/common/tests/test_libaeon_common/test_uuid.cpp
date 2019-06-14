// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/common/uuid.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_uuid, test_uuid_default_nil)
{
    common::uuid uuid;
    ASSERT_TRUE(uuid.is_nil());
}

TEST(test_uuid, test_uuid_is_nil)
{
    common::uuid uuid;
    ASSERT_TRUE(uuid.is_nil());

    uuid.data[0] = 1;
    ASSERT_FALSE(uuid.is_nil());

    uuid.data[0] = 0;
    ASSERT_TRUE(uuid.is_nil());
}

TEST(test_uuid, test_uuid_create_nil_is_nil)
{
    auto uuid = common::uuid::nil();
    common::uuid uuid2;
    ASSERT_TRUE(uuid.is_nil());
    ASSERT_EQ(uuid, uuid2);
}

TEST(test_uuid, test_uuid_random)
{
    auto uuid = common::uuid::generate();
    ASSERT_FALSE(uuid.is_nil());

    for (int i = 0; i < 100; ++i)
    {
        auto uuid2 = common::uuid::generate();
        ASSERT_NE(uuid, uuid2);
    }
}

TEST(test_uuid, test_uuid_nil_string)
{
    ASSERT_TRUE(common::uuid::parse("00000000-0000-0000-0000-000000000000").is_nil());
    ASSERT_TRUE(common::uuid::parse("{00000000-0000-0000-0000-000000000000}").is_nil());
    ASSERT_TRUE(common::uuid::parse("00000000000000000000000000000000").is_nil());
    ASSERT_TRUE(common::uuid::parse("{00000000000000000000000000000000}").is_nil());
    ASSERT_ANY_THROW(const auto result = common::uuid::parse("0"); (void)result;);
}

TEST(test_uuid, test_uuid_from_and_to_string)
{
    auto str = "00000000-0000-0000-0000-000000000000";
    auto uuid = common::uuid::parse("00000000-0000-0000-0000-000000000000");
    ASSERT_EQ(str, uuid.str());
}

TEST(test_uuid, test_uuid_from_and_to_string_random)
{
    for (int i = 0; i < 100; ++i)
    {
        auto uuid = common::uuid::generate();
        auto str = uuid.str();

        auto uuid2 = common::uuid::parse(str);

        ASSERT_EQ(uuid, uuid2);
        ASSERT_EQ(str, uuid2.str());
    }
}

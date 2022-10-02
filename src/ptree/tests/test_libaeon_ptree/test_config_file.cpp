// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/config_file.h>
#include <aeon/ptree/serialization/serialization_ini.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <gtest/gtest.h>

#include <ptree_unittest_data.h>

using namespace aeon;

TEST(test_ptree_config_file, has_header)
{
    ptree::property_tree pt;
    ptree::config_file config{pt};

    EXPECT_FALSE(config.has_header(u8"test"));
}

TEST(test_ptree_config_file, from_ini_file)
{
    using namespace std::string_literals;

    auto stream = streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "simple.ini"});
    auto result = ptree::serialization::from_ini(stream);

    ptree::config_file config{result};

    EXPECT_TRUE(config.has_header(u8"header1"));
    EXPECT_FALSE(config.has_header(u8"header2"));
    EXPECT_TRUE(config.has_header(u8"another_header"));
    EXPECT_FALSE(config.has_header(u8"anotherheader"));

    EXPECT_TRUE(config.has_entry(u8"header1", u8"value"));
    EXPECT_FALSE(config.has_entry(u8"header2", u8"value"));
    EXPECT_FALSE(config.has_entry(u8"header1", u8"value5"));

    EXPECT_TRUE(config.has_entry(u8"another_header", u8"val"));
    EXPECT_FALSE(config.has_entry(u8"another_header", u8"value"));

    EXPECT_EQ(42, config.get<std::int64_t>(u8"header1", u8"value"));
    EXPECT_EQ(false, config.get<bool>(u8"header1", u8"another_value"));
    EXPECT_EQ(true, config.get<bool>(u8"header1", u8"another_bool"));
    EXPECT_EQ(u8"This is a string", config.get<std::u8string>(u8"header1", u8"string"));
    EXPECT_EQ(1.0, config.get<double>(u8"header1", u8"value2"));
    EXPECT_EQ(42e-1, config.get<double>(u8"header1", u8"value3"));
    EXPECT_EQ(-10, config.get<std::int64_t>(u8"header1", u8"value4"));

    EXPECT_EQ(1337, config.get<std::int64_t>(u8"another_header", u8"val"));
    EXPECT_EQ(common::uuid::parse("f976d1e3-0f0d-4c9c-b7c5-2e31eb4bae89"),
              config.get<common::uuid>(u8"another_header", u8"uuid_value"));

    EXPECT_EQ(std::nullopt, config.get<bool>(u8"header1", u8"value"));
    EXPECT_EQ(42.0, config.get<double>(u8"header1", u8"value"));
    EXPECT_EQ(std::nullopt, config.get<std::u8string>(u8"header1", u8"value"));

    EXPECT_EQ(42, config.get<std::int64_t>(u8"header1", u8"value", 1337));
    EXPECT_EQ(1337, config.get<std::int64_t>(u8"header2", u8"value", 1337));
    EXPECT_EQ(1337, config.get<std::int64_t>(u8"header2", u8"value"));

    config.set(u8"header1", u8"value", 84);
    EXPECT_EQ(84, config.get<std::int64_t>(u8"header1", u8"value"));

    config.set(u8"header1", u8"value5", 9876);
    EXPECT_EQ(9876, config.get<std::int64_t>(u8"header1", u8"value5"));

    config.set(u8"a_completely_new_header", u8"new_value", 12131415);
    EXPECT_EQ(12131415, config.get<std::int64_t>(u8"a_completely_new_header", u8"new_value"));

    config.set(u8"header1", u8"value", u8"Change the type!"s);
    EXPECT_EQ(std::nullopt, config.get<std::int64_t>(u8"header1", u8"value"));
    EXPECT_EQ(u8"Change the type!", config.get<std::u8string>(u8"header1", u8"value"));
}

TEST(test_ptree_config_file, from_scratch)
{
    ptree::property_tree pt;
    ptree::config_file config{pt};

    EXPECT_EQ(std::nullopt, config.get<std::int64_t>(u8"header", u8"value"));
    config.set(u8"header", u8"value", 1337);
    EXPECT_EQ(1337, config.get<std::int64_t>(u8"header", u8"value"));
}

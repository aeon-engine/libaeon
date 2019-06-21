// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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

    EXPECT_FALSE(config.has_header("test"));
}

TEST(test_ptree_config_file, from_ini_file)
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "simple.ini"});
    auto result = ptree::serialization::from_ini(stream);

    ptree::config_file config{result};

    EXPECT_TRUE(config.has_header("header1"));
    EXPECT_FALSE(config.has_header("header2"));
    EXPECT_TRUE(config.has_header("another_header"));
    EXPECT_FALSE(config.has_header("anotherheader"));

    EXPECT_TRUE(config.has_entry("header1", "value"));
    EXPECT_FALSE(config.has_entry("header2", "value"));
    EXPECT_FALSE(config.has_entry("header1", "value5"));

    EXPECT_TRUE(config.has_entry("another_header", "val"));
    EXPECT_FALSE(config.has_entry("another_header", "value"));

    EXPECT_EQ(42, config.get<std::int64_t>("header1", "value"));
    EXPECT_EQ(false, config.get<bool>("header1", "another_value"));
    EXPECT_EQ(true, config.get<bool>("header1", "another_bool"));
    EXPECT_EQ("This is a string", config.get<std::string>("header1", "string"));
    EXPECT_EQ(1.0, config.get<double>("header1", "value2"));
    EXPECT_EQ(42e-1, config.get<double>("header1", "value3"));
    EXPECT_EQ(-10, config.get<std::int64_t>("header1", "value4"));

    EXPECT_EQ(1337, config.get<std::int64_t>("another_header", "val"));
    EXPECT_EQ(common::uuid::parse("f976d1e3-0f0d-4c9c-b7c5-2e31eb4bae89"),
              config.get<common::uuid>("another_header", "uuid_value"));

    EXPECT_EQ(std::nullopt, config.get<bool>("header1", "value"));
    EXPECT_EQ(42.0, config.get<double>("header1", "value"));
    EXPECT_EQ(std::nullopt, config.get<std::string>("header1", "value"));

    EXPECT_EQ(42, config.get<std::int64_t>("header1", "value", 1337));
    EXPECT_EQ(1337, config.get<std::int64_t>("header2", "value", 1337));
    EXPECT_EQ(1337, config.get<std::int64_t>("header2", "value"));

    config.set("header1", "value", 84);
    EXPECT_EQ(84, config.get<std::int64_t>("header1", "value"));

    config.set("header1", "value5", 9876);
    EXPECT_EQ(9876, config.get<std::int64_t>("header1", "value5"));

    config.set("a_completely_new_header", "new_value", 12131415);
    EXPECT_EQ(12131415, config.get<std::int64_t>("a_completely_new_header", "new_value"));

    config.set("header1", "value", "Change the type!");
    EXPECT_EQ(std::nullopt, config.get<std::int64_t>("header1", "value"));
    EXPECT_EQ("Change the type!", config.get<std::string>("header1", "value"));
}

TEST(test_ptree_config_file, from_scratch)
{
    ptree::property_tree pt;
    ptree::config_file config{pt};

    EXPECT_EQ(std::nullopt, config.get<std::int64_t>("header", "value"));
    config.set("header", "value", 1337);
    EXPECT_EQ(1337, config.get<std::int64_t>("header", "value"));
}

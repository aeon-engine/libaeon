// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_ini.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/common/string_utils.h>
#include <gtest/gtest.h>

#include <ptree_unittest_data.h>

using namespace aeon;

static const ptree::property_tree ini_test_pt{
    {{u8"header1", ptree::object{{u8"value1", 100}, {u8"value2", 10.0}, {u8"value3", false}, {u8"value4", true}}},
     {u8"header2", ptree::object{{u8"value_a", 200},
                                 {u8"value_b", 15.0},
                                 {u8"value_c", common::uuid::parse("f976d1e3-0f0d-4c9c-b7c5-2e31eb4bae89")},
                                 {u8"value_d", u8"This is a string test."}}},
     {u8"header3", ptree::object{{u8"value1", u8"This is a string value"},
                                 {u8"value2", u8"This is a string value"},
                                 {u8"value3", u8"This is a string value"},
                                 {u8"value4", u8"This is a string value"}}}}};

TEST(test_ptree, serialize_ini)
{
    const auto str = ptree::serialization::to_ini(ini_test_pt);

    streams::file_source_device stream{AEON_PTREE_UNITTEST_DATA_PATH "serialize_expect.ini"};
    streams::stream_reader reader{stream};

    // Strip all \r's to workaround git's auto line-endings on windows
    auto expected = reader.read_to_string();
    common::string_utils::replace(expected, "\r", "");

    EXPECT_EQ(expected, str);
}

TEST(test_ptree, serialize_deserialize_compare_ini)
{
    const auto str = ptree::serialization::to_ini(ini_test_pt);
    const auto result = ptree::serialization::from_ini(str);

    EXPECT_EQ(result, ini_test_pt);
}

TEST(test_ptree, deserialize_ini)
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "simple.ini"});
    const auto result = ptree::serialization::from_ini(stream);

    const auto &headers = result.object_value();
    EXPECT_EQ(2u, std::size(headers));
    EXPECT_TRUE(headers.contains(u8"header1"));
    EXPECT_TRUE(headers.contains(u8"another_header"));

    const auto &header1 = headers.at(u8"header1").object_value();
    EXPECT_EQ(7u, std::size(header1));
    EXPECT_EQ(42, header1.at(u8"value").integer_value());
    EXPECT_EQ(false, header1.at(u8"another_value").bool_value());
    EXPECT_EQ(true, header1.at(u8"another_bool").bool_value());
    EXPECT_EQ(u8"This is a string", header1.at(u8"string").string_value());
    EXPECT_EQ(1.0, header1.at(u8"value2").double_value());
    EXPECT_EQ(42e-1, header1.at(u8"value3").double_value());
    EXPECT_EQ(-10, header1.at(u8"value4").integer_value());

    const auto &another_header = headers.at(u8"another_header").object_value();
    EXPECT_EQ(2u, std::size(another_header));
    EXPECT_EQ(1337, another_header.at(u8"val").integer_value());
    EXPECT_EQ(common::uuid::parse("f976d1e3-0f0d-4c9c-b7c5-2e31eb4bae89"),
              another_header.at(u8"uuid_value").uuid_value());
}

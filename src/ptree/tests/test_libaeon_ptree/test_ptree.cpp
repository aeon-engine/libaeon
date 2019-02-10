// Copyright (c) 2012-2019 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_json.h>
#include <aeon/ptree/serialization/serialization_abf.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <gtest/gtest.h>

using namespace aeon;

static const ptree::property_tree pt_simple{{{"test", 3}, {"test2", 2.0}, {"test3", "Hello"}}};

static const ptree::property_tree pt_complex{
    {{"test", 3},
     {"test2", 2.0},
     {"test3",
      ptree::object{{"test3", 5},
                    {"he\\llo", ptree::array{1, 2, 3, 4}},
                    {"hello2", ptree::array{true, false, true, true}},
                    {"hello3", ptree::array{ptree::object{{"henk", true}}, ptree::object{{"henk", false}},
                                            ptree::object{{"henk", true}, {"henk2", "string\ttest\nhello"}}}}}}}};

TEST(test_ptree, json_serialize_deserialize_simple)
{
    const auto str = ptree::serialization::to_json(pt_simple);
    const auto pt2 = ptree::serialization::from_json(str);
    const auto str2 = ptree::serialization::to_json(pt2);
    EXPECT_EQ(str, str2);
}

TEST(test_ptree, json_serialize_deserialize_complex)
{
    const auto str = ptree::serialization::to_json(pt_complex);
    const auto pt2 = ptree::serialization::from_json(str);
    const auto str2 = ptree::serialization::to_json(pt2);
    EXPECT_EQ(str, str2);
}

TEST(test_ptree, abf_serialize_deserialize_simple)
{
    const auto data = ptree::serialization::to_abf(pt_simple);
    auto device = streams::make_dynamic_stream(streams::memory_view_device{data});
    const auto pt2 = ptree::serialization::from_abf(device);
    const auto data2 = ptree::serialization::to_abf(pt2);
}

TEST(test_ptree, abf_serialize_deserialize_complex)
{
    const auto data = ptree::serialization::to_abf(pt_complex);
    auto device = streams::make_dynamic_stream(streams::memory_view_device{data});
    const auto pt2 = ptree::serialization::from_abf(device);
    const auto data2 = ptree::serialization::to_abf(pt2);
}

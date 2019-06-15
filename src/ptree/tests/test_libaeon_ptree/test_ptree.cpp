// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_json.h>
#include <aeon/ptree/serialization/serialization_abf.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <aeon/streams/make_string_view_stream.h>
#include <aeon/streams/make_vector_view_stream.h>
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
    auto device = streams::make_string_view_stream(str);
    const auto pt2 = ptree::serialization::from_json(device);
    const auto str2 = ptree::serialization::to_json(pt2);
    EXPECT_EQ(str, str2);
}

TEST(test_ptree, json_serialize_deserialize_complex)
{
    const auto str = ptree::serialization::to_json(pt_complex);
    auto device = streams::make_string_view_stream(str);
    const auto pt2 = ptree::serialization::from_json(device);
    const auto str2 = ptree::serialization::to_json(pt2);
    EXPECT_EQ(str, str2);
}

TEST(test_ptree, abf_serialize_deserialize_simple)
{
    const auto data = ptree::serialization::to_abf(pt_simple);
    auto device = streams::make_vector_view_stream(data);
    const auto pt2 = ptree::serialization::from_abf(device);
    const auto data2 = ptree::serialization::to_abf(pt2);
}

TEST(test_ptree, abf_serialize_deserialize_complex)
{
    const auto data = ptree::serialization::to_abf(pt_complex);
    auto device = streams::make_vector_view_stream(data);
    const auto pt2 = ptree::serialization::from_abf(device);
    const auto data2 = ptree::serialization::to_abf(pt2);
}

TEST(test_ptree, shorthand_at)
{
    ASSERT_NO_THROW(const auto &result = pt_complex.at("test"); (void)result;); // NOLINT(cppcoreguidelines-avoid-goto)
    EXPECT_TRUE(pt_complex.at("test") == 3);
}

TEST(test_ptree, compare_simple)
{
    const auto other = pt_simple;
    EXPECT_TRUE(pt_simple == other);
    EXPECT_FALSE(pt_simple != other);
}

TEST(test_ptree, compare_complex)
{
    const auto other = pt_complex;
    EXPECT_TRUE(pt_complex == other);
    EXPECT_FALSE(pt_complex != other);
}

TEST(test_ptree, compare_different)
{
    EXPECT_FALSE(pt_simple == pt_complex);
    EXPECT_TRUE(pt_simple != pt_complex);
}

TEST(test_ptree, compare_after_change)
{
    auto other = pt_complex;
    EXPECT_TRUE(pt_complex == other);
    EXPECT_FALSE(pt_complex != other);

    other.object_value().emplace("test4", 5);
    EXPECT_FALSE(pt_complex == other);
    EXPECT_TRUE(pt_complex != other);

    other.object_value().erase("test4");
    EXPECT_TRUE(pt_complex == other);
    EXPECT_FALSE(pt_complex != other);
}

TEST(test_ptree, compare_int)
{
    EXPECT_TRUE(pt_complex.object_value().at("test") == 3);
    EXPECT_FALSE(pt_complex.object_value().at("test") != 3);
    EXPECT_TRUE(3 == pt_complex.object_value().at("test"));
    EXPECT_FALSE(3 != pt_complex.object_value().at("test"));

    EXPECT_FALSE(pt_complex.object_value().at("test") == "testing");
    EXPECT_FALSE(pt_complex.object_value().at("test") == 3.0);
}

TEST(test_ptree, compare_double)
{
    EXPECT_TRUE(pt_complex.object_value().at("test2") == 2.0);
    EXPECT_FALSE(pt_complex.object_value().at("test2") != 2.0);
    EXPECT_TRUE(2.0 == pt_complex.object_value().at("test2"));
    EXPECT_FALSE(2.0 != pt_complex.object_value().at("test2"));

    EXPECT_FALSE(pt_complex.object_value().at("test2") == "testing");
    EXPECT_FALSE(pt_complex.object_value().at("test2") == 3);
}

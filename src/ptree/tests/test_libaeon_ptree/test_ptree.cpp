// Copyright (c) 2012-2019 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_json.h>
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_ptree, json_serialize_deserialize_simple)
{
    const ptree::property_tree pt{{{"test", 3}, {"test2", 2.0}, {"test3", "Hello"}}};

    const auto str = ptree::serialization::to_json(pt);
    const auto pt2 = ptree::serialization::from_json(str);
    const auto str2 = ptree::serialization::to_json(pt2);
    EXPECT_EQ(str, str2);
}

TEST(test_ptree, json_serialize_deserialize_complex)
{
    const ptree::property_tree pt{
        {{"test", 3},
         {"test2", 2.0},
         {"test3",
          ptree::object{{"test3", 5},
                        {"he\\llo", ptree::array{1, 2, 3, 4}},
                        {"hello2", ptree::array{true, false, true, true}},
                        {"hello3", ptree::array{ptree::object{{"henk", true}}, ptree::object{{"henk", false}},
                                                ptree::object{{"henk", true}, {"henk2", "string\ttest\nhello"}}}}}}}};

    const auto str = ptree::serialization::to_json(pt);
    const auto pt2 = ptree::serialization::from_json(str);
    const auto str2 = ptree::serialization::to_json(pt2);
    EXPECT_EQ(str, str2);
}

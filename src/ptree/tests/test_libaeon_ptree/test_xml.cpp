// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_xml.h>
#include <aeon/ptree/xml_dom/xml_document.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/devices/file_device.h>
#include <gtest/gtest.h>

#include <ptree_unittest_data.h>

using namespace aeon;

TEST(test_ptree, serialize_xml_parse_simple_xml_file)
{
    auto stream =
        streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "simple_xml.xml"});
    const auto result = ptree::serialization::from_xml(stream);

    ptree::xml_dom::xml_document document{result};

    EXPECT_EQ(ptree::xml_dom::xml_node_type::invalid, document.child(u8"Hello1234").type());
    EXPECT_EQ(ptree::xml_dom::xml_node_type::invalid, document.child(u8"Hello1234").child(u8"Hello12345").type());

    const auto test_xml_node = document.child(u8"test_xml");
    EXPECT_EQ(ptree::xml_dom::xml_node_type::element, test_xml_node.type());

    const auto values_node = test_xml_node.child(u8"values");
    EXPECT_EQ(ptree::xml_dom::xml_node_type::element, values_node.type());

    const auto value_nodes = values_node.children(u8"value");
    EXPECT_EQ(2u, std::size(value_nodes));

    const auto value1_attributes = value_nodes.at(0).attributes();
    EXPECT_EQ(2u, std::size(value1_attributes));

    EXPECT_EQ(u8"3", value1_attributes.at(u8"a").get_value<std::u8string>());
    EXPECT_EQ(3, value1_attributes.at(u8"a").get_value<int>());
    EXPECT_EQ(u8"4", value1_attributes.at(u8"b").get_value<std::u8string>());
    EXPECT_EQ(4, value1_attributes.at(u8"b").get_value<int>());

    const auto value2_attributes = value_nodes.at(1).attributes();
    EXPECT_TRUE(std::empty(value2_attributes));
}

TEST(test_ptree, serialize_xml_parse_simple_xml_with_text)
{
    auto stream =
        streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "xml_with_strings.xml"});
    const auto result = ptree::serialization::from_xml(stream);

    ptree::xml_dom::xml_document document{result};
    const auto children = document.children();

    EXPECT_EQ(1u, std::size(children));
    EXPECT_EQ(u8"node_value", children.at(0).name());
    EXPECT_FALSE(children.at(0).has_value());

    const auto text_values = children.at(0).children();
    EXPECT_EQ(1u, std::size(text_values));

    EXPECT_EQ(ptree::xml_dom::xml_node_type::text, text_values.at(0).type());
    EXPECT_TRUE(text_values.at(0).has_value());
    EXPECT_EQ(u8"This is a string.", text_values.at(0).value());
    EXPECT_EQ(u8"This is a string.", text_values.at(0).value<std::u8string>());
}

TEST(test_ptree, serialize_xml_parse_simple_xml_with_floats)
{
    auto stream =
        streams::make_dynamic_stream(streams::file_source_device{AEON_PTREE_UNITTEST_DATA_PATH "xml_with_floats.xml"});
    const auto result = ptree::serialization::from_xml(stream);

    ptree::xml_dom::xml_document document{result};
    const auto values = document[u8"statistics"].children();
    EXPECT_EQ(3u, std::size(values));

    EXPECT_EQ(15.4f, document[u8"statistics"][u8"min"].child().value<float>());
    EXPECT_EQ(34.1f, document[u8"statistics"][u8"max"].child().value<float>());
    EXPECT_EQ(300.2f, document[u8"statistics"][u8"avg"].child().value<float>());
}

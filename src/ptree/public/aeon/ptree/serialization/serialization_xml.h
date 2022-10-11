// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/exception.h>
#include <aeon/ptree/xml_dom/xml_document.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::ptree::serialization
{

class ptree_xml_deserialize_exception final : public ptree_serialization_exception
{
public:
    explicit ptree_xml_deserialize_exception(common::string message)
        : message_{std::move(message)}
    {
    }

    [[nodiscard]] const auto &message() const noexcept
    {
        return message_;
    }

private:
    common::string message_;
};

void from_xml(streams::idynamic_stream &stream, property_tree &ptree,
              common::string attribute_placeholder = xml_dom::attribute_placeholder_name);
auto from_xml(streams::idynamic_stream &stream,
              common::string attribute_placeholder = xml_dom::attribute_placeholder_name) -> property_tree;
auto from_xml(const common::string &str, common::string attribute_placeholder = xml_dom::attribute_placeholder_name)
    -> property_tree;

} // namespace aeon::ptree::serialization

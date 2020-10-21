// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/exception.h>
#include <aeon/streams/idynamic_stream.h>

namespace aeon::ptree::serialization
{

class ptree_xml_deserialize_exception final : public ptree_serialization_exception
{
public:
    explicit ptree_xml_deserialize_exception(std::string message)
        : message_{std::move(message)}
    {
    }

    [[nodiscard]] const auto &message() const noexcept
    {
        return message_;
    }

private:
    std::string message_;
};

static constexpr auto attribute_placeholder_name = "<xmlattr>";

void from_xml(streams::idynamic_stream &stream, property_tree &ptree,
              std::string attribute_placeholder = attribute_placeholder_name);
auto from_xml(streams::idynamic_stream &stream, std::string attribute_placeholder = attribute_placeholder_name)
    -> property_tree;
auto from_xml(const std::string &str, std::string attribute_placeholder = attribute_placeholder_name) -> property_tree;

} // namespace aeon::ptree::serialization

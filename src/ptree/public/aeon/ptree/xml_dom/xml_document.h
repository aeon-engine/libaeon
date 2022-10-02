// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ptree/xml_dom/xml_node.h>
#include <aeon/ptree/ptree.h>

namespace aeon::ptree::xml_dom
{

static constexpr auto attribute_placeholder_name = u8"<xmlattr>";

class xml_document final : public xml_node
{
public:
    explicit xml_document(const property_tree &pt,
                          std::u8string attribute_placeholder = attribute_placeholder_name) noexcept;
    ~xml_document() noexcept final;

    xml_document(const xml_document &) = delete;
    auto operator=(const xml_document &) -> xml_document & = delete;

    xml_document(xml_document &&) noexcept;
    auto operator=(xml_document &&) noexcept -> xml_document &;

    [[nodiscard]] const auto &attribute_placeholder() const noexcept
    {
        return attribute_placeholder_;
    }

private:
    std::u8string attribute_placeholder_;
};

} // namespace aeon::ptree::xml_dom

// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/ptree/xml_dom/xml_document.h>

namespace aeon::ptree::xml_dom
{

xml_document::xml_document(const property_tree &pt, common::string attribute_placeholder) noexcept
    : xml_node{*this, pt, xml_node_type::document}
    , attribute_placeholder_{std::move(attribute_placeholder)}
{
}

xml_document::~xml_document() noexcept = default;

xml_document::xml_document(xml_document &&) noexcept = default;

auto xml_document::operator=(xml_document &&) noexcept -> xml_document & = default;

} // namespace aeon::ptree::xml_dom

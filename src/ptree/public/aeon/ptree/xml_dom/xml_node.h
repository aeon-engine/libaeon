// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <aeon/variant/converting_variant.h>
#include <vector>
#include <map>
#include <type_traits>

namespace aeon::ptree::xml_dom
{

enum class xml_node_type
{
    invalid,  // Invalid node.
    document, // Root of the xml document
    header,   // The <?xml header
    text,     // Plain text data
    element   // An <element>
};

class xml_document;

class xml_node
{
public:
    virtual ~xml_node() noexcept;

    xml_node(const xml_node &) noexcept;
    auto operator=(const xml_node &) noexcept -> xml_node &;

    xml_node(xml_node &&) noexcept;
    auto operator=(xml_node &&) noexcept -> xml_node &;

    [[nodiscard]] auto type() const noexcept
    {
        return type_;
    }

    [[nodiscard]] auto has_name() const noexcept -> bool;

    [[nodiscard]] auto name() const -> const common::string &;

    [[nodiscard]] auto has_value() const noexcept -> bool;

    template <typename T = common::string>
    [[nodiscard]] auto value() const
    {
        if constexpr (std::is_same_v<T, common::string>)
        {
            return value_impl();
        }
        else
        {
            variant::converting_variant value{value_impl()};
            return value.get_value<T>();
        }
    }

    [[nodiscard]] auto children() const -> std::vector<xml_node>;

    [[nodiscard]] auto children(const common::string_view child_name) const -> std::vector<xml_node>;

    [[nodiscard]] auto child() const noexcept -> xml_node;

    [[nodiscard]] auto child(const common::string_view child_name) const noexcept -> xml_node;

    [[nodiscard]] auto operator[](const common::string_view child_name) const noexcept -> xml_node;

    [[nodiscard]] auto attributes() const -> std::map<common::string, variant::converting_variant>;

protected:
    explicit xml_node(const xml_document &document) noexcept;
    explicit xml_node(const xml_document &document, const property_tree &pt, const xml_node_type type) noexcept;
    explicit xml_node(const xml_document &document, const property_tree &pt, const common::string &name,
                      const xml_node_type type) noexcept;

    [[nodiscard]] auto value_impl() const -> const common::string &;

private:
    const xml_document *document_;
    const property_tree *pt_;
    const common::string *name_;
    xml_node_type type_;
};

} // namespace aeon::ptree::xml_dom

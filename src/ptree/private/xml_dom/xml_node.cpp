// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/ptree/xml_dom/xml_node.h>
#include <aeon/ptree/xml_dom/exception.h>
#include <aeon/ptree/xml_dom/xml_document.h>

namespace aeon::ptree::xml_dom
{

xml_node::~xml_node() noexcept = default;

xml_node::xml_node(const xml_node &) noexcept = default;

auto xml_node::operator=(const xml_node &) noexcept -> xml_node & = default;

xml_node::xml_node(xml_node &&) noexcept = default;

auto xml_node::operator=(xml_node &&) noexcept -> xml_node & = default;

auto xml_node::has_name() const noexcept -> bool
{
    return name_ != nullptr;
}

auto xml_node::name() const -> const common::string &
{
    if (!name_)
        throw xml_dom_exception{};

    return *name_;
}

auto xml_node::has_value() const noexcept -> bool
{
    return pt_ && pt_->is_string();
}

auto xml_node::children() const -> std::vector<xml_node>
{
    return children("");
}

auto xml_node::children(const common::string_view child_name) const -> std::vector<xml_node>
{
    if (type_ != xml_node_type::document && type_ != xml_node_type::element)
        return {};

    if (!pt_ || !pt_->is_array())
        throw xml_dom_exception{};

    const auto &pt_children = pt_->array_value();

    std::vector<xml_node> children;
    children.reserve(std::size(pt_children));

    for (const auto &pt_child : pt_children)
    {
        if (std::empty(child_name) && pt_child.is_string())
        {
            // emplace_back is not possible because the ctor is protected.
            children.push_back(xml_node{*document_, pt_child, xml_node_type::text}); // NOLINT(modernize-use-emplace)
        }
        else if (pt_child.is_object())
        {
            const auto &pt_object = pt_child.object_value();

            if (std::size(pt_object) != 1)
                throw xml_dom_exception{};

            const auto &[name, value] = *pt_object.begin();

            if (name == document_->attribute_placeholder())
                continue;

            if (std::empty(child_name) || name == child_name)
                children.push_back(
                    xml_node{*document_, value, name, xml_node_type::element}); // NOLINT(modernize-use-emplace)
        }
    }

    return children;
}

auto xml_node::child() const noexcept -> xml_node
{
    return child("");
}

auto xml_node::child(const common::string_view child_name) const noexcept -> xml_node
{
    if (type_ != xml_node_type::document && type_ != xml_node_type::element)
        return xml_node{*document_};

    if (!pt_ || !pt_->is_array())
        return xml_node{*document_};

    const auto &pt_children = pt_->array_value();
    for (const auto &pt_child : pt_children)
    {
        if (std::empty(child_name) && pt_child.is_string())
        {
            return xml_node{*document_, pt_child, xml_node_type::text};
        }
        else if (pt_child.is_object())
        {
            const auto &pt_object = pt_child.object_value();

            if (std::size(pt_object) != 1)
                continue;

            const auto &[name, value] = *pt_object.begin();

            if (name == document_->attribute_placeholder())
                continue;

            if (std::empty(child_name) || name == child_name)
                return xml_node{*document_, value, name, xml_node_type::element};
        }
    }

    return xml_node{*document_};
}

auto xml_node::operator[](const common::string_view child_name) const noexcept -> xml_node
{
    return child(child_name);
}

auto xml_node::attributes() const -> std::map<common::string, variant::converting_variant>
{
    if (type_ != xml_node_type::element)
        return {};

    if (!pt_ || !pt_->is_array())
        return {};

    const auto &pt_children = pt_->array_value();
    for (const auto &pt_child : pt_children)
    {
        if (pt_child.is_object())
        {
            const auto &pt_object = pt_child.object_value();

            if (std::size(pt_object) != 1)
                continue;

            const auto &[name, pt_attrib_value] = *pt_object.begin();

            if (!pt_attrib_value.is_object())
                continue;

            if (name != document_->attribute_placeholder())
                continue;

            const auto &pt_attributes = pt_attrib_value.object_value();

            std::map<common::string, variant::converting_variant> attributes;
            for (const auto &[key, value] : pt_attributes)
            {
                if (!value.is_string())
                    throw xml_dom_exception{};

                attributes.emplace(key, value.string_value());
            }

            return attributes;
        }
    }

    return {};
}

auto xml_node::value_impl() const -> const common::string &
{
    if (!pt_ || !pt_->is_string())
        throw xml_dom_exception{};

    return pt_->string_value();
}

xml_node::xml_node(const xml_document &document) noexcept
    : document_{&document}
    , pt_{nullptr}
    , name_{nullptr}
    , type_{xml_node_type::invalid}
{
}

xml_node::xml_node(const xml_document &document, const property_tree &pt, const xml_node_type type) noexcept
    : document_{&document}
    , pt_{&pt}
    , name_{nullptr}
    , type_{type}
{
}

xml_node::xml_node(const xml_document &document, const property_tree &pt, const common::string &name,
                   const xml_node_type type) noexcept
    : document_{&document}
    , pt_{&pt}
    , name_{&name}
    , type_{type}
{
}

} // namespace aeon::ptree::xml_dom

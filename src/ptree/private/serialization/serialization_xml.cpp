// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/ptree/serialization/serialization_xml.h>
#include <aeon/streams/devices/memory_view_device.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/rdp/matchers.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/rdp/parser.h>

namespace aeon::ptree::serialization
{

namespace internal
{

static constexpr auto cdata_begin = u8"<![CDATA[";
static constexpr auto cdata_end = u8"]]>";

static constexpr auto comment_begin = u8"<!--";
static constexpr auto comment_end = u8"-->";

static constexpr auto header_begin = u8"<?xml";
static constexpr auto header_end = u8"?>";

static constexpr auto dtd_begin = u8"<!";

static constexpr auto element_begin = u8'<';
static constexpr auto element_end = u8'>';
static constexpr auto element_self_closing_end = u8"/>";
static constexpr auto element_closing_begin = u8"</";

class xml_parser final
{
public:
    explicit xml_parser(const std::u8string_view &view, std::u8string attribute_placeholder)
        : parser_{view}
        , attribute_placeholder_{std::move(attribute_placeholder)}
    {
    }

    void parse(property_tree &ptree)
    {
        if (rdp::eof(parser_))
            return;

        rdp::skip_byte_order_marker(parser_);

        auto arr = parse_nodes(u8"");

        if (arr.is_error())
        {
            rdp::print_parse_error(arr.error());
            throw ptree_xml_deserialize_exception{arr.error().message()};
        }

        ptree = std::move(arr.value());
    }

private:
    struct attribute final
    {
        std::u8string_view name;
        std::u8string_view value;
    };

    [[nodiscard]] auto parse_attribute_and_value() -> rdp::parse_result<std::u8string_view, attribute>
    {
        rdp::skip_whitespace(parser_);

        const auto attribute_name_result = rdp::match_alnum(parser_);

        if (!attribute_name_result)
            return rdp::parse_error{parser_, u8"Expected attribute name."};

        rdp::skip_whitespace(parser_);

        if (!parser_.check('='))
            return rdp::parse_error{parser_, u8"Expected '='."};

        rdp::skip_whitespace(parser_);

        if (!parser_.check('"'))
            return rdp::parse_error{parser_, u8"Expected '\"'."};

        const auto attribute_value_result = parser_.match_until('"');

        if (!attribute_value_result)
            return rdp::parse_error{parser_, u8"Expected value closed by '\"'."};

        if (!parser_.check('"'))
            return rdp::parse_error{parser_, u8"Expected value closed by '\"'."};

        return rdp::matched{attribute{attribute_name_result.value(), attribute_value_result.value()}};
    }

    [[nodiscard]] auto parse_header() -> rdp::parse_result<std::u8string_view, property_tree>
    {
        if (!rdp::check_whitespace(parser_))
            return rdp::parse_error{parser_, u8"Expected whitespace after <?xml."};

        object obj;

        while (!parser_.check(header_end))
        {
            const auto result = parse_attribute_and_value();

            if (!result)
                return result.error();

            obj.emplace(std::u8string{result.value().name}, std::u8string{result.value().value});
        }

        return rdp::matched{property_tree{object{{u8"?xml", std::move(obj)}}}};
    }

    [[nodiscard]] auto parse_element() -> rdp::parse_result<std::u8string_view, property_tree>
    {
        rdp::skip_whitespace_and_newline(parser_);

        const auto element_name = parser_.match(
            [](const auto c) { return std::isalnum(c) != 0 || c == u8'_' || c == u8'-' || c == u8'.' || c == u8':'; });

        if (!element_name)
            return rdp::parse_error{parser_, u8"Expected element name."};

        rdp::skip_whitespace(parser_);

        object attributes;

        while (!rdp::eof(parser_))
        {
            rdp::skip_whitespace(parser_);

            if (parser_.check(element_self_closing_end))
            {
                if (std::empty(attributes))
                    return rdp::matched{property_tree{object{{std::u8string{element_name.value()}, array{{}}}}}};
                else
                    return rdp::matched{
                        property_tree{object{{std::u8string{element_name.value()},
                                              array{{object{{attribute_placeholder_, std::move(attributes)}}}}}}}};
            }

            if (parser_.check(element_end))
                break;

            const auto result = parse_attribute_and_value();

            if (!result)
                return rdp::parse_error{parser_, u8"Expected attribute or />."};

            attributes.emplace(std::u8string{result.value().name}, std::u8string{result.value().value});
        }

        auto children_result = parse_nodes(std::u8string{element_name.value()});

        if (children_result.is_error())
            return children_result.error();

        auto children = std::move(children_result.value());

        if (!std::empty(attributes))
            children.push_back(object{{attribute_placeholder_, std::move(attributes)}});

        return rdp::matched{property_tree{object{{std::u8string{element_name.value()}, std::move(children)}}}};
    }

    [[nodiscard]] auto parse_cdata() -> rdp::parse_result<std::u8string_view, property_tree>
    {
        rdp::skip_whitespace_and_newline(parser_);
        const auto result = parser_.match_until(cdata_end);

        if (result.is_error())
            return result.error();

        if (!parser_.check(cdata_end))
            return rdp::parse_error{parser_, u8"Expected ]]>."};

        return rdp::matched{property_tree{std::u8string{result.value()}}};
    }

    [[nodiscard]] auto parse_nodes(const std::u8string &parent_node) -> rdp::parse_result<std::u8string_view, array>
    {
        array nodes;

        const auto parent_closing_node =
            std::u8string{element_closing_begin} + parent_node + std::u8string{element_end};

        while (!rdp::eof(parser_))
        {
            // If there is no parent (root of the file), then don't check for the closing tag.
            if (!std::empty(parent_node))
            {
                if (parser_.check(parent_closing_node))
                    break;
            }

            auto result = parse_node();

            if (result.is_unmatched())
                continue;

            if (result.is_error())
                return result.error();

            nodes.push_back(std::move(result.value()));
        }

        return rdp::matched{std::move(nodes)};
    }

    [[nodiscard]] auto parse_node() -> rdp::parse_result<std::u8string_view, property_tree>
    {
        if (parser_.check(cdata_begin))
        {
            return parse_cdata();
        }
        else if (parser_.check(comment_begin))
        {
            if (!parser_.match_until(comment_end))
                return rdp::parse_error{parser_, u8"Unmatched comment section."};

            if (!parser_.check(comment_end))
                return rdp::parse_error{parser_, u8"Unmatched comment section."};
        }
        else if (parser_.check(header_begin))
        {
            return parse_header();
        }
        else if (parser_.check(dtd_begin))
        {
            return rdp::parse_error{parser_, u8"DTD is not yet unsupported."};
        }
        else if (parser_.check(element_begin))
        {
            return parse_element();
        }

        const auto text_result = parser_.match_until('<', rdp::eof_mode::match);

        if (!text_result)
            return rdp::parse_error{parser_, u8"Could not parse XML file."};

        const auto value = common::string::trimmedsv(text_result.value());

        if (std::empty(value))
            return rdp::unmatched{};

        return rdp::matched{property_tree{std::u8string{value}}};
    }

    rdp::parser<std::u8string_view> parser_;
    std::u8string attribute_placeholder_;
};

} // namespace internal

void from_xml(streams::idynamic_stream &stream, property_tree &ptree, std::u8string attribute_placeholder)
{
    streams::stream_reader reader{stream};
    const auto str = reader.read_to_u8string();
    internal::xml_parser parser{str, std::move(attribute_placeholder)};
    parser.parse(ptree);
}

auto from_xml(streams::idynamic_stream &stream, std::u8string attribute_placeholder) -> property_tree
{
    property_tree pt;
    from_xml(stream, pt, std::move(attribute_placeholder));
    return pt;
}

auto from_xml(const std::string &str, std::u8string attribute_placeholder) -> property_tree
{
    auto stream = streams::make_dynamic_stream(streams::memory_view_device{str});
    return from_xml(stream, std::move(attribute_placeholder));
}

} // namespace aeon::ptree::serialization

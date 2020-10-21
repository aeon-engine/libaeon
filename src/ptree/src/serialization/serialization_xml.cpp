// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/ptree/serialization/serialization_xml.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/make_string_view_stream.h>
#include <aeon/rdp/matchers.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/rdp/parser.h>

namespace aeon::ptree::serialization
{

namespace internal
{

static constexpr auto cdata_begin = "<![CDATA[";
static constexpr auto cdata_end = "]]>";

static constexpr auto comment_begin = "<!--";
static constexpr auto comment_end = "-->";

static constexpr auto header_begin = "<?xml";
static constexpr auto header_end = "?>";

static constexpr auto dtd_begin = "<!";

static constexpr auto element_begin = '<';
static constexpr auto element_end = '>';
static constexpr auto element_self_closing_end = "/>";
static constexpr auto element_closing_begin = "</";

class xml_parser final
{
public:
    explicit xml_parser(const std::string_view &view, std::string attribute_placeholder)
        : parser_{view}
        , attribute_placeholder_{std::move(attribute_placeholder)}
    {
    }

    void parse(property_tree &ptree)
    {
        if (rdp::eof(parser_))
            return;

        rdp::skip_byte_order_marker(parser_);

        auto arr = parse_nodes("");

        if (arr.is_error())
        {
            rdp::print_parse_error(arr.error());
            throw ptree_xml_deserialize_exception{arr.error().message()};
        }

        // TODO: This is a hack. There is always a top-level ptree array object with 1 child.
        if (std::size(arr.value()) != 1)
            throw ptree_xml_deserialize_exception{"Parse error."};

        ptree = std::move(arr.value().at(0));
    }

private:
    struct attribute final
    {
        std::string_view name;
        std::string_view value;
    };

    [[nodiscard]] auto parse_attribute_and_value() -> rdp::parse_result<attribute>
    {
        rdp::skip_whitespace(parser_);

        const auto attribute_name_result = rdp::match_alnum(parser_);

        if (!attribute_name_result)
            return rdp::parse_error{parser_, "Expected attribute name."};

        rdp::skip_whitespace(parser_);

        if (!parser_.check('='))
            return rdp::parse_error{parser_, "Expected '='."};

        rdp::skip_whitespace(parser_);

        if (!parser_.check('"'))
            return rdp::parse_error{parser_, "Expected '\"'."};

        const auto attribute_value_result = parser_.match_until('"');

        if (!attribute_value_result)
            return rdp::parse_error{parser_, "Expected value closed by '\"'."};

        if (!parser_.check('"'))
            return rdp::parse_error{parser_, "Expected value closed by '\"'."};

        return rdp::matched{attribute{attribute_name_result.value(), attribute_value_result.value()}};
    }

    [[nodiscard]] auto parse_header() -> rdp::parse_result<property_tree>
    {
        if (!rdp::check_whitespace(parser_))
            return rdp::parse_error{parser_, "Expected whitespace after <?xml."};

        object obj;

        while (!parser_.check(header_end))
        {
            const auto result = parse_attribute_and_value();

            if (!result)
                return result.error();

            obj.emplace(std::string{result.value().name}, std::string{result.value().value});
        }

        return rdp::matched{property_tree{std::move(obj)}};
    }

    [[nodiscard]] auto parse_element() -> rdp::parse_result<property_tree>
    {
        rdp::skip_whitespace_and_newline(parser_);

        const auto element_name = parser_.match(
            [](const auto c) { return std::isalnum(c) != 0 || c == '_' || c == '-' || c == '.' || c == ':'; });

        if (!element_name)
            return rdp::parse_error{parser_, "Expected element name."};

        rdp::skip_whitespace(parser_);

        object attributes;

        while (!rdp::eof(parser_))
        {
            rdp::skip_whitespace(parser_);

            if (parser_.check(element_self_closing_end))
            {
                if (std::empty(attributes))
                    return rdp::matched{property_tree{object{{std::string{element_name.value()}, array{{}}}}}};
                else
                    return rdp::matched{
                        property_tree{object{{std::string{element_name.value()},
                                              array{{object{{attribute_placeholder_, std::move(attributes)}}}}}}}};
            }

            if (parser_.check(element_end))
                break;

            const auto result = parse_attribute_and_value();

            if (!result)
                return rdp::parse_error{parser_, "Expected attribute or />."};

            attributes.emplace(std::string{result.value().name}, std::string{result.value().value});
        }

        auto children_result = parse_nodes(std::string{element_name.value()});

        if (children_result.is_error())
            return children_result.error();

        auto children = std::move(children_result.value());

        if (!std::empty(attributes))
            children.push_back(object{{attribute_placeholder_, std::move(attributes)}});

        return rdp::matched{property_tree{object{{std::string{element_name.value()}, std::move(children)}}}};
    }

    [[nodiscard]] auto parse_nodes(const std::string &parent_node) -> rdp::parse_result<array>
    {
        array nodes;

        const auto parent_closing_node = std::string{element_closing_begin} + parent_node + std::string{element_end};

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

    [[nodiscard]] auto parse_node() -> rdp::parse_result<property_tree>
    {
        if (parser_.check(cdata_begin))
        {
            return rdp::parse_error{parser_, "CDATA is not yet unsupported."};
        }
        else if (parser_.check(comment_begin))
        {
            if (!parser_.match_until(comment_end))
                return rdp::parse_error{parser_, "Unmatched comment section."};

            if (!parser_.check(comment_end))
                return rdp::parse_error{parser_, "Unmatched comment section."};
        }
        else if (parser_.check(header_begin))
        {
            return parse_header();
        }
        else if (parser_.check(dtd_begin))
        {
            return rdp::parse_error{parser_, "DTD is not yet unsupported."};
        }
        else if (parser_.check(element_begin))
        {
            return parse_element();
        }

        const auto text_result = parser_.match_until('<', rdp::eof_mode::match);

        if (!text_result)
            return rdp::parse_error{parser_, "Could not parse XML file."};

        const auto value = common::string::trimmedsv(text_result.value());

        if (std::empty(value))
            return rdp::unmatched{};

        return rdp::matched{property_tree{std::string{value}}};
    }

    rdp::parser parser_;
    std::string attribute_placeholder_;
};

} // namespace internal

void from_xml(streams::idynamic_stream &stream, property_tree &ptree, std::string attribute_placeholder)
{
    streams::stream_reader reader{stream};
    const auto str = reader.read_to_string();
    internal::xml_parser parser{str, std::move(attribute_placeholder)};
    parser.parse(ptree);
}

auto from_xml(streams::idynamic_stream &stream, std::string attribute_placeholder) -> property_tree
{
    property_tree pt;
    from_xml(stream, pt, std::move(attribute_placeholder));
    return pt;
}

auto from_xml(const std::string &str, std::string attribute_placeholder) -> property_tree
{
    auto stream = streams::make_string_view_stream(str);
    return from_xml(stream, std::move(attribute_placeholder));
}

} // namespace aeon::ptree::serialization

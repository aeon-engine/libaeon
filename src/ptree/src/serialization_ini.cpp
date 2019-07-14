// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/ptree/serialization/serialization_ini.h>
#include <aeon/streams/stream_writer.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/make_string_view_stream.h>
#include <aeon/rdp/parser.h>
#include <aeon/rdp/matchers.h>
#include <aeon/rdp/scoped_state.h>
#include <aeon/rdp/cursor.h>
#include <aeon/common/from_chars.h>

namespace aeon::ptree::serialization
{

namespace internal
{

static void to_string(const std::monostate, streams::idynamic_stream &);
static void to_string(const array &arr, streams::idynamic_stream &);
static void to_string(const object &obj, streams::idynamic_stream &);
static void to_string(const std::string &obj_str, streams::idynamic_stream &stream);
static void to_string(const common::uuid &uuid, streams::idynamic_stream &stream);
static void to_string(const std::int64_t val, streams::idynamic_stream &stream);
static void to_string(const double val, streams::idynamic_stream &stream);
static void to_string(const bool val, streams::idynamic_stream &stream);
static void to_string(const property_tree &ptree, streams::idynamic_stream &stream)
{
    std::visit([&stream](auto &&arg) { internal::to_string(arg, stream); }, ptree.value());
}

static void to_string(const std::monostate, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << "null";
}

static void to_string(const array &arr, streams::idynamic_stream &stream)
{
    throw ptree_unsupported_ini_format{};
}

static void to_string(const object &obj, streams::idynamic_stream &stream)
{
    throw ptree_unsupported_ini_format{};
}

static void to_string(const common::uuid &uuid, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << uuid.str();
}

static void to_string(const std::string &obj_str, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << '"';
    writer << obj_str;
    writer << '"';
}

static void to_string(const std::int64_t val, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << std::to_string(val);
}

static void to_string(const double val, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};
    writer << std::to_string(val);
}

static void to_string(const bool val, streams::idynamic_stream &stream)
{
    streams::stream_writer writer{stream};

    if (val)
        writer << "true";
    else
        writer << "false";
}

class ini_parser final
{
public:
    explicit ini_parser(const std::string_view &view)
        : parser_{view}
        , headers_{}
        , current_header_{}
    {
    }

    auto parse() -> property_tree
    {
        while (!rdp::eof(parser_))
        {
            rdp::skip_whitespace_and_newline(parser_);

            if (rdp::eof(parser_))
                break;

            if (const auto comment_result = check_comment(); comment_result.result())
                continue;

            if (const auto header_result = match_header(); header_result.is_error())
            {
                rdp::print_parse_error(header_result.error());
                throw ptree_serialization_exception{};
            }
            else if (header_result.result())
            {
                continue;
            }

            if (const auto key_value_result = match_key_value_pair(); key_value_result.is_error())
            {
                rdp::print_parse_error(key_value_result.error());
                throw ptree_serialization_exception{};
            }
            else if (key_value_result.result())
            {
                continue;
            }

            rdp::print_parse_error(parser_.cursor(), "Syntax error.");
            throw ptree_serialization_exception{};
        }

        return headers_;
    }

private:
    auto check_comment() -> rdp::parse_result<bool>
    {
        rdp::scoped_state state{parser_};

        rdp::skip_whitespace(parser_);

        if (!parser_.check(';'))
            return rdp::unmatched{};

        rdp::skip_until_newline(parser_);

        state.accept();
        return rdp::matched{};
    }

    auto match_key_name() -> rdp::parse_result<std::string_view>
    {
        return parser_.match_regex("[a-zA-Z_][a-zA-Z0-9\\-_]*");
    }

    auto match_string() -> rdp::parse_result<std::string_view>
    {
        rdp::scoped_state state{parser_};

        if (!parser_.check('"'))
            return rdp::unmatched{};

        const auto string_value = parser_.match_until('"');
        const auto quote_result = parser_.check('"');

        if (!string_value || !quote_result)
            return rdp::parse_error{parser_, "Expected: '\"'"};

        state.accept();
        return string_value;
    }

    auto match_value() -> rdp::parse_result<property_tree>
    {
        if (const auto double_result = rdp::parse_floating_point(parser_); double_result.result())
            return rdp::matched{property_tree{double_result.value()}};
        else if (double_result.is_error())
            return double_result.error();

        if (const auto digit_result = rdp::parse_decimal_signed(parser_); digit_result.result())
            return rdp::matched{property_tree{digit_result.value()}};
        else if (digit_result.is_error())
            return digit_result.error();

        if (const auto bool_result = rdp::parse_boolean(parser_); bool_result.result())
            return rdp::matched{property_tree{bool_result.value()}};
        else if (bool_result.is_error())
            return bool_result.error();

        if (const auto uuid_result = rdp::parse_uuid(parser_); uuid_result.result())
            return rdp::matched{property_tree{uuid_result.value()}};
        else if (uuid_result.is_error())
            return uuid_result.error();

        if (const auto string_result = match_string(); string_result.result())
            return rdp::matched{property_tree{std::string{string_result.value()}}};
        else if (string_result.is_error())
            return string_result.error();

        return rdp::parse_error{parser_, "Unknown value type."};
    }

    auto match_header() -> rdp::parse_result<bool>
    {
        rdp::scoped_state state{parser_};

        if (!parser_.check('['))
            return rdp::unmatched{};

        const auto header_name_result = match_key_name();

        if (!header_name_result)
            return rdp::parse_error{parser_, "Expected a valid header name after '['"};

        if (!parser_.check(']'))
            return rdp::parse_error{parser_, "Expected: ']'"};

        if (!check_comment() && !rdp::check_newline(parser_))
            return rdp::parse_error{parser_, "Expected newline."};

        auto result = headers_.insert(std::string{header_name_result.value()}, object{});
        current_header_ = &(result->second.object_value());

        state.accept();

        return rdp::matched{};
    }

    auto match_key_value_pair() -> rdp::parse_result<bool>
    {
        rdp::scoped_state state{parser_};

        const auto key_name_result = match_key_name();

        if (!key_name_result)
            return rdp::unmatched{};

        rdp::skip_whitespace(parser_);

        if (!parser_.check('='))
            return rdp::parse_error{parser_, "Expected: '='"};

        rdp::skip_whitespace(parser_);

        const auto value_result = match_value();

        if (!value_result)
            return value_result.error();

        rdp::skip_whitespace(parser_);

        if (!check_comment() && !rdp::check_newline(parser_))
            return rdp::parse_error{parser_, "Expected newline"};

        if (!current_header_)
            return rdp::parse_error{parser_, "Expected header"};

        current_header_->push_back(std::string{key_name_result.value()}, value_result.value());

        state.accept();
        return rdp::matched{};
    }

    rdp::parser parser_;

    object headers_;
    object *current_header_;
};

} // namespace internal

void to_ini(const property_tree &ptree, streams::idynamic_stream &stream)
{
    if (!ptree.is_object())
        throw ptree_unsupported_ini_format{};

    streams::stream_writer writer{stream};

    for (const auto &[segment_name, segment_values] : ptree.object_value())
    {
        if (!segment_values.is_object())
            throw ptree_unsupported_ini_format{};

        writer << '[';
        writer << segment_name;
        writer << ']';
        writer << '\n';

        for (const auto &[key, value] : segment_values.object_value())
        {
            if (value.is_array() || value.is_object())
                throw ptree_unsupported_ini_format{};

            writer << key;
            writer << " = ";
            internal::to_string(value, stream);
            writer << '\n';
        }
    }
}

auto to_ini(const property_tree &ptree) -> std::string
{
    std::string str;
    auto stream = streams::make_string_view_stream(str);
    to_ini(ptree, stream);
    return str;
}

void from_ini(streams::idynamic_stream &stream, property_tree &ptree)
{
    streams::stream_reader reader{stream};
    const auto str = reader.read_to_string();
    internal::ini_parser parser{str};
    ptree = parser.parse();
}

auto from_ini(streams::idynamic_stream &stream) -> property_tree
{
    property_tree pt;
    from_ini(stream, pt);
    return pt;
}

auto from_ini(const std::string &str) -> property_tree
{
    auto stream = streams::make_string_view_stream(str);
    return from_ini(stream);
}

} // namespace aeon::ptree::serialization

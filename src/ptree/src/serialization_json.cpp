// Copyright (c) 2012-2019 Robin Degen

#include <aeon/ptree/serialization/serialization_json.h>
#include <aeon/ptree/serialization/exception.h>
#include <aeon/unicode/utf_string_view.h>
#include <aeon/unicode/stringutils.h>
#include <aeon/common/type_traits.h>
#include <aeon/common/lexical_parse.h>
#include <variant>
#include <string>
#include <cctype>

namespace aeon::ptree::serialization
{

namespace internal
{

void to_json(const std::monostate, std::string &);
void to_json(const array &arr, std::string &str);
void to_json(const object &obj, std::string &str);
void to_json(const std::string &obj_str, std::string &str);
void to_json(const utility::uuid &uuid, std::string &str);
void to_json(const std::int64_t val, std::string &str);
void to_json(const double val, std::string &str);
void to_json(const bool val, std::string &str);

void to_json(const property_tree &ptree, std::string &str)
{
    std::visit([&str](auto &&arg) { internal::to_json(arg, str); }, ptree.value());
}

void to_json(const std::monostate, std::string &str)
{
    str += "null";
}

void to_json(const array &arr, std::string &str)
{
    str.push_back('[');

    for (const auto &pt : arr)
    {
        to_json(pt, str);
        str.push_back(',');
    }

    str.resize(std::size(str) - 1);
    str.push_back(']');
}

void to_json(const object &obj, std::string &str)
{
    str.push_back('{');

    for (const auto &[key, val] : obj)
    {
        to_json(key, str);
        str.push_back(':');
        to_json(val, str);
        str.push_back(',');
    }

    str.resize(std::size(str) - 1);
    str.push_back('}');
}

void to_json(const utility::uuid &uuid, std::string &str)
{
    to_json(uuid.str(), str);
}

void to_json(const std::string &obj_str, std::string &str)
{
    str.push_back('"');
    // TODO: Proper UTF-8 support
    str += unicode::stringutils::escape(obj_str);
    str.push_back('"');
}

void to_json(const std::int64_t val, std::string &str)
{
    str += std::to_string(val);
}

void to_json(const double val, std::string &str)
{
    str += std::to_string(val);
}

void to_json(const bool val, std::string &str)
{
    if (val)
        str += "true";
    else
        str += "false";
}

class json_parser final
{
public:
    explicit json_parser(const std::string_view &view)
        : view_{view}
        , itr_{std::begin(view_)}
        , prev_itr_{itr_}
    {
    }

    auto parse() -> property_tree
    {
        const auto token = next_token();

        if (std::isdigit(token) || token == '-')
        {
            itr_ = prev_itr_;
            return parse_number();
        }

        if (token == 't' || token == 'f')
            return parse_boolean(token);

        if (token == 'n')
            return parse_null();

        if (token == '"')
            return parse_string();

        if (token == '{')
            return parse_object();

        if (token == '[')
            return parse_array();

        throw ptree_serialization_exception{};
    }

private:
    void consume_whitespace() noexcept
    {
        while ((*itr_ == ' ' || *itr_ == '\r' || *itr_ == '\n' || *itr_ == '\t') && itr_ != std::end(view_))
            ++itr_;
    }

    auto parse_boolean(const char32_t token) -> property_tree
    {
        if (token == 't')
        {
            check("true");
            return true;
        }

        if (token == 'f')
        {
            check("false");
            return false;
        }

        throw ptree_serialization_exception{};
    }

    auto parse_null() -> property_tree
    {
        check("null");
        return nullptr;
    }

    auto parse_object() -> property_tree
    {
        object data;
        auto token = next_token();

        if (token == '}')
            return data;

        while (true)
        {
            if (token != '"')
                throw ptree_serialization_exception{};

            auto key = parse_string();

            token = next_token();

            if (token != ':')
                throw ptree_serialization_exception{};

            data.emplace(std::move(key), parse());

            token = next_token();
            if (token == '}')
                break;

            if (token != ',')
                throw ptree_serialization_exception{};

            token = next_token();
        }
        return data;
    }

    auto parse_array() -> property_tree
    {
        array data;
        auto token = next_token();

        if (token == ']')
            return data;

        while (true)
        {
            itr_ = prev_itr_;
            data.push_back(parse());

            token = next_token();

            if (token == ']')
                break;

            if (token != ',')
                throw ptree_serialization_exception{};

            next_token();
        }

        return data;
    }

    auto parse_number() -> property_tree
    {
        const auto str = common::lexical_parse::extract_number_string(view_.str().substr(itr_.offset()));
        const auto result = common::lexical_parse::number(str);

        std::advance(itr_, result.offset());

        if (result.is_integer())
            return result.integer_value();

        return result.double_value();
    }

    void check(const std::string_view &expected)
    {
        itr_ = prev_itr_;
        if (view_.str().compare(itr_.offset(), std::size(expected), expected) == 0)
        {
            std::advance(itr_, std::size(expected));
        }
        else
        {
            throw ptree_serialization_exception{};
        }
    }

    auto parse_string() -> std::string
    {
        std::string out;

        while (true)
        {
            if (itr_ == std::end(view_))
                throw ptree_serialization_exception{};

            if (*itr_ == '"')
            {
                ++itr_;
                return out;
            }

            if (std::iscntrl(*itr_))
                throw ptree_serialization_exception{};

            if (*itr_ != '\\')
            {
                out += itr_.character_str();
                ++itr_;
                continue;
            }

            ++itr_;

            if (itr_ == std::end(view_))
                throw ptree_serialization_exception{};

            const auto c = *itr_++;
            if (c == 'b')
            {
                out += '\b';
            }
            else if (c == 'f')
            {
                out += '\f';
            }
            else if (c == 'n')
            {
                out += '\n';
            }
            else if (c == 'r')
            {
                out += '\r';
            }
            else if (c == 't')
            {
                out += '\t';
            }
            else if (c == '"' || c == '\\' || c == '/')
            {
                out += static_cast<char>(c);
            }
            else
            {
                throw ptree_serialization_exception{};
            }
        }
    }

    auto next_token() -> char32_t
    {
        consume_whitespace();

        if (itr_ == std::end(view_))
            throw ptree_serialization_exception{};

        prev_itr_ = itr_;

        return *itr_++;
    }

    unicode::utf_string_view<std::string_view> view_;
    unicode::utf_string_view<std::string_view>::iterator itr_;
    unicode::utf_string_view<std::string_view>::iterator prev_itr_;
};

} // namespace internal

void to_json(const property_tree &ptree, std::string &str)
{
    internal::to_json(ptree, str);
}

auto to_json(const property_tree &ptree) -> std::string
{
    std::string str;
    to_json(ptree, str);
    return str;
}

void from_json(std::string_view str, property_tree &ptree)
{
    internal::json_parser parser{str};
    ptree = parser.parse();
}

auto from_json(std::string_view str) -> property_tree
{
    property_tree pt;
    from_json(str, pt);
    return pt;
}

} // namespace aeon::ptree::serialization

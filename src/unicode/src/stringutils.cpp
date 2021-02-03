// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/unicode/stringutils.h>

namespace aeon::unicode::stringutils
{

[[nodiscard]] auto escape(const std::u8string_view &str) -> std::u8string
{
    utf_string_view view{str};
    return escape(std::begin(view), std::end(view));
}

[[nodiscard]] auto escape(const utf_string_view<std::u8string_view>::iterator begin,
                          const utf_string_view<std::u8string_view>::iterator end) -> std::u8string
{
    std::u8string result;
    result.reserve(std::distance(begin, end));

    for (auto itr = begin; itr != end; ++itr)
    {
        switch (*itr)
        {
            case '\b':
                result += u8"\\b";
                break;
            case '\f':
                result += u8"\\f";
                break;
            case '\n':
                result += u8"\\n";
                break;
            case '\r':
                result += u8"\\r";
                break;
            case '\t':
                result += u8"\\t";
                break;
            case '\\':
                result += u8"\\\\";
                break;
            case '"':
                result += u8"\\\"";
                break;
            case '/':
                result += u8"\\/";
                break;
            default:
                result += itr.character_str();
        }
    }

    return result;
}

[[nodiscard]] auto unescape(const std::u8string_view &str, const unescape_mode mode) -> std::u8string
{
    utf_string_view view{str};
    return unescape(std::begin(view), std::end(view), mode);
}

[[nodiscard]] auto unescape(const utf_string_view<std::u8string_view>::iterator begin,
                            const utf_string_view<std::u8string_view>::iterator end, const unescape_mode mode)
    -> std::u8string
{
    std::u8string result;
    result.reserve(std::distance(begin, end));

    for (auto itr = begin; itr != end; ++itr)
    {
        if (*itr == '\\')
        {
            ++itr;

            if (itr == end)
                throw unescape_exception{};

            switch (*itr)
            {
                case 'b':
                    result += '\b';
                    break;
                case 'f':
                    result += '\f';
                    break;
                case 'n':
                    result += '\n';
                    break;
                case 'r':
                    result += '\r';
                    break;
                case 't':
                    result += '\t';
                    break;
                case '\\':
                case '"':
                case '/':
                    result += static_cast<char>(*itr);
                    break;
                default:
                {
                    if (mode == unescape_mode::error_on_unknown)
                        throw unescape_exception{};

                    result += itr.character_str();
                }
                break;
            }
        }
        else
        {
            result += itr.character_str();
        }
    }

    return result;
}

} // namespace aeon::unicode::stringutils

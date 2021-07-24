// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/url_encoding.h>
#include <aeon/common/string.h>
#include <aeon/common/literals.h>

namespace aeon::web::http
{

auto url_encode(const std::u8string &str) -> std::u8string
{
    std::u8string out;
    out.reserve(std::size(str));

    for (const auto t : str)
    {
        if (t == '-' || t == '.' || (t >= '0' && t <= '9') || (t >= 'A' && t <= 'Z') || t == '_' ||
            (t >= 'a' && t <= 'z') || t == '~' || t == '/')
        {
            out += t;
        }
        else
        {
            const auto hex_str = common::string::char_to_hex(t);

            // TODO: Fix when char_to_hex supports utf8.
            out += std::u8string_view{reinterpret_cast<const char8_t *>(std::data(hex_str)), std::size(hex_str)};
        }
    }

    return out;
}

auto url_decode(const std::u8string &str) -> std::u8string
{
    std::u8string out;
    out.reserve(std::size(str));

    for (auto i = 0_size_t; i < str.length(); ++i)
    {
        if (str.at(i) == '%')
        {
            // TODO: Fix when hex_to_char supports utf8.
            const auto u8_str = str.substr(i + 1, 2);
            out += common::string::hex_to_char(std::string{std::begin(u8_str), std::end(u8_str)});
            i += 2;
        }
        else
        {
            out += str.at(i);
        }
    }

    return out;
}

} // namespace aeon::web::http

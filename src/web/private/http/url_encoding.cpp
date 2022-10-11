// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/web/http/url_encoding.h>
#include <aeon/common/string_utils.h>
#include <aeon/common/literals.h>

namespace aeon::web::http
{

auto url_encode(const common::string &str) -> common::string
{
    common::string out;
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
            out += common::string_utils::char_to_hex(t);
        }
    }

    return out;
}

auto url_decode(const common::string &str) -> common::string
{
    common::string out;
    out.reserve(std::size(str));

    for (auto i = 0_size_t; i < std::size(str); ++i)
    {
        if (str.at(i) == '%')
        {
            out += common::string_utils::hex_to_char(str.substr(i + 1, 2));
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

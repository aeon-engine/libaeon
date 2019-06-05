// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/sockets/http/url_encoding.h>
#include <aeon/common/string.h>
#include <aeon/common/literals.h>

namespace aeon::sockets::http
{

auto url_encode(const std::string &str) -> std::string
{
    std::ostringstream out;

    for (const auto t : str)
    {
        if (t == '-' || t == '.' || (t >= '0' && t <= '9') || (t >= 'A' && t <= 'Z') || t == '_' ||
            (t >= 'a' && t <= 'z') || t == '~' || t == '/')
        {
            out << t;
        }
        else
        {
            out << common::string::char_to_hex(t);
        }
    }

    return out.str();
}

auto url_decode(const std::string &str) -> std::string
{
    std::ostringstream out;

    for (auto i = 0_size_t; i < str.length(); ++i)
    {
        if (str.at(i) == '%')
        {
            out << common::string::hex_to_char(str.substr(i + 1, 2));
            i += 2;
        }
        else
        {
            out << str.at(i);
        }
    }

    return out.str();
}

} // namespace aeon::sockets::http

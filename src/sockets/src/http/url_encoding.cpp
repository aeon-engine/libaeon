/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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

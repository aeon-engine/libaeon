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

#pragma once

#include <aeon/common/utf8_string_view.h>

namespace aeon::common::utf8
{

inline auto to_utf8_string(const char32_t *str) -> std::string
{
    std::string utf8str;

    while (str != nullptr && *str != '\0')
    {
        utf8_append(utf8str, *str);
        ++str;
    }

    return utf8str;
}

inline auto to_wstring(const std::string_view &str) -> std::wstring
{
    std::wstring result;
    result.reserve(str.size());

    utf8_string_view view{str};

    for (auto c : view)
    {
        if (c <= 0xFFFF)
        {
            result.push_back(static_cast<wchar_t>(c));
        }
        else
        {
            c -= 0x10000;
            result.push_back(static_cast<wchar_t>((c >> 10) + 0xD800));
            result.push_back(static_cast<wchar_t>((c & 0x3FF) + 0xDC00));
        }
    }

    return result;
}

} // namespace aeon::common::utf8

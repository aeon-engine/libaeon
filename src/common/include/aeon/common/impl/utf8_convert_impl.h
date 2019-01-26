// Copyright (c) 2012-2019 Robin Degen

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

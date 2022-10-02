// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <ostream>
#include <string>

/*!
 * Write an u8string to an ostream. This assumes that the output stream (for example the terminal, in case of std::out)
 * supports UTF-8. No conversion is done.
 */
inline auto operator<<(std::ostream &os, const std::u8string_view &s) -> std::ostream &
{
    // This is not perfectly portable, but works fine on all major platforms
    return os << std::string_view{reinterpret_cast<const char *>(std::data(s)), std::size(s)};
}

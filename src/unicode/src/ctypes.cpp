// Copyright (c) 2012-2019 Robin Degen

#include <aeon/unicode/ctypes.h>
#include <unicode/utypes.h>
#include <unicode/utext.h>

namespace aeon::unicode::ctypes
{

auto is_digit(const char32_t c) noexcept -> bool
{
    return u_isdigit(c);
}

auto is_digit_ascii(const char32_t c) noexcept -> bool
{
    return (c <= 0x7f && is_digit(c));
}

auto is_xdigit(const char32_t c) noexcept -> bool
{
    return u_isxdigit(c);
}

auto is_xdigit_ascii(const char32_t c) noexcept -> bool
{
    return (c <= 0x7f && is_xdigit(c));
}

auto is_graph(const char32_t c) noexcept -> bool
{
    return u_isgraph(c);
}

} // namespace aeon::unicode::ctypes

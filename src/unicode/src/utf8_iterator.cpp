// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/unicode/utf8_iterator.h>
#include <unicode/utf8.h>

namespace aeon::unicode
{

void utf8_iterator::advance() noexcept
{
    offset_ = next_offset_;
    ++cp_pos_;

    if (next_offset_ < len_)
    {
        auto chr = 0;
        U8_NEXT(str_, next_offset_, len_, chr);
        char_ = static_cast<char32_t>(chr);
    }
}

} // namespace aeon::unicode

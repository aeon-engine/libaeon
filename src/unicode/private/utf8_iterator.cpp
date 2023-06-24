// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/unicode/utf8_iterator.h>

namespace aeon::unicode
{

[[nodiscard]] inline auto u8_next(const char8_t *str, int32_t &offset, int32_t length, char32_t &codepoint)
{
    // Reached the end of the string
    if (offset >= length)
        return false;

    const auto lead = str[offset++];

    // Single-byte code point (ASCII range)
    if ((lead & 0x80) == 0)
    {
        codepoint = lead;
        return true;
    }

    int32_t extraBytes = 0;
    if ((lead & 0xE0) == 0xC0)
    {
        codepoint = lead & 0x1F;
        extraBytes = 1;
    }
    else if ((lead & 0xF0) == 0xE0)
    {
        codepoint = lead & 0x0F;
        extraBytes = 2;
    }
    else if ((lead & 0xF8) == 0xF0)
    {
        codepoint = lead & 0x07;
        extraBytes = 3;
    }
    else
    {
        // Invalid lead byte
        return false;
    }

    // Incomplete multibyte sequence
    if (offset + extraBytes > length)
        return false;

    for (auto i = 0; i < extraBytes; ++i)
    {
        const auto trail = str[offset++];

        // Invalid trail byte
        if ((trail & 0xC0) != 0x80)
            return false;

        codepoint = (codepoint << 6) | (trail & 0x3F);
    }

    return true;
}

void utf8_iterator::advance() noexcept
{
    offset_ = next_offset_;
    ++cp_pos_;

    if (next_offset_ < len_)
    {
        [[maybe_unused]] const auto result = u8_next(str_, next_offset_, len_, char_);
        aeon_assert(result, "Invalid UTF-16 string.");
    }
}

} // namespace aeon::unicode

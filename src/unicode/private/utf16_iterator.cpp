// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/unicode/utf16_iterator.h>
#include <aeon/common/assert.h>

namespace aeon::unicode
{

[[nodiscard]] static auto u16_next(const char16_t *str, int32_t &offset, const int32_t length, char32_t &codepoint)
{
    // Reached the end of the string
    if (offset >= length)
        return false;

    const auto lead = str[offset++];

    // Single code unit (not a surrogate pair)
    if (lead < 0xD800 || lead > 0xDBFF)
    {
        codepoint = lead;
        return true;
    }

    // Invalid surrogate pair (trailing code unit missing or invalid)
    if (offset >= length || str[offset] < 0xDC00 || str[offset] > 0xDFFF)
        return false;

    // Valid surrogate pair
    codepoint = ((lead - 0xD800) << 10) + (str[offset] - 0xDC00) + 0x10000;
    ++offset;
    return true;
}

void utf16_iterator::advance() noexcept
{
    offset_ = next_offset_;
    ++cp_pos_;

    if (next_offset_ < len_)
    {
        [[maybe_unused]] const auto result = u16_next(str_, next_offset_, len_, char_);
        aeon_assert(result, "Invalid UTF-16 string.");
    }
}

} // namespace aeon::unicode

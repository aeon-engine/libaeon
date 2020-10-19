// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/unicode/base_utf_iterator.h>
#include <aeon/common/bom.h>
#include <aeon/common/assert.h>

namespace aeon::unicode
{

class utf16_iterator final : public base_utf_iterator<std::u16string_view, char16_t>
{
public:
    using value_type = const char32_t;
    using pointer = const char32_t *;
    using reference = const char32_t &;
    using difference_type = std::int32_t;
    using iterator_category = std::forward_iterator_tag;

    explicit utf16_iterator(const std::u16string_view &str) noexcept
        : base_utf_iterator<std::u16string_view, char16_t>{str}
    {
        consume_bom();
        advance();
    }

    explicit utf16_iterator(const std::u16string_view &str, const std::int32_t offset) noexcept
        : base_utf_iterator<std::u16string_view, char16_t>{str, offset}
    {
    }

    ~utf16_iterator() = default;

    utf16_iterator(const utf16_iterator &) = default;
    auto operator=(const utf16_iterator &) -> utf16_iterator & = default;

    utf16_iterator(utf16_iterator &&) noexcept = default;
    auto operator=(utf16_iterator &&) noexcept -> utf16_iterator & = default;

    auto operator++() noexcept -> utf16_iterator &
    {
        aeon_assert(offset_ < len_, "Iterator out of range.");
        advance();
        return *this;
    }

    auto operator++(int) noexcept -> utf16_iterator
    {
        const auto temp(*this);
        ++*this;
        return temp;
    }

    auto operator==(const utf16_iterator &other) const noexcept
    {
        aeon_assert(str_ == other.str_ && len_ == other.len_, "utf8_string_iterator range mismatch.");
        return offset_ == other.offset_;
    }

    auto operator!=(const utf16_iterator &other) const noexcept
    {
        return !(*this == other);
    }

private:
    void consume_bom() noexcept
    {
        if (len_ == 0)
            return;

        if (str_[0] == common::bom::utf16::signature || str_[0] == common::bom::utf16::big_endian_signature)
            ++next_offset_;
    }

    void advance() noexcept;
};

} // namespace aeon::unicode

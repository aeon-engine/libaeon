// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/unicode/base_utf_iterator.h>
#include <aeon/common/assert.h>

namespace aeon::unicode
{

class utf16_iterator final : public base_utf_iterator<std::wstring_view, char16_t>
{
public:
    using value_type = const char32_t;
    using pointer = const char32_t *;
    using reference = const char32_t &;
    using difference_type = std::int32_t;
    using iterator_category = std::forward_iterator_tag;

    explicit utf16_iterator(const std::wstring_view &str) noexcept
        : base_utf_iterator<std::wstring_view, char16_t>{str}
    {
        advance();
    }

    explicit utf16_iterator(const std::wstring_view &str, const std::int32_t offset) noexcept
        : base_utf_iterator<std::wstring_view, char16_t>{str, offset}
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
        aeon_assert(begin_ == other.begin_ && len_ == other.len_, "utf8_string_iterator range mismatch.");
        return offset_ == other.offset_;
    }

    auto operator!=(const utf16_iterator &other) const noexcept
    {
        return !(*this == other);
    }

private:
    void advance() noexcept;
};

} // namespace aeon::unicode

// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/unicode/base_utf_iterator.h>
#include <aeon/common/bom.h>
#include <aeon/common/assert.h>

namespace aeon::unicode
{

class utf8_iterator final : public base_utf_iterator<common::string_view, char8_t>
{
public:
    using value_type = const char32_t;
    using pointer = const char32_t *;
    using reference = const char32_t &;
    using difference_type = std::int32_t;
    using iterator_category = std::forward_iterator_tag;

    explicit utf8_iterator(const common::string_view &str) noexcept
        : base_utf_iterator<common::string_view, char8_t>{str}
    {
        consume_bom();
        advance();
    }

    explicit utf8_iterator(const common::string_view &str, const std::int32_t offset) noexcept
        : base_utf_iterator<common::string_view, char8_t>{str, offset}
    {
    }

    ~utf8_iterator() = default;

    utf8_iterator(const utf8_iterator &) = default;
    auto operator=(const utf8_iterator &) -> utf8_iterator & = default;

    utf8_iterator(utf8_iterator &&) noexcept = default;
    auto operator=(utf8_iterator &&) noexcept -> utf8_iterator & = default;

    auto operator++() noexcept -> utf8_iterator &
    {
        aeon_assert(offset_ < len_, "Iterator out of range.");
        advance();
        return *this;
    }

    auto operator++(int) noexcept -> utf8_iterator
    {
        const auto temp(*this);
        ++*this;
        return temp;
    }

    auto operator==(const utf8_iterator &other) const noexcept
    {
        aeon_assert(str_ == other.str_ && len_ == other.len_, "utf8_string_iterator range mismatch.");
        return offset_ == other.offset_;
    }

    auto operator!=(const utf8_iterator &other) const noexcept
    {
        return !(*this == other);
    }

private:
    void consume_bom() noexcept
    {
        if (len_ < 3)
            return;

        if (str_[0] == common::bom::utf8::signature[0] && str_[1] == common::bom::utf8::signature[1] &&
            str_[2] == common::bom::utf8::signature[2])
            next_offset_ += 3;
    }

    void advance() noexcept;
};

} // namespace aeon::unicode

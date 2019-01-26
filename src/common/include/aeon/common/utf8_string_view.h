// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/utf8_utils.h>
#include <string_view>

namespace aeon::common::utf8
{

class utf8_string_iterator final
{
public:
    using value_type = const char32_t;
    using pointer = const char32_t *;
    using reference = const char32_t &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit utf8_string_iterator(const char *begin, const char *end);
    explicit utf8_string_iterator(const char *begin, const char *end, const char *offset);

    ~utf8_string_iterator() = default;

    utf8_string_iterator(const utf8_string_iterator &) noexcept = default;
    auto operator=(const utf8_string_iterator &) noexcept -> utf8_string_iterator & = default;

    utf8_string_iterator(utf8_string_iterator &&) noexcept = default;
    auto operator=(utf8_string_iterator &&) noexcept -> utf8_string_iterator & = default;

    auto operator*() noexcept -> reference;
    auto operator-> () noexcept -> pointer;

    auto operator++() -> utf8_string_iterator &;
    auto operator++(int) -> utf8_string_iterator;

    auto operator==(const utf8_string_iterator &other) const noexcept -> bool;
    auto operator!=(const utf8_string_iterator &other) const noexcept -> bool;

private:
    void consume_bom();

    const char *begin_;
    const char *end_;
    const char *offset_;
    char32_t current_;
};

class utf8_string_view final
{
public:
    explicit utf8_string_view(const std::string_view view) noexcept;

    ~utf8_string_view() = default;

    utf8_string_view(const utf8_string_view &) noexcept = default;
    auto operator=(const utf8_string_view &) noexcept -> utf8_string_view & = default;

    utf8_string_view(utf8_string_view &&) noexcept = default;
    auto operator=(utf8_string_view &&) noexcept -> utf8_string_view & = default;

    auto begin() const noexcept;

    auto end() const noexcept;

private:
    std::string_view view_;
};

} // namespace aeon::common::utf8

#include <aeon/common/impl/utf8_string_view_impl.h>

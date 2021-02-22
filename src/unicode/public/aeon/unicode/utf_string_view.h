// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/unicode/utf8_iterator.h>
#include <aeon/unicode/utf16_iterator.h>
#include <aeon/unicode/concepts.h>
#include <string_view>

struct UText;

namespace aeon::unicode
{

namespace internal
{

template <typename T>
struct utf_iterator_traits;

template <>
struct utf_iterator_traits<std::u8string_view>
{
    using iterator_type = utf8_iterator;
};

template <>
struct utf_iterator_traits<std::u16string_view>
{
    using iterator_type = utf16_iterator;
};

} // namespace internal

template <concepts::utf_string_view T>
class utf_string_view final
{
public:
    using iterator = typename internal::utf_iterator_traits<T>::iterator_type;

    explicit utf_string_view(const T str) noexcept
        : str_{str}
    {
    }

    ~utf_string_view() = default;

    utf_string_view(const utf_string_view &) noexcept = default;
    auto operator=(const utf_string_view &) noexcept -> utf_string_view & = default;

    utf_string_view(utf_string_view &&) noexcept = default;
    auto operator=(utf_string_view &&) noexcept -> utf_string_view & = default;

    [[nodiscard]] auto begin() const noexcept
    {
        return iterator{str_};
    }

    [[nodiscard]] auto end() const noexcept
    {
        return iterator{str_, static_cast<std::int32_t>(std::size(str_))};
    }

    [[nodiscard]] auto str() const noexcept
    {
        return str_;
    }

private:
    T str_;
};

template <>
class utf_string_view<std::u32string_view> final
{
public:
    using iterator = std::u32string_view::iterator;

    explicit utf_string_view(const std::u32string_view str) noexcept
        : str_{str}
    {
    }

    ~utf_string_view() = default;

    utf_string_view(const utf_string_view &) noexcept = default;
    auto operator=(const utf_string_view &) noexcept -> utf_string_view & = default;

    utf_string_view(utf_string_view &&) noexcept = default;
    auto operator=(utf_string_view &&) noexcept -> utf_string_view & = default;

    [[nodiscard]] auto begin() const noexcept
    {
        return std::begin(str_);
    }

    [[nodiscard]] auto end() const noexcept
    {
        return std::end(str_);
    }

    [[nodiscard]] auto str() const noexcept
    {
        return str_;
    }

private:
    std::u32string_view str_;
};

utf_string_view(char8_t *const)->utf_string_view<std::u8string_view>;
utf_string_view(const char8_t *const)->utf_string_view<std::u8string_view>;
utf_string_view(const std::u8string &)->utf_string_view<std::u8string_view>;

utf_string_view(char16_t *const)->utf_string_view<std::u16string_view>;
utf_string_view(const char16_t *const)->utf_string_view<std::u16string_view>;
utf_string_view(const std::u16string &)->utf_string_view<std::u16string_view>;

utf_string_view(char32_t *const)->utf_string_view<std::u32string_view>;
utf_string_view(const char32_t *const)->utf_string_view<std::u32string_view>;
utf_string_view(const std::u32string &)->utf_string_view<std::u32string_view>;

} // namespace aeon::unicode

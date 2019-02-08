// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/unicode/utf8_iterator.h>
#include <aeon/unicode/utf16_iterator.h>
#include <string_view>

struct UText;

namespace aeon::unicode
{

namespace internal
{

template <typename T>
struct utf_iterator_traits
{
};

template <>
struct utf_iterator_traits<std::string_view>
{
    using iterator_type = utf8_iterator;
};

template <>
struct utf_iterator_traits<std::wstring_view>
{
    using iterator_type = utf16_iterator;
};

} // namespace internal

template <typename T>
class utf_string_view final
{
public:
    using iterator = typename internal::utf_iterator_traits<T>::iterator_type;

    explicit utf_string_view(const T str) noexcept
        : str_{str}
    {
        static_assert(std::disjunction_v<std::is_same<T, std::string_view>, std::is_same<T, std::wstring_view>>,
                      "T must be std::string_view or std::wstring_view.");
    }

    ~utf_string_view() = default;

    utf_string_view(const utf_string_view &) noexcept = default;
    auto operator=(const utf_string_view &) noexcept -> utf_string_view & = default;

    utf_string_view(utf_string_view &&) noexcept = default;
    auto operator=(utf_string_view &&) noexcept -> utf_string_view & = default;

    auto begin() const noexcept
    {
        return iterator{str_};
    }

    auto end() const noexcept
    {
        return iterator{str_, static_cast<std::int32_t>(std::size(str_))};
    }

    auto str() const noexcept
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

    auto begin() const noexcept
    {
        return std::begin(str_);
    }

    auto end() const noexcept
    {
        return std::end(str_);
    }

    auto str() const noexcept
    {
        return str_;
    }

private:
    std::u32string_view str_;
};

utf_string_view(char *const)->utf_string_view<std::string_view>;
utf_string_view(const char *const)->utf_string_view<std::string_view>;
utf_string_view(const std::string &)->utf_string_view<std::string_view>;

utf_string_view(wchar_t *const)->utf_string_view<std::wstring_view>;
utf_string_view(const wchar_t *const)->utf_string_view<std::wstring_view>;
utf_string_view(const std::wstring &)->utf_string_view<std::wstring_view>;

utf_string_view(char32_t *const)->utf_string_view<std::u32string_view>;
utf_string_view(const char32_t *const)->utf_string_view<std::u32string_view>;
utf_string_view(const std::u32string &)->utf_string_view<std::u32string_view>;

} // namespace aeon::unicode

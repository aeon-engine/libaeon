// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <algorithm>
#include <array>

namespace aeon::common
{

template <typename char_type_t, std::size_t N>
class basic_string_literal
{
public:
    using storage_type = char[N];

    using value_type = char_type_t;
    using reference = const char_type_t &;
    using const_reference = const char_type_t &;
    using size_type = std::size_t;

    using iterator = const char_type_t *;
    using const_iterator = const char_type_t *;

    constexpr basic_string_literal() noexcept
    {
        static_assert(N == 0, "String literal of size > 0 can not be empty.");
    }

    constexpr basic_string_literal(const char_type_t (&str)[N])
    {
        std::copy_n(str, N, value);
    }

    constexpr operator const storage_type &() const
    {
        return value;
    }

    constexpr auto size() const -> size_type
    {
        return N;
    }

    constexpr const char_type_t *data() const noexcept
    {
        return value;
    }

    constexpr const char_type_t *c_str() const noexcept
    {
        return value;
    }

    constexpr iterator begin() const noexcept
    {
        return value;
    }

    constexpr iterator end() const noexcept
    {
        return value + N;
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return value;
    }

    constexpr const_iterator cend() const noexcept
    {
        return value + N;
    }

    char_type_t value[N];
};

template <typename char_type_t, std::size_t N>
basic_string_literal(const char_type_t (&)[N]) -> basic_string_literal<char_type_t, N>;

template <std::size_t N>
using string_literal = basic_string_literal<char, N>;

template <std::size_t N>
using wstring_literal = basic_string_literal<wchar_t, N>;

template <std::size_t N>
using u8string_literal = basic_string_literal<char8_t, N>;

template <std::size_t N>
using u16string_literal = basic_string_literal<char16_t, N>;

template <std::size_t N>
using u32string_literal = basic_string_literal<char32_t, N>;

} // namespace aeon::common

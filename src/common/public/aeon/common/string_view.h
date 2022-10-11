// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <string_view>
#include <ostream>

namespace aeon::common
{

class string;

class string_view
{
    friend class string;

public:
    static_assert(alignof(char) == alignof(char8_t),
                  "Alignment of char and char8_t don't match. string_view won't work properly.");
    static_assert(sizeof(char) == sizeof(char8_t),
                  "Size of char and char8_t don't match. string_view won't work properly.");

    static constexpr auto npos = std::string_view::npos;

    using value_type = std::string_view::value_type;

    using size_type = std::string_view::size_type;
    using difference_type = std::string_view::difference_type;
    using pointer = std::string_view::pointer;
    using const_pointer = std::string_view::const_pointer;
    using reference = std::string_view::reference;
    using const_reference = std::string_view::const_reference;

    using iterator = std::string_view::iterator;
    using const_iterator = std::string_view::const_iterator;

    using reverse_iterator = std::string_view::reverse_iterator;
    using const_reverse_iterator = std::string_view::const_reverse_iterator;

    constexpr string_view() noexcept;

    constexpr string_view(const char *const str);

    string_view(const char8_t *const str);

    constexpr string_view(const char *const str, const size_type size);

    string_view(const char8_t *const str, const size_type size);

    constexpr string_view(const std::string &str) noexcept;

    string_view(const std::u8string &str);

    constexpr string_view(const std::string_view &str) noexcept;

    string_view(const std::u8string_view &str);

    constexpr string_view(const string &str) noexcept;

    constexpr string_view(const string_view &other) = default;
    constexpr auto operator=(const string_view &other) -> string_view & = default;

    constexpr string_view(string_view &&other) noexcept = default;
    constexpr auto operator=(string_view &&other) noexcept -> string_view & = default;

    constexpr ~string_view() = default;

    constexpr auto operator=(const value_type *const str) -> string_view &;
    constexpr auto operator=(const std::string &str) -> string_view &;

    auto operator=(const char8_t *const str) -> string_view &;

    auto operator=(const std::u8string &str) -> string_view &;

    constexpr void assign(const value_type *const str);

    constexpr void assign(const std::string &str);

    void assign(const char8_t *const str);

    void assign(const std::u8string &str);

    constexpr void assign(const string &str);

    [[nodiscard]] constexpr auto size() const noexcept -> size_type;

    [[nodiscard]] constexpr auto data() const noexcept -> const_pointer;

    [[nodiscard]] constexpr auto compare(const string &str) const noexcept -> int;

    [[nodiscard]] constexpr auto compare(const std::string &str) const noexcept -> int;

    [[nodiscard]] auto compare(const std::u8string &str) const noexcept -> int;

    [[nodiscard]] constexpr auto compare(const value_type *const str) const noexcept -> int;

    [[nodiscard]] auto compare(const char8_t *const str) const noexcept -> int;

    [[nodiscard]] constexpr auto compare(const size_type pos, const size_type count, const string_view str) const
        -> int;

    constexpr auto operator==(const string &str) const -> bool;

    constexpr auto operator==(const string_view &str) const -> bool;

    constexpr auto operator==(const std::string &str) const -> bool;

    auto operator==(const std::u8string &str) const -> bool;

    constexpr auto operator==(const value_type *const str) const -> bool;

    auto operator==(const char8_t *const str) const -> bool;

    constexpr auto operator<=>(const string &str) const -> std::strong_ordering;

    constexpr auto operator<=>(const string_view &str) const -> std::strong_ordering;

    constexpr auto operator<=>(const std::string &str) const -> std::strong_ordering;

    auto operator<=>(const std::u8string &str) const -> std::strong_ordering;

    constexpr auto operator<=>(const value_type *const str) const -> std::strong_ordering;

    auto operator<=>(const char8_t *const str) const -> std::strong_ordering;

    [[nodiscard]] constexpr auto as_std_string_view() noexcept -> std::string_view;

    [[nodiscard]] constexpr auto as_std_string_view() const noexcept -> std::string_view;

    [[nodiscard]] auto as_std_u8string_view() noexcept -> std::u8string_view;

    [[nodiscard]] auto as_std_u8string_view() const noexcept -> std::u8string_view;

    [[nodiscard]] constexpr auto empty() const noexcept -> bool;

    [[nodiscard]] constexpr auto at(const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto operator[](const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto front() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto back() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto end() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto rbegin() noexcept -> reverse_iterator;

    [[nodiscard]] constexpr auto rbegin() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto crbegin() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto rend() noexcept -> reverse_iterator;

    [[nodiscard]] constexpr auto rend() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto crend() const noexcept -> const_reverse_iterator;

    [[nodiscard]] constexpr auto starts_with(const std::string_view &str) const noexcept -> bool;

    [[nodiscard]] auto starts_with(const std::u8string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto starts_with(const string &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto starts_with(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto starts_with(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const std::string_view &str) const noexcept -> bool;

    [[nodiscard]] auto ends_with(const std::u8string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const string &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto substr(const size_type pos = 0, const size_type count = npos) const -> string_view;

    [[nodiscard]] auto find(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto find(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto rfind(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto rfind(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto rfind(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto rfind(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto rfind(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto rfind(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto rfind(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_first_of(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto find_first_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_first_of(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find_first_of(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_first_of(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_first_of(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_first_of(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_first_not_of(const std::string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] auto find_first_not_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const string &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_first_not_of(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_last_of(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto find_last_of(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find_last_of(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find_last_of(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_last_of(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_last_of(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_last_of(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_last_not_of(const std::string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] auto find_last_not_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const string &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_last_not_of(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const char8_t c, const size_type pos = 0) const -> size_type;

    constexpr void remove_prefix(const size_type n);

    constexpr void remove_suffix(const size_type n);

private:
    std::string_view str_;
};

inline auto operator<<(std::ostream &os, const string_view &str) -> std::ostream &;

} // namespace aeon::common

#include <aeon/common/impl/string_view_impl.h>

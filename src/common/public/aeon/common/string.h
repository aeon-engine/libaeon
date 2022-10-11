// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <string>
#include <ostream>

namespace aeon::common
{

class string_view;

class string
{
    friend class string_view;

public:
    static_assert(alignof(char) == alignof(char8_t),
                  "Alignment of char and char8_t don't match. String won't work properly.");
    static_assert(sizeof(char) == sizeof(char8_t), "Size of char and char8_t don't match. String won't work properly.");

    static constexpr auto npos = std::string::npos;

    using value_type = std::string::value_type;
    using allocator_type = std::string::allocator_type;

    using size_type = std::string::size_type;
    using difference_type = std::string::difference_type;
    using pointer = std::string::pointer;
    using const_pointer = std::string::const_pointer;
    using reference = std::string::reference;
    using const_reference = std::string::const_reference;

    using iterator = std::string::iterator;
    using const_iterator = std::string::const_iterator;

    using reverse_iterator = std::string::reverse_iterator;
    using const_reverse_iterator = std::string::const_reverse_iterator;

    constexpr string() noexcept;

    constexpr string(const size_type count, const value_type c) noexcept;

    constexpr string(const size_type count, const char8_t c) noexcept;

    constexpr string(const char *const str);

    string(const char8_t *const str);

    constexpr string(std::string str) noexcept;

    constexpr string(const std::u8string &str);

    constexpr explicit string(const string_view &str) noexcept;

    template <typename iterator_t>
    constexpr string(iterator_t begin, iterator_t end) noexcept;

    constexpr string(const string &other) = default;
    constexpr auto operator=(const string &other) -> string & = default;

    constexpr string(string &&other) noexcept = default;
    constexpr auto operator=(string &&other) noexcept -> string & = default;

    constexpr ~string() = default;

    constexpr auto operator=(const value_type *const str) -> string &;

    constexpr auto operator=(std::string str) -> string &;

    auto operator=(const char8_t *const str) -> string &;

    constexpr auto operator=(const std::u8string &str) -> string &;

    constexpr auto operator=(const string_view &str) -> string &;

    constexpr void assign(const value_type *const str);

    constexpr void assign(std::string &&str);

    void assign(const char8_t *const str);

    constexpr void assign(const std::u8string &str);

    constexpr void assign(const string &str);

    constexpr void assign(const string_view &str);

    constexpr auto insert(const size_type index, const value_type *const str) -> string &;

    auto insert(const size_type index, const char8_t *const str) -> string &;

    constexpr auto insert(const size_type index, const std::string_view &str) -> string &;

    auto insert(const size_type index, const std::u8string_view &str) -> string &;

    auto insert(const size_type index, const string &str) -> string &;

    auto insert(const size_type index, const string_view &str) -> string &;

    constexpr auto erase(const size_type index = 0, const size_type count = npos) -> string &;

    constexpr auto erase(const_iterator position) -> iterator;

    constexpr auto erase(const_iterator first, const_iterator last) -> iterator;

    [[nodiscard]] constexpr auto str() noexcept -> std::string &;

    [[nodiscard]] constexpr auto str() const noexcept -> const std::string &;

    [[nodiscard]] auto u8str() const noexcept -> std::u8string;

    [[nodiscard]] constexpr auto size() const noexcept -> size_type;

    [[nodiscard]] constexpr auto capacity() const noexcept -> size_type;

    [[nodiscard]] constexpr auto data() noexcept -> pointer;

    [[nodiscard]] constexpr auto data() const noexcept -> const_pointer;

    constexpr void shrink_to_fit();

    [[nodiscard]] constexpr auto c_str() const noexcept -> const_pointer;

    [[nodiscard]] auto u8_c_str() const noexcept -> const char8_t *;

    constexpr void reserve(const size_type size);

    constexpr void resize(const size_type count);

    [[nodiscard]] constexpr auto compare(const string &str) const noexcept -> int;

    [[nodiscard]] constexpr auto compare(const string_view &str) const noexcept -> int;

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

    constexpr auto append(const value_type *const str) -> string &;

    auto append(const char8_t *const str) -> string &;

    constexpr auto append(const std::string &str) -> string &;

    auto append(const std::u8string &str) -> string &;

    constexpr auto append(const string &str) -> string &;

    constexpr auto append(const string_view &str) -> string &;

    template <typename iterator_t>
    constexpr auto append(iterator_t begin, iterator_t end) noexcept -> string &;

    constexpr auto operator+=(const char *str) -> string &;

    auto operator+=(const char8_t *str) -> string &;

    constexpr auto operator+=(const std::string &str) -> string &;

    constexpr auto operator+=(const std::string_view &str) -> string &;

    auto operator+=(const std::u8string_view &str) -> string &;

    constexpr auto operator+=(const string &str) -> string &;

    constexpr auto operator+=(const string_view &str) -> string &;

    constexpr auto operator+=(const value_type c) -> string &;

    constexpr auto operator+=(const char8_t c) -> string &;

    [[nodiscard]] constexpr auto as_std_string_view() noexcept -> std::string_view;

    [[nodiscard]] constexpr auto as_std_string_view() const noexcept -> std::string_view;

    [[nodiscard]] auto as_std_u8string_view() noexcept -> std::u8string_view;

    [[nodiscard]] auto as_std_u8string_view() const noexcept -> std::u8string_view;

    constexpr void clear();

    [[nodiscard]] constexpr auto empty() const noexcept -> bool;

    [[nodiscard]] constexpr auto at(const size_type pos) -> reference;

    [[nodiscard]] constexpr auto at(const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto operator[](const size_type pos) -> reference;

    [[nodiscard]] constexpr auto operator[](const size_type pos) const -> const_reference;

    [[nodiscard]] constexpr auto front() noexcept -> reference;

    [[nodiscard]] constexpr auto front() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto back() noexcept -> reference;

    [[nodiscard]] constexpr auto back() const noexcept -> const_reference;

    [[nodiscard]] constexpr auto begin() noexcept -> iterator;

    [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;

    [[nodiscard]] constexpr auto end() noexcept -> iterator;

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

    [[nodiscard]] constexpr auto starts_with(const string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto starts_with(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto starts_with(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const std::string_view &str) const noexcept -> bool;

    [[nodiscard]] auto ends_with(const std::u8string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const string &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const string_view &str) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const value_type c) const noexcept -> bool;

    [[nodiscard]] constexpr auto ends_with(const char8_t c) const noexcept -> bool;

    [[nodiscard]] constexpr auto substr(const size_type pos = 0, const size_type count = npos) const -> string;

    [[nodiscard]] auto find(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto find(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find(const string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto rfind(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto rfind(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto rfind(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto rfind(const string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto rfind(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto rfind(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto rfind(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto rfind(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_first_of(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto find_first_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_first_of(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find_first_of(const string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

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

    [[nodiscard]] constexpr auto find_first_not_of(const string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_first_not_of(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_first_not_of(const char8_t c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_last_of(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] auto find_last_of(const std::u8string_view &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find_last_of(const string &str, const size_type pos = 0) const noexcept -> size_type;

    [[nodiscard]] constexpr auto find_last_of(const string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

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

    [[nodiscard]] constexpr auto find_last_not_of(const string_view &str, const size_type pos = 0) const noexcept
        -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const value_type *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] auto find_last_not_of(const char8_t *str, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const value_type c, const size_type pos = 0) const -> size_type;

    [[nodiscard]] constexpr auto find_last_not_of(const char8_t c, const size_type pos = 0) const -> size_type;

    void replace(const size_type pos, const size_type count, const string_view &str);

private:
    std::string str_;
};

inline constexpr auto operator+(const string &lhs, const string &rhs) -> string;

inline constexpr auto operator+(const string &lhs, const std::string &rhs) -> string;

inline constexpr auto operator+(const std::string &lhs, const string &rhs) -> string;

inline auto operator+(const string &lhs, const std::u8string &rhs) -> string;

inline auto operator+(const std::u8string &lhs, const string &rhs) -> string;

inline constexpr auto operator+(const string &lhs, const char *const rhs) -> string;

inline constexpr auto operator+(const char *const lhs, const string &rhs) -> string;

inline auto operator+(const string &lhs, const char8_t *const rhs) -> string;

inline auto operator+(const char8_t *const lhs, const string &rhs) -> string;

inline constexpr auto operator+(const string_view &lhs, const string &rhs) -> string;

inline constexpr auto operator+(const string_view &lhs, const string_view &rhs) -> string;

inline constexpr auto operator+(const string_view &lhs, const std::string &rhs) -> string;

inline constexpr auto operator+(const std::string &lhs, const string_view &rhs) -> string;

inline auto operator+(const string_view &lhs, const std::u8string &rhs) -> string;

inline auto operator+(const std::u8string &lhs, const string_view &rhs) -> string;

inline constexpr auto operator+(const string_view &lhs, const char *const rhs) -> string;

inline constexpr auto operator+(const char *const lhs, const string_view &rhs) -> string;

inline auto operator+(const string_view &lhs, const char8_t *const rhs) -> string;

inline auto operator+(const char8_t *const lhs, const string_view &rhs) -> string;

inline auto operator<<(std::ostream &os, const string &str) -> std::ostream &;

} // namespace aeon::common

#include <aeon/common/impl/string_impl.h>

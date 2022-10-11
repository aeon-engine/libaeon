// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string.h>

namespace aeon::common
{

inline constexpr string_view::string_view() noexcept
    : str_{}
{
}

inline constexpr string_view::string_view(const char *const str)
    : str_{str}
{
}

inline string_view::string_view(const char8_t *const str)
    : str_{reinterpret_cast<const char *const>(str)}
{
}

inline constexpr string_view::string_view(const std::string &str) noexcept
    : str_{str}
{
}

inline string_view::string_view(const std::u8string &str)
    : str_{reinterpret_cast<const char *const>(std::data(str))}
{
}

inline constexpr string_view::string_view(const std::string_view &str) noexcept
    : str_{str}
{
}

inline constexpr string_view::string_view(const string &str) noexcept
    : str_{str.str_}
{
}

inline string_view::string_view(const std::u8string_view &str)
    : str_{reinterpret_cast<const char *const>(std::data(str))}
{
}

inline constexpr auto string_view::operator=(const value_type *const str) -> string_view &
{
    assign(str);
    return *this;
}

inline constexpr auto string_view::operator=(const std::string &str) -> string_view &
{
    assign(str);
    return *this;
}

inline auto string_view::operator=(const char8_t *const str) -> string_view &
{
    assign(str);
    return *this;
}

inline auto string_view::operator=(const std::u8string &str) -> string_view &
{
    assign(str);
    return *this;
}

inline constexpr void string_view::assign(const value_type *const str)
{
    str_ = str;
}

inline constexpr void string_view::assign(const std::string &str)
{
    str_ = str;
}

inline void string_view::assign(const char8_t *const str)
{
    str_ = reinterpret_cast<const char *const>(str);
}

inline void string_view::assign(const std::u8string &str)
{
    str_ = reinterpret_cast<const char *const>(std::data(str));
}

inline constexpr void string_view::assign(const string &str)
{
    str_ = str.str_;
}

[[nodiscard]] inline constexpr auto string_view::size() const noexcept -> size_type
{
    return std::size(str_);
}

[[nodiscard]] inline constexpr auto string_view::data() const noexcept -> const_pointer
{
    return std::data(str_);
}

[[nodiscard]] inline constexpr auto string_view::compare(const string &str) const noexcept -> int
{
    return str_.compare(str.str_);
}

[[nodiscard]] inline constexpr auto string_view::compare(const std::string &str) const noexcept -> int
{
    return str_.compare(str);
}

[[nodiscard]] inline auto string_view::compare(const std::u8string &str) const noexcept -> int
{
    return str_.compare(reinterpret_cast<const char *const>(std::data(str)));
}

[[nodiscard]] inline constexpr auto string_view::compare(const value_type *const str) const noexcept -> int
{
    return str_.compare(str);
}

[[nodiscard]] inline auto string_view::compare(const char8_t *const str) const noexcept -> int
{
    return str_.compare(reinterpret_cast<const char *const>(str));
}

inline constexpr auto string_view::operator==(const string &str) const -> bool
{
    return str_ == str.str_;
}

inline constexpr auto string_view::operator==(const std::string &str) const -> bool
{
    return str_ == str;
}

inline auto string_view::operator==(const std::u8string &str) const -> bool
{
    return str_ == reinterpret_cast<const char *const>(std::data(str));
}

inline constexpr auto string_view::operator==(const value_type *const str) const -> bool
{
    return str_ == str;
}

inline auto string_view::operator==(const char8_t *const str) const -> bool
{
    return str_ == reinterpret_cast<const char *const>(str);
}

inline constexpr auto string_view::operator<=>(const string &str) const -> std::strong_ordering
{
    return str_ <=> str.str_;
}

constexpr auto string_view::operator<=>(const string_view &str) const -> std::strong_ordering
{
    return str_ <=> str.str_;
}

inline constexpr auto string_view::operator<=>(const std::string &str) const -> std::strong_ordering
{
    return str_ <=> str;
}

inline auto string_view::operator<=>(const std::u8string &str) const -> std::strong_ordering
{
    return str_ <=> reinterpret_cast<const char *const>(std::data(str));
}

inline constexpr auto string_view::operator<=>(const value_type *const str) const -> std::strong_ordering
{
    return str_ <=> str;
}

inline auto string_view::operator<=>(const char8_t *const str) const -> std::strong_ordering
{
    return str_ <=> reinterpret_cast<const char *const>(str);
}

[[nodiscard]] inline constexpr auto string_view::as_std_string_view() noexcept -> std::string_view
{
    return str_;
}

[[nodiscard]] inline constexpr auto string_view::as_std_string_view() const noexcept -> std::string_view
{
    return str_;
}

[[nodiscard]] inline auto string_view::as_std_u8string_view() noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<const char8_t *>(std::data(str_)), std::size(str_)};
}

[[nodiscard]] inline auto string_view::as_std_u8string_view() const noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<const char8_t *const>(std::data(str_)), std::size(str_)};
}

[[nodiscard]] inline constexpr auto string_view::empty() const noexcept -> bool
{
    return str_.empty();
}

[[nodiscard]] inline constexpr auto string_view::at(const size_type pos) const -> const_reference
{
    return str_.at(pos);
}

[[nodiscard]] inline constexpr auto string_view::operator[](const size_type pos) const -> const_reference
{
    return str_[pos];
}

[[nodiscard]] inline constexpr auto string_view::front() const noexcept -> const_reference
{
    return str_.front();
}

[[nodiscard]] inline constexpr auto string_view::back() const noexcept -> const_reference
{
    return str_.back();
}

[[nodiscard]] inline constexpr auto string_view::begin() const noexcept -> const_iterator
{
    return str_.begin();
}

[[nodiscard]] inline constexpr auto string_view::cbegin() const noexcept -> const_iterator
{
    return str_.cbegin();
}

[[nodiscard]] inline constexpr auto string_view::end() const noexcept -> const_iterator
{
    return str_.end();
}

[[nodiscard]] inline constexpr auto string_view::cend() const noexcept -> const_iterator
{
    return str_.cend();
}

[[nodiscard]] inline constexpr auto string_view::rbegin() noexcept -> reverse_iterator
{
    return str_.rbegin();
}

[[nodiscard]] inline constexpr auto string_view::rbegin() const noexcept -> const_reverse_iterator
{
    return str_.rbegin();
}

[[nodiscard]] inline constexpr auto string_view::crbegin() const noexcept -> const_reverse_iterator
{
    return str_.crbegin();
}

[[nodiscard]] inline constexpr auto string_view::rend() noexcept -> reverse_iterator
{
    return str_.rend();
}

[[nodiscard]] inline constexpr auto string_view::rend() const noexcept -> const_reverse_iterator
{
    return str_.rend();
}

[[nodiscard]] inline constexpr auto string_view::crend() const noexcept -> const_reverse_iterator
{
    return str_.crend();
}

[[nodiscard]] inline constexpr auto string_view::starts_with(const std::string_view &str) const noexcept -> bool
{
    return str_.starts_with(str);
}

[[nodiscard]] inline auto string_view::starts_with(const std::u8string_view &str) const noexcept -> bool
{
    return str_.starts_with(reinterpret_cast<const char *const>(std::data(str)));
}

[[nodiscard]] inline constexpr auto string_view::starts_with(const string &str) const noexcept -> bool
{
    return str_.starts_with(str.str_);
}

[[nodiscard]] inline constexpr auto string_view::starts_with(const value_type c) const noexcept -> bool
{
    return str_.starts_with(c);
}

[[nodiscard]] inline constexpr auto string_view::starts_with(const char8_t c) const noexcept -> bool
{
    return str_.starts_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto string_view::ends_with(const std::string_view &str) const noexcept -> bool
{
    return str_.ends_with(str);
}

[[nodiscard]] inline auto string_view::ends_with(const std::u8string_view &str) const noexcept -> bool
{
    return str_.ends_with(reinterpret_cast<const char *const>(std::data(str)));
}

[[nodiscard]] inline constexpr auto string_view::ends_with(const string &str) const noexcept -> bool
{
    return str_.ends_with(str.str_);
}

[[nodiscard]] inline constexpr auto string_view::ends_with(const value_type c) const noexcept -> bool
{
    return str_.ends_with(c);
}

[[nodiscard]] inline constexpr auto string_view::ends_with(const char8_t c) const noexcept -> bool
{
    return str_.ends_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto string_view::substr(const size_type pos, const size_type count) const -> string_view
{
    return str_.substr(pos, count);
}

[[nodiscard]] inline auto string_view::find(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find(str, pos);
}

[[nodiscard]] inline auto string_view::find(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find(reinterpret_cast<const char *const>(std::data(str)), pos);
}

[[nodiscard]] inline constexpr auto string_view::find(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string_view::find(const value_type *str, const size_type pos) const -> size_type
{
    return str_.find(str, pos);
}

[[nodiscard]] inline auto string_view::find(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string_view::find(const value_type c, const size_type pos) const -> size_type
{
    return str_.find(c, pos);
}

[[nodiscard]] inline constexpr auto string_view::find(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string_view::rfind(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.rfind(str, pos);
}

[[nodiscard]] inline auto string_view::rfind(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.rfind(reinterpret_cast<const char *const>(std::data(str)), pos);
}

[[nodiscard]] inline constexpr auto string_view::rfind(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.rfind(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string_view::rfind(const value_type *str, const size_type pos) const -> size_type
{
    return str_.rfind(str, pos);
}

[[nodiscard]] inline auto string_view::rfind(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.rfind(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string_view::rfind(const value_type c, const size_type pos) const -> size_type
{
    return str_.rfind(c, pos);
}

[[nodiscard]] inline constexpr auto string_view::rfind(const char8_t c, const size_type pos) const -> size_type
{
    return str_.rfind(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string_view::find_first_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_first_of(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(reinterpret_cast<const char *const>(std::data(str)), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_of(const value_type *str, const size_type pos) const
    -> size_type
{
    return str_.find_first_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_first_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_first_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_of(const value_type c, const size_type pos) const
    -> size_type
{
    return str_.find_first_of(c, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_of(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find_first_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string_view::find_first_not_of(const std::string_view &str,
                                                         const size_type pos) const noexcept -> size_type
{
    return str_.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_first_not_of(const std::u8string_view &str,
                                                         const size_type pos) const noexcept -> size_type
{
    return str_.find_first_not_of(reinterpret_cast<const char *const>(std::data(str)), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_not_of(const string &str,
                                                                   const size_type pos) const noexcept -> size_type
{
    return str_.find_first_not_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_not_of(const value_type *str, const size_type pos) const
    -> size_type
{
    return str_.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_first_not_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_first_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_not_of(const value_type c, const size_type pos) const
    -> size_type
{
    return str_.find_first_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_first_not_of(const char8_t c, const size_type pos) const
    -> size_type
{
    return str_.find_first_not_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string_view::find_last_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_last_of(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(reinterpret_cast<const char *const>(std::data(str)), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_of(const value_type *str, const size_type pos) const
    -> size_type
{
    return str_.find_last_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_last_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_last_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_of(const value_type c, const size_type pos) const
    -> size_type
{
    return str_.find_last_of(c, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_of(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find_last_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string_view::find_last_not_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_last_not_of(const std::u8string_view &str,
                                                        const size_type pos) const noexcept -> size_type
{
    return str_.find_last_not_of(reinterpret_cast<const char *const>(std::data(str)), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_not_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_not_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_not_of(const value_type *str, const size_type pos) const
    -> size_type
{
    return str_.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto string_view::find_last_not_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_last_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_not_of(const value_type c, const size_type pos) const
    -> size_type
{
    return str_.find_last_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto string_view::find_last_not_of(const char8_t c, const size_type pos) const
    -> size_type
{
    return str_.find_last_not_of(static_cast<const char>(c), pos);
}

constexpr void string_view::remove_prefix(const size_type n)
{
    str_.remove_prefix(n);
}

constexpr void string_view::remove_suffix(const size_type n)
{
    str_.remove_suffix(n);
}

} // namespace aeon::common

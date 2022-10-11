// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/string_view.h>

namespace aeon::common
{

inline constexpr string::string() noexcept
    : str_{}
{
}

inline constexpr string::string(const char *const str)
    : str_{str}
{
}

inline string::string(const char8_t *const str)
    : str_{reinterpret_cast<const char *const>(str)}
{
}

inline constexpr string::string(std::string str) noexcept
    : str_{std::move(str)}
{
}

inline constexpr string::string(const std::u8string &str)
    : str_{std::begin(str), std::end(str)}
{
}

inline constexpr string::string(const string_view &str) noexcept
    : str_{str.str_}
{
}

inline constexpr auto string::operator=(const value_type *const str) -> string &
{
    assign(str);
    return *this;
}

inline constexpr auto string::operator=(std::string str) -> string &
{
    assign(std::move(str));
    return *this;
}

inline auto string::operator=(const char8_t *const str) -> string &
{
    assign(str);
    return *this;
}

inline constexpr auto string::operator=(const std::u8string &str) -> string &
{
    assign(str);
    return *this;
}

inline constexpr auto string::operator=(const string_view &str) -> string &
{
    assign(str);
    return *this;
}

inline constexpr void string::assign(const value_type *const str)
{
    str_ = str;
}

inline constexpr void string::assign(std::string &&str)
{
    str_ = std::move(str);
}

inline void string::assign(const char8_t *const str)
{
    str_ = reinterpret_cast<const char *const>(str);
}

inline constexpr void string::assign(const std::u8string &str)
{
    str_ = std::string{std::begin(str), std::end(str)};
}

inline constexpr void string::assign(const string &str)
{
    str_ = str.str_;
}

constexpr void string::assign(const string_view &str)
{
    str_ = str.str_;
}

inline constexpr auto string::insert(const size_type index, const value_type *const str) -> string &
{
    str_.insert(index, str);
    return *this;
}

inline auto string::insert(const size_type index, const char8_t *const str) -> string &
{
    str_.insert(index, reinterpret_cast<const char *const>(str));
    return *this;
}

inline constexpr auto string::insert(const size_type index, const std::string_view &str) -> string &
{
    str_.insert(index, str);
    return *this;
}

inline auto string::insert(const size_type index, const std::u8string_view &str) -> string &
{
    str_.insert(index, reinterpret_cast<const char *const>(std::data(str)), std::size(str));
    return *this;
}

inline auto string::insert(const size_type index, const string &str) -> string &
{
    str_.insert(index, str.str_);
    return *this;
}

inline auto string::insert(const size_type index, const string_view &str) -> string &
{
    str_.insert(index, str.str_);
    return *this;
}

inline constexpr auto string::erase(const size_type index, const size_type count) -> string &
{
    str_.erase(index, count);
    return *this;
}

inline constexpr auto string::erase(const_iterator position) -> iterator
{
    return str_.erase(position);
}

inline constexpr auto string::erase(const_iterator first, const_iterator last) -> iterator
{
    return str_.erase(first, last);
}

[[nodiscard]] inline constexpr auto string::str() noexcept -> std::string &
{
    return str_;
}

[[nodiscard]] inline constexpr auto string::str() const noexcept -> const std::string &
{
    return str_;
}

[[nodiscard]] inline auto string::u8str() const noexcept -> std::u8string
{
    return std::u8string{reinterpret_cast<const char8_t *const>(std::data(str_)), std::size(str_)};
}

[[nodiscard]] inline constexpr auto string::size() const noexcept -> size_type
{
    return std::size(str_);
}

[[nodiscard]] inline constexpr auto string::capacity() const noexcept -> size_type
{
    return str_.capacity();
}

[[nodiscard]] inline constexpr auto string::data() noexcept -> pointer
{
    return std::data(str_);
}

[[nodiscard]] inline constexpr auto string::data() const noexcept -> const_pointer
{
    return std::data(str_);
}

inline constexpr void string::shrink_to_fit()
{
    str_.shrink_to_fit();
}

[[nodiscard]] inline constexpr auto string::c_str() const noexcept -> const_pointer
{
    return str_.c_str();
}

[[nodiscard]] inline auto string::u8_c_str() const noexcept -> const char8_t *
{
    return reinterpret_cast<const char8_t *const>(c_str());
}

inline constexpr void string::reserve(const size_type size)
{
    str_.reserve(size);
}

inline constexpr void string::resize(const size_type count)
{
    str_.resize(count);
}

[[nodiscard]] inline constexpr auto string::compare(const string &str) const noexcept -> int
{
    return str_.compare(str.str_);
}

[[nodiscard]] inline constexpr auto string::compare(const string_view &str) const noexcept -> int
{
    return str_.compare(str.str_);
}

[[nodiscard]] inline constexpr auto string::compare(const std::string &str) const noexcept -> int
{
    return str_.compare(str);
}

[[nodiscard]] inline auto string::compare(const std::u8string &str) const noexcept -> int
{
    return str_.compare(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto string::compare(const value_type *const str) const noexcept -> int
{
    return str_.compare(str);
}

[[nodiscard]] inline auto string::compare(const char8_t *const str) const noexcept -> int
{
    return str_.compare(reinterpret_cast<const char *const>(str));
}

inline constexpr auto string::operator==(const string &str) const -> bool
{
    return str_ == str.str_;
}

inline constexpr auto string::operator==(const string_view &str) const -> bool
{
    return str_ == str.str_;
}

inline constexpr auto string::operator==(const std::string &str) const -> bool
{
    return str_ == str;
}

inline auto string::operator==(const std::u8string &str) const -> bool
{
    return str_ == std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto string::operator==(const value_type *const str) const -> bool
{
    return str_ == str;
}

inline auto string::operator==(const char8_t *const str) const -> bool
{
    return str_ == reinterpret_cast<const char *const>(str);
}

inline constexpr auto string::operator<=>(const string &str) const -> std::strong_ordering
{
    return str_ <=> str.str_;
}

inline constexpr auto string::operator<=>(const string_view &str) const -> std::strong_ordering
{
    return str_ <=> str.str_;
}

inline constexpr auto string::operator<=>(const std::string &str) const -> std::strong_ordering
{
    return str_ <=> str;
}

inline auto string::operator<=>(const std::u8string &str) const -> std::strong_ordering
{
    return str_ <=> std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
}

inline constexpr auto string::operator<=>(const value_type *const str) const -> std::strong_ordering
{
    return str_ <=> str;
}

inline auto string::operator<=>(const char8_t *const str) const -> std::strong_ordering
{
    return str_ <=> reinterpret_cast<const char *const>(str);
}

inline constexpr auto string::append(const value_type *const str) -> string &
{
    str_.append(str);
    return *this;
}

inline auto string::append(const char8_t *const str) -> string &
{
    str_.append(reinterpret_cast<const char *const>(str));
    return *this;
}

inline constexpr auto string::append(const std::string &str) -> string &
{
    str_.append(str);
    return *this;
}

inline auto string::append(const std::u8string &str) -> string &
{
    str_.append(std::begin(str), std::end(str));
    return *this;
}

inline constexpr auto string::append(const string &str) -> string &
{
    str_.append(str.str_);
    return *this;
}

inline constexpr auto string::append(const string_view &str) -> string &
{
    str_.append(str.str_);
    return *this;
}

inline constexpr auto string::operator+=(const std::string_view &str) -> string &
{
    str_ += str;
    return *this;
}

inline auto string::operator+=(const std::u8string_view &str) -> string &
{
    str_ += std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)};
    return *this;
}

inline constexpr auto string::operator+=(const string &str) -> string &
{
    str_ += str.str_;
    return *this;
}

inline constexpr auto string::operator+=(const string_view &str) -> string &
{
    str_ += str.str_;
    return *this;
}

inline constexpr auto string::operator+=(const value_type c) -> string &
{
    str_ += c;
    return *this;
}

inline constexpr auto string::operator+=(const char8_t c) -> string &
{
    str_ += static_cast<const char>(c);
    return *this;
}

[[nodiscard]] inline constexpr auto string::as_std_string_view() noexcept -> std::string_view
{
    return str_;
}

[[nodiscard]] inline constexpr auto string::as_std_string_view() const noexcept -> std::string_view
{
    return str_;
}

[[nodiscard]] inline auto string::as_std_u8string_view() noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<char8_t *>(std::data(str_)), std::size(str_)};
}

[[nodiscard]] inline auto string::as_std_u8string_view() const noexcept -> std::u8string_view
{
    return std::u8string_view{reinterpret_cast<const char8_t *const>(std::data(str_)), std::size(str_)};
}

inline constexpr void string::clear()
{
    str_.clear();
}

[[nodiscard]] inline constexpr auto string::empty() const noexcept -> bool
{
    return str_.empty();
}

[[nodiscard]] inline constexpr auto string::at(const size_type pos) -> reference
{
    return str_.at(pos);
}

[[nodiscard]] inline constexpr auto string::at(const size_type pos) const -> const_reference
{
    return str_.at(pos);
}

[[nodiscard]] inline constexpr auto string::operator[](const size_type pos) -> reference
{
    return str_[pos];
}

[[nodiscard]] inline constexpr auto string::operator[](const size_type pos) const -> const_reference
{
    return str_[pos];
}

[[nodiscard]] inline constexpr auto string::front() noexcept -> reference
{
    return str_.front();
}

[[nodiscard]] inline constexpr auto string::front() const noexcept -> const_reference
{
    return str_.front();
}

[[nodiscard]] inline constexpr auto string::back() noexcept -> reference
{
    return str_.back();
}

[[nodiscard]] inline constexpr auto string::back() const noexcept -> const_reference
{
    return str_.back();
}

[[nodiscard]] inline constexpr auto string::begin() noexcept -> iterator
{
    return str_.begin();
}

[[nodiscard]] inline constexpr auto string::begin() const noexcept -> const_iterator
{
    return str_.begin();
}

[[nodiscard]] inline constexpr auto string::cbegin() const noexcept -> const_iterator
{
    return str_.cbegin();
}

[[nodiscard]] inline constexpr auto string::end() noexcept -> iterator
{
    return str_.end();
}

[[nodiscard]] inline constexpr auto string::end() const noexcept -> const_iterator
{
    return str_.end();
}

[[nodiscard]] inline constexpr auto string::cend() const noexcept -> const_iterator
{
    return str_.cend();
}

[[nodiscard]] inline constexpr auto string::rbegin() noexcept -> reverse_iterator
{
    return str_.rbegin();
}

[[nodiscard]] inline constexpr auto string::rbegin() const noexcept -> const_reverse_iterator
{
    return str_.rbegin();
}

[[nodiscard]] inline constexpr auto string::crbegin() const noexcept -> const_reverse_iterator
{
    return str_.crbegin();
}

[[nodiscard]] inline constexpr auto string::rend() noexcept -> reverse_iterator
{
    return str_.rend();
}

[[nodiscard]] inline constexpr auto string::rend() const noexcept -> const_reverse_iterator
{
    return str_.rend();
}

[[nodiscard]] inline constexpr auto string::crend() const noexcept -> const_reverse_iterator
{
    return str_.crend();
}

[[nodiscard]] inline constexpr auto string::starts_with(const std::string_view &str) const noexcept -> bool
{
    return str_.starts_with(str);
}

[[nodiscard]] inline auto string::starts_with(const std::u8string_view &str) const noexcept -> bool
{
    return str_.starts_with(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto string::starts_with(const string &str) const noexcept -> bool
{
    return str_.starts_with(str.str_);
}

[[nodiscard]] inline constexpr auto string::starts_with(const string_view &str) const noexcept -> bool
{
    return str_.starts_with(str.str_);
}

[[nodiscard]] inline constexpr auto string::starts_with(const value_type c) const noexcept -> bool
{
    return str_.starts_with(c);
}

[[nodiscard]] inline constexpr auto string::starts_with(const char8_t c) const noexcept -> bool
{
    return str_.starts_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto string::ends_with(const std::string_view &str) const noexcept -> bool
{
    return str_.ends_with(str);
}

[[nodiscard]] inline auto string::ends_with(const std::u8string_view &str) const noexcept -> bool
{
    return str_.ends_with(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)});
}

[[nodiscard]] inline constexpr auto string::ends_with(const string &str) const noexcept -> bool
{
    return str_.ends_with(str.str_);
}

[[nodiscard]] inline constexpr auto string::ends_with(const string_view &str) const noexcept -> bool
{
    return str_.ends_with(str.str_);
}

[[nodiscard]] inline constexpr auto string::ends_with(const value_type c) const noexcept -> bool
{
    return str_.ends_with(c);
}

[[nodiscard]] inline constexpr auto string::ends_with(const char8_t c) const noexcept -> bool
{
    return str_.ends_with(static_cast<const char>(c));
}

[[nodiscard]] inline constexpr auto string::substr(const size_type pos, const size_type count) const -> string
{
    return str_.substr(pos, count);
}

[[nodiscard]] inline auto string::find(const std::string_view &str, const size_type pos) const noexcept -> size_type
{
    return str_.find(str, pos);
}

[[nodiscard]] inline auto string::find(const std::u8string_view &str, const size_type pos) const noexcept -> size_type
{
    return str_.find(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}, pos);
}

[[nodiscard]] inline constexpr auto string::find(const string &str, const size_type pos) const noexcept -> size_type
{
    return str_.find(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find(const string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find(const value_type *str, const size_type pos) const -> size_type
{
    return str_.find(str, pos);
}

[[nodiscard]] inline auto string::find(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string::find(const value_type c, const size_type pos) const -> size_type
{
    return str_.find(c, pos);
}

[[nodiscard]] inline constexpr auto string::find(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string::rfind(const std::string_view &str, const size_type pos) const noexcept -> size_type
{
    return str_.rfind(str, pos);
}

[[nodiscard]] inline auto string::rfind(const std::u8string_view &str, const size_type pos) const noexcept -> size_type
{
    return str_.rfind(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)}, pos);
}

[[nodiscard]] inline constexpr auto string::rfind(const string &str, const size_type pos) const noexcept -> size_type
{
    return str_.rfind(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::rfind(const string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.rfind(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::rfind(const value_type *str, const size_type pos) const -> size_type
{
    return str_.rfind(str, pos);
}

[[nodiscard]] inline auto string::rfind(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.rfind(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string::rfind(const value_type c, const size_type pos) const -> size_type
{
    return str_.rfind(c, pos);
}

[[nodiscard]] inline constexpr auto string::rfind(const char8_t c, const size_type pos) const -> size_type
{
    return str_.rfind(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string::find_first_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(str, pos);
}

[[nodiscard]] inline auto string::find_first_of(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                              pos);
}

[[nodiscard]] inline constexpr auto string::find_first_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_first_of(const string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_first_of(const value_type *str, const size_type pos) const -> size_type
{
    return str_.find_first_of(str, pos);
}

[[nodiscard]] inline auto string::find_first_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_first_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string::find_first_of(const value_type c, const size_type pos) const -> size_type
{
    return str_.find_first_of(c, pos);
}

[[nodiscard]] inline constexpr auto string::find_first_of(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find_first_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string::find_first_not_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto string::find_first_not_of(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_not_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                                  pos);
}

[[nodiscard]] inline constexpr auto string::find_first_not_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_first_not_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_first_not_of(const string_view &str,
                                                              const size_type pos) const noexcept -> size_type
{
    return str_.find_first_not_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_first_not_of(const value_type *str, const size_type pos) const
    -> size_type
{
    return str_.find_first_not_of(str, pos);
}

[[nodiscard]] inline auto string::find_first_not_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_first_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string::find_first_not_of(const value_type c, const size_type pos) const
    -> size_type
{
    return str_.find_first_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto string::find_first_not_of(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find_first_not_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string::find_last_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(str, pos);
}

[[nodiscard]] inline auto string::find_last_of(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                             pos);
}

[[nodiscard]] inline constexpr auto string::find_last_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_last_of(const string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_last_of(const value_type *str, const size_type pos) const -> size_type
{
    return str_.find_last_of(str, pos);
}

[[nodiscard]] inline auto string::find_last_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_last_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string::find_last_of(const value_type c, const size_type pos) const -> size_type
{
    return str_.find_last_of(c, pos);
}

[[nodiscard]] inline constexpr auto string::find_last_of(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find_last_of(static_cast<const char>(c), pos);
}

[[nodiscard]] inline auto string::find_last_not_of(const std::string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto string::find_last_not_of(const std::u8string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_not_of(std::string_view{reinterpret_cast<const char *const>(std::data(str)), std::size(str)},
                                 pos);
}

[[nodiscard]] inline constexpr auto string::find_last_not_of(const string &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_not_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_last_not_of(const string_view &str, const size_type pos) const noexcept
    -> size_type
{
    return str_.find_last_not_of(str.str_, pos);
}

[[nodiscard]] inline constexpr auto string::find_last_not_of(const value_type *str, const size_type pos) const
    -> size_type
{
    return str_.find_last_not_of(str, pos);
}

[[nodiscard]] inline auto string::find_last_not_of(const char8_t *str, const size_type pos) const -> size_type
{
    return str_.find_last_not_of(reinterpret_cast<const char *const>(str), pos);
}

[[nodiscard]] inline constexpr auto string::find_last_not_of(const value_type c, const size_type pos) const -> size_type
{
    return str_.find_last_not_of(c, pos);
}

[[nodiscard]] inline constexpr auto string::find_last_not_of(const char8_t c, const size_type pos) const -> size_type
{
    return str_.find_last_not_of(static_cast<const char>(c), pos);
}

inline constexpr auto operator+(const string &lhs, const string &rhs) -> string
{
    return lhs.str() + rhs.str();
}

inline constexpr auto operator+(const string &lhs, const std::string &rhs) -> string
{
    return lhs.str() + rhs;
}

inline constexpr auto operator+(const std::string &lhs, const string &rhs) -> string
{
    return lhs + rhs.str();
}

inline auto operator+(const string &lhs, const std::u8string &rhs) -> string
{
    return lhs + string{rhs};
}

inline auto operator+(const std::u8string &lhs, const string &rhs) -> string
{
    return string{lhs} + rhs;
}

inline constexpr auto operator+(const string &lhs, const char *const rhs) -> string
{
    return lhs.str() + rhs;
}

inline constexpr auto operator+(const char *const lhs, const string &rhs) -> string
{
    return lhs + rhs.str();
}

inline auto operator+(const string &lhs, const char8_t *const rhs) -> string
{
    return lhs.str() + reinterpret_cast<const char *const>(rhs);
}

inline auto operator+(const char8_t *const lhs, const string &rhs) -> string
{
    return reinterpret_cast<const char *const>(lhs) + rhs.str();
}

inline constexpr auto operator+(const string_view &lhs, const string &rhs) -> string
{
    return lhs.as_std_string_view() + rhs.str();
}

inline constexpr auto operator+(const string_view &lhs, const string_view &rhs) -> string
{
    return lhs.as_std_string_view() + rhs.as_std_string_view();
}

inline constexpr auto operator+(const string_view &lhs, const std::string &rhs) -> string
{
    return lhs.as_std_string_view() + rhs;
}

inline constexpr auto operator+(const std::string &lhs, const string_view &rhs) -> string
{
    return lhs + rhs.as_std_string_view();
}

inline auto operator+(const string_view &lhs, const std::u8string &rhs) -> string
{
    return std::string{lhs.as_std_string_view()} + reinterpret_cast<const char *const>(std::data(rhs));
}

inline auto operator+(const std::u8string &lhs, const string_view &rhs) -> string
{
    return std::string_view{reinterpret_cast<const char *const>(std::data(lhs)), std::size(lhs)} +
           rhs.as_std_string_view();
}

inline constexpr auto operator+(const string_view &lhs, const char *const rhs) -> string
{
    return lhs.as_std_string_view() + rhs;
}

inline constexpr auto operator+(const char *const lhs, const string_view &rhs) -> string
{
    return lhs + rhs.as_std_string_view();
}

inline auto operator+(const string_view &lhs, const char8_t *const rhs) -> string
{
    return lhs.as_std_string_view() + reinterpret_cast<const char *const>(rhs);
}

inline auto operator+(const char8_t *const lhs, const string_view &rhs) -> string
{
    return reinterpret_cast<const char *const>(lhs) + rhs.as_std_string_view();
}

} // namespace aeon::common

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/containers/buffer.h>
#include <string>
#include <string_view>

namespace aeon::common::containers
{

class string
{
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

    constexpr string() noexcept
        : str_{}
    {
    }

    constexpr string(const char *const str)
        : str_{str}
    {
    }

    string(const char8_t *const str)
        : str_{reinterpret_cast<const char *const>(str)}
    {
    }

    constexpr string(std::string &&str) noexcept
        : str_{std::move(str)}
    {
    }

    constexpr string(const std::u8string &str)
        : str_{std::begin(str), std::end(str)}
    {
    }

    constexpr string(const string &other) = default;
    constexpr auto operator=(const string &other) -> string & = default;

    constexpr string(string &&other) noexcept = default;
    constexpr auto operator=(string &&other) noexcept -> string & = default;

    constexpr ~string() = default;

    constexpr auto operator=(const value_type *const str) -> string &
    {
        assign(str);
        return *this;
    }

    constexpr auto operator=(std::string &&str) -> string &
    {
        assign(std::move(str));
        return *this;
    }

    auto operator=(const char8_t *const str) -> string &
    {
        assign(str);
        return *this;
    }

    constexpr auto operator=(const std::u8string &str) -> string &
    {
        assign(str);
        return *this;
    }

    constexpr void assign(const value_type *const str)
    {
        str_ = str;
    }

    constexpr void assign(std::string &&str)
    {
        str_ = std::move(str);
    }

    void assign(const char8_t *const str)
    {
        str_ = reinterpret_cast<const char *const>(str);
    }

    constexpr void assign(const std::u8string &str)
    {
        str_ = std::string{std::begin(str), std::end(str)};
    }

    constexpr void assign(const string &str)
    {
        str_ = str.str_;
    }

    constexpr auto insert(const size_type index, const value_type *const str) -> string &
    {
        str_.insert(index, str);
        return *this;
    }

    auto insert(const size_type index, const char8_t *const str) -> string &
    {
        str_.insert(index, reinterpret_cast<const char *const>(str));
        return *this;
    }

    constexpr auto insert(const size_type index, const std::string_view &str) -> string &
    {
        str_.insert(index, str);
        return *this;
    }

    auto insert(const size_type index, const std::u8string_view &str) -> string &
    {
        str_.insert(index, reinterpret_cast<const char *const>(std::data(str)));
        return *this;
    }

    constexpr auto erase(size_type index = 0, size_type count = npos) -> string &
    {
        str_.erase(index, count);
        return *this;
    }

    constexpr auto erase(const_iterator position) -> iterator
    {
        return str_.erase(position);
    }

    constexpr auto erase(const_iterator first, const_iterator last) -> iterator
    {
        return str_.erase(first, last);
    }

    [[nodiscard]] constexpr auto str() const noexcept -> const std::string &
    {
        return str_;
    }

    [[nodiscard]] constexpr auto size() const noexcept
    {
        return std::size(str_);
    }

    [[nodiscard]] constexpr auto capacity() const noexcept
    {
        return str_.capacity();
    }

    [[nodiscard]] constexpr auto data() noexcept
    {
        return std::data(str_);
    }

    [[nodiscard]] constexpr auto data() const noexcept
    {
        return std::data(str_);
    }

    constexpr void shrink_to_fit()
    {
        str_.shrink_to_fit();
    }

    [[nodiscard]] constexpr auto c_str() const noexcept
    {
        return str_.c_str();
    }

    [[nodiscard]] auto u8_c_str() const noexcept
    {
        return reinterpret_cast<const char8_t *const>(c_str());
    }

    constexpr void reserve(const size_type size)
    {
        str_.reserve(size);
    }

    constexpr void resize(const size_type count)
    {
        str_.resize(count);
    }

    [[nodiscard]] constexpr auto compare(const string &str) const noexcept
    {
        return str_.compare(str.str_);
    }

    [[nodiscard]] constexpr auto compare(const std::string &str) const noexcept
    {
        return str_.compare(str);
    }

    [[nodiscard]] auto compare(const std::u8string &str) const noexcept
    {
        return str_.compare(reinterpret_cast<const char *const>(std::data(str)));
    }

    [[nodiscard]] constexpr auto compare(const value_type *const str) const noexcept
    {
        return str_.compare(str);
    }

    [[nodiscard]] constexpr auto compare(const char8_t *const str) const noexcept
    {
        return str_.compare(reinterpret_cast<const char *const>(str));
    }

    constexpr auto append(const value_type *const str) -> string &
    {
        str_.append(str);
        return *this;
    }

    constexpr auto append(const char8_t *const str) -> string &
    {
        str_.append(reinterpret_cast<const char *const>(str));
        return *this;
    }

    constexpr auto append(const std::string &str) -> string &
    {
        str_.append(str);
        return *this;
    }

    auto append(const std::u8string &str) -> string &
    {
        str_.append(std::begin(str), std::end(str));
        return *this;
    }

    constexpr auto append(const string &str) -> string &
    {
        str_.append(str.str_);
        return *this;
    }

    constexpr auto operator+=(const std::string_view &str) -> string &
    {
        str_ += str;
        return *this;
    }

    constexpr auto operator+=(const std::u8string_view &str) -> string &
    {
        str_ += reinterpret_cast<const char *const>(std::data(str));
        return *this;
    }

    constexpr auto operator+=(const string &str) -> string &
    {
        str_ += str.str_;
        return *this;
    }

    constexpr auto operator+=(const value_type c) -> string &
    {
        str_ += c;
        return *this;
    }

    constexpr auto operator+=(const char8_t c) -> string &
    {
        str_ += static_cast<const char>(c);
        return *this;
    }

    [[nodiscard]] constexpr auto as_string_view() noexcept -> std::string_view
    {
        return str_;
    }

    [[nodiscard]] constexpr auto as_string_view() const noexcept -> std::string_view
    {
        return str_;
    }

    [[nodiscard]] auto as_u8string_view() noexcept -> std::u8string_view
    {
        return std::u8string_view{reinterpret_cast<char8_t *>(std::data(str_)), std::size(str_)};
    }

    [[nodiscard]] auto as_u8string_view() const noexcept -> std::u8string_view
    {
        return std::u8string_view{reinterpret_cast<const char8_t *const>(std::data(str_)), std::size(str_)};
    }

    constexpr void clear()
    {
        str_.clear();
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return str_.empty();
    }

    [[nodiscard]] constexpr auto at(const size_type pos) -> reference
    {
        return str_.at(pos);
    }

    [[nodiscard]] constexpr auto at(const size_type pos) const -> const_reference
    {
        return str_.at(pos);
    }

    [[nodiscard]] constexpr auto operator[](const size_type pos) -> reference
    {
        return str_[pos];
    }

    [[nodiscard]] constexpr auto operator[](const size_type pos) const -> const_reference
    {
        return str_[pos];
    }

    [[nodiscard]] constexpr auto front() noexcept -> reference
    {
        return str_.front();
    }

    [[nodiscard]] constexpr auto front() const noexcept -> const_reference
    {
        return str_.front();
    }

    [[nodiscard]] constexpr auto back() noexcept -> reference
    {
        return str_.back();
    }

    [[nodiscard]] constexpr auto back() const noexcept -> const_reference
    {
        return str_.back();
    }

    [[nodiscard]] constexpr auto begin() noexcept -> iterator
    {
        return str_.begin();
    }

    [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator
    {
        return str_.begin();
    }

    [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator
    {
        return str_.cbegin();
    }

    [[nodiscard]] constexpr auto end() noexcept -> iterator
    {
        return str_.end();
    }

    [[nodiscard]] constexpr auto end() const noexcept -> const_iterator
    {
        return str_.end();
    }

    [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator
    {
        return str_.cend();
    }

    [[nodiscard]] constexpr auto starts_with(const std::string_view &str) const noexcept -> bool
    {
        return str_.starts_with(str);
    }

    [[nodiscard]] auto starts_with(const std::u8string_view &str) const noexcept -> bool
    {
        return str_.starts_with(reinterpret_cast<const char *const>(std::data(str)));
    }

    [[nodiscard]] constexpr auto starts_with(const string &str) const noexcept -> bool
    {
        return str_.starts_with(str.str_);
    }

    [[nodiscard]] constexpr auto starts_with(const value_type c) const noexcept -> bool
    {
        return str_.starts_with(c);
    }

    [[nodiscard]] constexpr auto starts_with(const char8_t c) const noexcept -> bool
    {
        return str_.starts_with(static_cast<const char>(c));
    }

    [[nodiscard]] constexpr auto ends_with(const std::string_view &str) const noexcept -> bool
    {
        return str_.ends_with(str);
    }

    [[nodiscard]] auto ends_with(const std::u8string_view &str) const noexcept -> bool
    {
        return str_.ends_with(reinterpret_cast<const char *const>(std::data(str)));
    }

    [[nodiscard]] constexpr auto ends_with(const string &str) const noexcept -> bool
    {
        return str_.ends_with(str.str_);
    }

    [[nodiscard]] constexpr auto ends_with(const value_type c) const noexcept -> bool
    {
        return str_.ends_with(c);
    }

    [[nodiscard]] constexpr auto ends_with(const char8_t c) const noexcept -> bool
    {
        return str_.ends_with(static_cast<const char>(c));
    }

    [[nodiscard]] constexpr auto substr(const size_type pos = 0, const size_type count = npos) const -> string
    {
        return str_.substr(pos, count);
    }

    [[nodiscard]] auto find(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find(str, pos);
    }

    [[nodiscard]] constexpr auto find(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find(reinterpret_cast<const char *const>(std::data(str)), pos);
    }

    [[nodiscard]] constexpr auto find(const string &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find(str.str_, pos);
    }

    [[nodiscard]] constexpr auto find(const value_type *str, const size_type pos = 0) const -> size_type
    {
        return str_.find(str, pos);
    }

    [[nodiscard]] auto find(const char8_t *str, const size_type pos = 0) const -> size_type
    {
        return str_.find(reinterpret_cast<const char *const>(str), pos);
    }

    [[nodiscard]] constexpr auto find(const value_type c, const size_type pos = 0) const -> size_type
    {
        return str_.find(c, pos);
    }

    [[nodiscard]] constexpr auto find(const char8_t c, const size_type pos = 0) const -> size_type
    {
        return str_.find(static_cast<const char>(c), pos);
    }

    [[nodiscard]] auto rfind(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.rfind(str, pos);
    }

    [[nodiscard]] constexpr auto rfind(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.rfind(reinterpret_cast<const char *const>(std::data(str)), pos);
    }

    [[nodiscard]] constexpr auto rfind(const string &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.rfind(str.str_, pos);
    }

    [[nodiscard]] constexpr auto rfind(const value_type *str, const size_type pos = 0) const -> size_type
    {
        return str_.rfind(str, pos);
    }

    [[nodiscard]] auto rfind(const char8_t *str, const size_type pos = 0) const -> size_type
    {
        return str_.rfind(reinterpret_cast<const char *const>(str), pos);
    }

    [[nodiscard]] constexpr auto rfind(const value_type c, const size_type pos = 0) const -> size_type
    {
        return str_.rfind(c, pos);
    }

    [[nodiscard]] constexpr auto rfind(const char8_t c, const size_type pos = 0) const -> size_type
    {
        return str_.rfind(static_cast<const char>(c), pos);
    }

    [[nodiscard]] auto find_first_of(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find_first_of(str, pos);
    }

    [[nodiscard]] constexpr auto find_first_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_first_of(reinterpret_cast<const char *const>(std::data(str)), pos);
    }

    [[nodiscard]] constexpr auto find_first_of(const string &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find_first_of(str.str_, pos);
    }

    [[nodiscard]] constexpr auto find_first_of(const value_type *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_of(str, pos);
    }

    [[nodiscard]] auto find_first_of(const char8_t *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_of(reinterpret_cast<const char *const>(str), pos);
    }

    [[nodiscard]] constexpr auto find_first_of(const value_type c, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_of(c, pos);
    }

    [[nodiscard]] constexpr auto find_first_of(const char8_t c, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_of(static_cast<const char>(c), pos);
    }

    [[nodiscard]] auto find_first_not_of(const std::string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_first_not_of(str, pos);
    }

    [[nodiscard]] constexpr auto find_first_not_of(const std::u8string_view &str,
                                                   const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find_first_not_of(reinterpret_cast<const char *const>(std::data(str)), pos);
    }

    [[nodiscard]] constexpr auto find_first_not_of(const string &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_first_not_of(str.str_, pos);
    }

    [[nodiscard]] constexpr auto find_first_not_of(const value_type *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_not_of(str, pos);
    }

    [[nodiscard]] auto find_first_not_of(const char8_t *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_not_of(reinterpret_cast<const char *const>(str), pos);
    }

    [[nodiscard]] constexpr auto find_first_not_of(const value_type c, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_not_of(c, pos);
    }

    [[nodiscard]] constexpr auto find_first_not_of(const char8_t c, const size_type pos = 0) const -> size_type
    {
        return str_.find_first_not_of(static_cast<const char>(c), pos);
    }

    [[nodiscard]] auto find_last_of(const std::string_view &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find_last_of(str, pos);
    }

    [[nodiscard]] constexpr auto find_last_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_last_of(reinterpret_cast<const char *const>(std::data(str)), pos);
    }

    [[nodiscard]] constexpr auto find_last_of(const string &str, const size_type pos = 0) const noexcept -> size_type
    {
        return str_.find_last_of(str.str_, pos);
    }

    [[nodiscard]] constexpr auto find_last_of(const value_type *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_of(str, pos);
    }

    [[nodiscard]] auto find_last_of(const char8_t *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_of(reinterpret_cast<const char *const>(str), pos);
    }

    [[nodiscard]] constexpr auto find_last_of(const value_type c, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_of(c, pos);
    }

    [[nodiscard]] constexpr auto find_last_of(const char8_t c, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_of(static_cast<const char>(c), pos);
    }

    [[nodiscard]] auto find_last_not_of(const std::string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_last_not_of(str, pos);
    }

    [[nodiscard]] constexpr auto find_last_not_of(const std::u8string_view &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_last_not_of(reinterpret_cast<const char *const>(std::data(str)), pos);
    }

    [[nodiscard]] constexpr auto find_last_not_of(const string &str, const size_type pos = 0) const noexcept
        -> size_type
    {
        return str_.find_last_not_of(str.str_, pos);
    }

    [[nodiscard]] constexpr auto find_last_not_of(const value_type *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_not_of(str, pos);
    }

    [[nodiscard]] auto find_last_not_of(const char8_t *str, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_not_of(reinterpret_cast<const char *const>(str), pos);
    }

    [[nodiscard]] constexpr auto find_last_not_of(const value_type c, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_not_of(c, pos);
    }

    [[nodiscard]] constexpr auto find_last_not_of(const char8_t c, const size_type pos = 0) const -> size_type
    {
        return str_.find_last_not_of(static_cast<const char>(c), pos);
    }

private:
    std::string str_;
};

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

inline auto operator<=>(const string &lhs, const string &rhs) -> int
{
    return lhs.compare(rhs);
}

inline auto operator<=>(const string &lhs, const std::string &rhs) -> int
{
    return lhs.compare(rhs);
}

inline auto operator<=>(const std::string &lhs, const string &rhs) -> int
{
    return lhs.compare(rhs.str());
}

inline auto operator<=>(const string &lhs, const std::u8string &rhs) -> int
{
    return lhs.compare(rhs);
}

inline auto operator<=>(const std::u8string &lhs, const string &rhs) -> int
{
    return lhs.compare(rhs.as_u8string_view());
}

inline auto operator<=>(const string &lhs, const char *const rhs) -> int
{
    return lhs.compare(rhs);
}

inline auto operator<=>(const char *const lhs, const string &rhs) -> int
{
    return string{lhs}.compare(rhs);
}

inline auto operator<=>(const string &lhs, const char8_t *const rhs) -> int
{
    return lhs.compare(rhs);
}

inline auto operator<=>(const char8_t *const lhs, const string &rhs) -> int
{
    return string{lhs}.compare(rhs);
}

} // namespace aeon::common::containers

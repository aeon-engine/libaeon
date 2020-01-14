// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <ostream>

namespace aeon::common
{

template <typename T>
class string_table
{
    static constexpr auto npos = std::numeric_limits<std::size_t>::max();

public:
    explicit string_table() noexcept;
    explicit string_table(std::string str) noexcept;
    ~string_table();

    string_table(const string_table &) noexcept = default;
    auto operator=(const string_table &) noexcept -> string_table & = default;

    string_table(string_table &&) noexcept = default;
    auto operator=(string_table &&) noexcept -> string_table & = default;

    auto operator=(std::string str) noexcept -> string_table &;

    [[nodiscard]] auto str() const noexcept -> const std::string &;

    [[nodiscard]] static auto size() noexcept;
    [[nodiscard]] static auto str(const std::size_t i) -> const std::string &;

    template <typename U>
    friend auto operator==(const string_table<U> &lhs, const string_table<U> &rhs) noexcept -> bool;

    template <typename U>
    friend auto operator!=(const string_table<U> &lhs, const string_table<U> &rhs) noexcept -> bool;

private:
    [[nodiscard]] static auto table() noexcept -> std::vector<std::string> &;

    void init(std::string str);

    std::size_t index_;
};

template <typename T>
inline string_table<T>::string_table() noexcept
    : index_{npos}
{
}

template <typename T>
inline string_table<T>::string_table(std::string str) noexcept
    : index_{}
{
    init(std::move(str));
}

template <typename T>
inline string_table<T>::~string_table() = default;

template <typename T>
inline auto string_table<T>::operator=(std::string str) noexcept -> string_table &
{
    init(std::move(str));
    return *this;
}

template <typename T>
[[nodiscard]] inline auto string_table<T>::str() const noexcept -> const std::string &
{
    if (index_ == npos)
    {
        static const std::string str;
        return str;
    }

    aeon_assert_index_bounds(index_, std::size(table()));
    return table()[index_];
}

template <typename T>
[[nodiscard]] inline auto string_table<T>::size() noexcept
{
    return std::size(table());
}

template <typename T>
[[nodiscard]] inline auto string_table<T>::str(const std::size_t i) -> const std::string &
{
    aeon_assert_index_bounds(i, std::size(table()));
    return table().at(i);
}

template <typename T>
[[nodiscard]] inline auto string_table<T>::table() noexcept -> std::vector<std::string> &
{
    static std::vector<std::string> table;
    return table;
}

template <typename T>
inline void string_table<T>::init(std::string str)
{
    if (str.empty())
    {
        index_ = npos;
        return;
    }

    const auto result =
        std::find_if(std::begin(table()), std::end(table()), [&str](const auto &s) { return s == str; });

    if (result != std::end(table()))
    {
        index_ = std::distance(std::begin(table()), result);
        return;
    }

    table().emplace_back(std::move(str));
    index_ = std::size(table()) - 1;
}

template <typename U>
inline auto operator==(const string_table<U> &lhs, const string_table<U> &rhs) noexcept -> bool
{
    return lhs.index_ == rhs.index_;
}

template <typename U>
inline auto operator!=(const string_table<U> &lhs, const string_table<U> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator==(const string_table<T> &lhs, const std::string &rhs) noexcept -> bool
{
    return lhs.str() == rhs;
}

template <typename T>
inline auto operator!=(const string_table<T> &lhs, const std::string &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator==(const std::string &lhs, const string_table<T> &rhs) noexcept -> bool
{
    return lhs == rhs.str();
}

template <typename T>
inline auto operator!=(const std::string &lhs, const string_table<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<(const string_table<T> &lhs, const string_table<T> &rhs) noexcept -> bool
{
    return lhs.str() < rhs.str();
}

template <typename T>
inline auto operator<=(const string_table<T> &lhs, const string_table<T> &rhs) noexcept -> bool
{
    return lhs.str() <= rhs.str();
}

template <typename T>
inline auto operator>(const string_table<T> &lhs, const string_table<T> &rhs) noexcept -> bool
{
    return lhs.str() > rhs.str();
}

template <typename T>
inline auto operator>=(const string_table<T> &lhs, const string_table<T> &rhs) noexcept -> bool
{
    return lhs.str() >= rhs.str();
}

template <typename T>
inline auto operator<<(std::ostream &os, const string_table<T> &str) -> std::ostream &
{
    return os << str.str();
}

} // namespace aeon::common

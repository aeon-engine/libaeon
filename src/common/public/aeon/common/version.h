// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <tuple>
#include <ostream>
#include <string>

namespace aeon::common
{

template <typename T = int>
class version2
{
public:
    constexpr version2() noexcept;

    constexpr explicit version2(const T major, const T minor) noexcept;

    template <typename U>
    constexpr explicit version2(const version2<U> other) noexcept;

    template <typename U>
    constexpr explicit version2(const U major, const U minor) noexcept;

    ~version2() = default;

    constexpr version2(const version2<T> &) noexcept = default;
    constexpr auto operator=(const version2<T> &) noexcept -> version2<T> & = default;

    constexpr version2(version2<T> &&) noexcept = default;
    constexpr auto operator=(version2<T> &&) noexcept -> version2<T> & = default;

    [[nodiscard]] auto str() const -> std::string;

    T major;
    T minor;
};

template <typename T = int>
class version3 : public version2<T>
{
public:
    constexpr version3() noexcept;

    constexpr explicit version3(const T major, const T minor) noexcept;

    constexpr explicit version3(const T major, const T minor, const T patch) noexcept;

    constexpr explicit version3(const version2<T> &ver) noexcept;

    constexpr explicit version3(const version2<T> &ver, const T patch) noexcept;

    template <typename U>
    constexpr explicit version3(const U major, const U minor) noexcept;

    template <typename U>
    constexpr explicit version3(const U major, const U minor, const U patch) noexcept;

    template <typename U>
    constexpr explicit version3(const version2<U> &ver) noexcept;

    template <typename U>
    constexpr explicit version3(const version2<U> &ver, const U patch) noexcept;

    template <typename U>
    constexpr explicit version3(const version3<U> &ver) noexcept;

    ~version3() = default;

    constexpr version3(const version3<T> &) noexcept = default;
    constexpr auto operator=(const version3<T> &) noexcept -> version3<T> & = default;

    constexpr version3(version3<T> &&) noexcept = default;
    constexpr auto operator=(version3<T> &&) noexcept -> version3<T> & = default;

    [[nodiscard]] auto str() const -> std::string;

    T patch;
};

template <typename T = int>
class version4 : public version3<T>
{
public:
    constexpr version4() noexcept;

    constexpr explicit version4(const T major, const T minor) noexcept;

    constexpr explicit version4(const T major, const T minor, const T patch) noexcept;

    constexpr explicit version4(const T major, const T minor, const T patch, const T build) noexcept;

    constexpr explicit version4(const version2<T> &ver) noexcept;

    constexpr explicit version4(const version2<T> &ver, const T patch) noexcept;

    constexpr explicit version4(const version2<T> &ver, const T patch, const T build) noexcept;

    constexpr explicit version4(const version3<T> &ver) noexcept;

    constexpr explicit version4(const version3<T> &ver, const T build) noexcept;

    template <typename U>
    constexpr explicit version4(const U major, const U minor) noexcept;

    template <typename U>
    constexpr explicit version4(const U major, const U minor, const U patch) noexcept;

    template <typename U>
    constexpr explicit version4(const U major, const U minor, const U patch, const U build) noexcept;

    template <typename U>
    constexpr explicit version4(const version2<U> &ver) noexcept;

    template <typename U>
    constexpr explicit version4(const version2<U> &ver, const U patch) noexcept;

    template <typename U>
    constexpr explicit version4(const version2<U> &ver, const U patch, const U build) noexcept;

    template <typename U>
    constexpr explicit version4(const version3<U> &ver) noexcept;

    template <typename U>
    constexpr explicit version4(const version3<U> &ver, const U build) noexcept;

    template <typename U>
    constexpr explicit version4(const version4<U> &ver) noexcept;

    ~version4() = default;

    constexpr version4(const version4<T> &) noexcept = default;
    constexpr auto operator=(const version4<T> &) noexcept -> version4<T> & = default;

    constexpr version4(version4<T> &&) noexcept = default;
    constexpr auto operator=(version4<T> &&) noexcept -> version4<T> & = default;

    [[nodiscard]] auto str() const -> std::string;

    T build;
};

template <typename T>
inline constexpr auto operator<(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator==(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const version2<T> &v) -> std::ostream &;

template <typename T>
inline constexpr auto operator<(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator==(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const version3<T> &v) -> std::ostream &;

template <typename T>
inline constexpr auto operator<(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator>=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator==(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const version4<T> &v) -> std::ostream &;

using version = version4<int>;

} // namespace aeon::common

#include <aeon/common/impl/version_impl.h>

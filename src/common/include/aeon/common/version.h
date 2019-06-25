// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

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
    version2() noexcept;

    explicit version2(const T major, const T minor) noexcept;

    ~version2() = default;

    version2(const version2<T> &) noexcept = default;
    auto operator=(const version2<T> &) noexcept -> version2<T> & = default;

    version2(version2<T> &&) noexcept = default;
    auto operator=(version2<T> &&) noexcept -> version2<T> & = default;

    [[nodiscard]] auto str() const -> std::string;

    T major;
    T minor;
};

template <typename T = int>
class version3 : public version2<T>
{
public:
    version3() noexcept;

    explicit version3(const T major, const T minor) noexcept;

    explicit version3(const T major, const T minor, const T patch) noexcept;

    explicit version3(const version2<T> &ver) noexcept;

    explicit version3(const version2<T> &ver, const T patch) noexcept;

    ~version3() = default;

    version3(const version3<T> &) noexcept = default;
    auto operator=(const version3<T> &) noexcept -> version3<T> & = default;

    version3(version3<T> &&) noexcept = default;
    auto operator=(version3<T> &&) noexcept -> version3<T> & = default;

    [[nodiscard]] auto str() const -> std::string;

    T patch;
};

template <typename T = int>
class version4 : public version3<T>
{
public:
    version4() noexcept;

    explicit version4(const T major, const T minor) noexcept;

    explicit version4(const T major, const T minor, const T patch) noexcept;

    explicit version4(const T major, const T minor, const T patch, const T build) noexcept;

    explicit version4(const version2<T> &ver) noexcept;

    explicit version4(const version2<T> &ver, const int patch) noexcept;

    explicit version4(const version2<T> &ver, const int patch, const int build) noexcept;

    explicit version4(const version3<T> &ver) noexcept;

    explicit version4(const version3<T> &ver, const int build) noexcept;

    ~version4() = default;

    version4(const version4<T> &) noexcept = default;
    auto operator=(const version4<T> &) noexcept -> version4<T> & = default;

    version4(version4<T> &&) noexcept = default;
    auto operator=(version4<T> &&) noexcept -> version4<T> & = default;

    [[nodiscard]] auto str() const -> std::string;

    int build;
};

template <typename T>
inline auto operator<(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator==(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<<(std::ostream &os, const version2<T> &v) -> std::ostream &;

template <typename T>
inline auto operator<(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator==(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<<(std::ostream &os, const version3<T> &v) -> std::ostream &;

template <typename T>
inline auto operator<(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator==(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<<(std::ostream &os, const version4<T> &v) -> std::ostream &;

using version = version4<int>;

} // namespace aeon::common

#include <aeon/common/impl/version_impl.h>

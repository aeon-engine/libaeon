// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <tuple>

namespace aeon::common
{

template <typename T>
inline version2<T>::version2() noexcept
    : major{}
    , minor{}
{
}

template <typename T>
inline version2<T>::version2(const T major, const T minor) noexcept
    : major{major}
    , minor{minor}
{
}

template <typename T>
inline auto version2<T>::str() const -> std::string
{
    std::string version;
    version.reserve(3); // Typically 1.2
    version += std::to_string(major);
    version += '.';
    version += std::to_string(minor);
    return version;
}

template <typename T>
inline version3<T>::version3() noexcept
    : version2<T>{}
    , patch{}
{
}

template <typename T>
inline version3<T>::version3(const T major, const T minor) noexcept
    : version3{major, minor, {}}
{
}

template <typename T>
inline version3<T>::version3(const T major, const T minor, const T patch) noexcept
    : version2<T>{major, minor}
    , patch{patch}
{
}

template <typename T>
inline version3<T>::version3(const version2<T> &ver) noexcept
    : version3{ver, {}}
{
}

template <typename T>
inline version3<T>::version3(const version2<T> &ver, const T patch) noexcept
    : version2<T>{ver}
    , patch{patch}
{
}

template <typename T>
inline auto version3<T>::str() const -> std::string
{
    std::string version;
    version.reserve(5); // Typically 1.2.3
    version += std::to_string(version2<T>::major);
    version += '.';
    version += std::to_string(version2<T>::minor);
    version += '.';
    version += std::to_string(patch);
    return version;
}

template <typename T>
inline version4<T>::version4() noexcept
    : version3<T>{}
    , build{}
{
}

template <typename T>
inline version4<T>::version4(const T major, const T minor) noexcept
    : version4{major, minor, {}, {}}
{
}

template <typename T>
inline version4<T>::version4(const T major, const T minor, const T patch) noexcept
    : version4{major, minor, patch, {}}
{
}

template <typename T>
inline version4<T>::version4(const T major, const T minor, const T patch, const T build) noexcept
    : version3<T>{major, minor, patch}
    , build{build}
{
}

template <typename T>
inline version4<T>::version4(const version2<T> &ver) noexcept
    : version3<T>{ver.major, ver.minor, {}}
    , build{}
{
}

template <typename T>
inline version4<T>::version4(const version2<T> &ver, const int patch) noexcept
    : version4{ver, patch, {}}
{
}

template <typename T>
inline version4<T>::version4(const version2<T> &ver, const int patch, const int build) noexcept
    : version3<T>{ver.major, ver.minor, patch}
    , build{build}
{
}

template <typename T>
inline version4<T>::version4(const version3<T> &ver) noexcept
    : version4{ver, {}}
{
}

template <typename T>
inline version4<T>::version4(const version3<T> &ver, const int build) noexcept
    : version3<T>{ver}
    , build{build}
{
}

template <typename T>
inline auto version4<T>::str() const -> std::string
{
    std::string version;
    version.reserve(7); // Typically 1.2.3.4
    version += std::to_string(version2<T>::major);
    version += '.';
    version += std::to_string(version2<T>::minor);
    version += '.';
    version += std::to_string(version3<T>::patch);
    version += '.';
    version += std::to_string(build);
    return version;
}

template <typename T>
inline auto operator<(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) < std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline auto operator<=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) <= std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline auto operator>(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) > std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline auto operator>=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) >= std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline auto operator==(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor;
}

template <typename T>
inline auto operator!=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<<(std::ostream &os, const version2<T> &v) -> std::ostream &
{
    return os << std::to_string(v.major) << "." << std::to_string(v.minor);
}

template <typename T>
inline auto operator<(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) < std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline auto operator<=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) <= std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline auto operator>(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) > std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline auto operator>=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) >= std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline auto operator==(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch;
}

template <typename T>
inline auto operator!=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<<(std::ostream &os, const version3<T> &v) -> std::ostream &
{
    return os << v.major << "." << v.minor << "." << v.patch;
}

template <typename T>
inline auto operator<(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) < std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline auto operator<=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) <= std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline auto operator>(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) > std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline auto operator>=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) >= std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline auto operator==(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch && lhs.build == rhs.build;
}

template <typename T>
inline auto operator!=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator<<(std::ostream &os, const version4<T> &v) -> std::ostream &
{
    return os << v.major << "." << v.minor << "." << v.patch << "." << v.build;
}

} // namespace aeon::common

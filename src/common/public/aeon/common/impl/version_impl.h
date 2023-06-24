// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <tuple>

namespace aeon::common
{

template <typename T>
inline constexpr version2<T>::version2() noexcept
    : major{}
    , minor{}
{
}

template <typename T>
inline constexpr version2<T>::version2(const T major, const T minor) noexcept
    : major{major}
    , minor{minor}
{
}

template <typename T>
template <typename U>
inline constexpr version2<T>::version2(const version2<U> other) noexcept
    : major{static_cast<T>(other.major)}
    , minor{static_cast<T>(other.minor)}
{
}

template <typename T>
template <typename U>
inline constexpr version2<T>::version2(const U major, const U minor) noexcept
    : major{static_cast<T>(major)}
    , minor{static_cast<T>(minor)}
{
}

template <typename T>
inline auto version2<T>::str() const -> string
{
    string version;
    version.reserve(3); // Typically 1.2
    version += std::to_string(major);
    version += '.';
    version += std::to_string(minor);
    return version;
}

template <typename T>
inline constexpr version3<T>::version3() noexcept
    : version2<T>{}
    , patch{}
{
}

template <typename T>
inline constexpr version3<T>::version3(const T major, const T minor) noexcept
    : version3{major, minor, {}}
{
}

template <typename T>
inline constexpr version3<T>::version3(const T major, const T minor, const T patch) noexcept
    : version2<T>{major, minor}
    , patch{patch}
{
}

template <typename T>
inline constexpr version3<T>::version3(const version2<T> &ver) noexcept
    : version3{ver, {}}
{
}

template <typename T>
inline constexpr version3<T>::version3(const version2<T> &ver, const T patch) noexcept
    : version2<T>{ver}
    , patch{patch}
{
}

template <typename T>
template <typename U>
inline constexpr version3<T>::version3(const U major, const U minor) noexcept
    : version3{static_cast<T>(major), static_cast<T>(minor), {}}
{
}

template <typename T>
template <typename U>
inline constexpr version3<T>::version3(const U major, const U minor, const U patch) noexcept
    : version2<T>{static_cast<T>(major), static_cast<T>(minor)}
    , patch{static_cast<T>(patch)}
{
}

template <typename T>
template <typename U>
inline constexpr version3<T>::version3(const version2<U> &ver) noexcept
    : version3{ver, {}}
{
}

template <typename T>
template <typename U>
inline constexpr version3<T>::version3(const version2<U> &ver, const U patch) noexcept
    : version2<T>{ver}
    , patch{static_cast<T>(patch)}
{
}

template <typename T>
template <typename U>
inline constexpr version3<T>::version3(const version3<U> &ver) noexcept
    : version3<T>{static_cast<T>(ver.major), static_cast<T>(ver.minor), static_cast<T>(ver.patch)}
{
}

template <typename T>
inline auto version3<T>::str() const -> string
{
    string version;
    version.reserve(5); // Typically 1.2.3
    version += std::to_string(version2<T>::major);
    version += '.';
    version += std::to_string(version2<T>::minor);
    version += '.';
    version += std::to_string(patch);
    return version;
}

template <typename T>
inline constexpr version4<T>::version4() noexcept
    : version3<T>{}
    , build{}
{
}

template <typename T>
inline constexpr version4<T>::version4(const T major, const T minor) noexcept
    : version4{major, minor, {}, {}}
{
}

template <typename T>
inline constexpr version4<T>::version4(const T major, const T minor, const T patch) noexcept
    : version4{major, minor, patch, {}}
{
}

template <typename T>
inline constexpr version4<T>::version4(const T major, const T minor, const T patch, const T build) noexcept
    : version3<T>{major, minor, patch}
    , build{build}
{
}

template <typename T>
inline constexpr version4<T>::version4(const version2<T> &ver) noexcept
    : version3<T>{ver.major, ver.minor, {}}
    , build{}
{
}

template <typename T>
inline constexpr version4<T>::version4(const version2<T> &ver, const T patch) noexcept
    : version4{ver, patch, {}}
{
}

template <typename T>
inline constexpr version4<T>::version4(const version2<T> &ver, const T patch, const T build) noexcept
    : version3<T>{ver.major, ver.minor, patch}
    , build{build}
{
}

template <typename T>
inline constexpr version4<T>::version4(const version3<T> &ver) noexcept
    : version4{ver, {}}
{
}

template <typename T>
inline constexpr version4<T>::version4(const version3<T> &ver, const T build) noexcept
    : version3<T>{ver}
    , build{build}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const U major, const U minor) noexcept
    : version4{static_cast<T>(major), static_cast<T>(minor), {}, {}}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const U major, const U minor, const U patch) noexcept
    : version4{static_cast<T>(major), static_cast<T>(minor), static_cast<T>(patch), {}}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const U major, const U minor, const U patch, const U build) noexcept
    : version3<T>{static_cast<T>(major), static_cast<T>(minor), static_cast<T>(patch)}
    , build{static_cast<T>(build)}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const version2<U> &ver) noexcept
    : version3<T>{static_cast<T>(ver.major), static_cast<T>(ver.minor), {}}
    , build{}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const version2<U> &ver, const U patch) noexcept
    : version4{ver, patch, {}}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const version2<U> &ver, const U patch, const U build) noexcept
    : version3<T>{static_cast<T>(ver.major), static_cast<T>(ver.minor), static_cast<T>(patch)}
    , build{static_cast<T>(build)}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const version3<U> &ver) noexcept
    : version4{ver, {}}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const version3<U> &ver, const U build) noexcept
    : version3<T>{ver}
    , build{static_cast<T>(build)}
{
}

template <typename T>
template <typename U>
inline constexpr version4<T>::version4(const version4<U> &ver) noexcept
    : version4{static_cast<T>(ver.major), static_cast<T>(ver.minor), static_cast<T>(ver.patch),
               static_cast<T>(ver.build)}
{
}

template <typename T>
inline auto version4<T>::str() const -> string
{
    string version;
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
inline constexpr auto operator<(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) < std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline constexpr auto operator<=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) <= std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline constexpr auto operator>(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) > std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline constexpr auto operator>=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor) >= std::tie(rhs.major, rhs.minor);
}

template <typename T>
inline constexpr auto operator==(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor;
}

template <typename T>
inline constexpr auto operator!=(const version2<T> &lhs, const version2<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const version2<T> &v) -> std::ostream &
{
    return os << std::to_string(v.major) << "." << std::to_string(v.minor);
}

template <typename T>
inline constexpr auto operator<(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) < std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline constexpr auto operator<=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) <= std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline constexpr auto operator>(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) > std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline constexpr auto operator>=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch) >= std::tie(rhs.major, rhs.minor, rhs.patch);
}

template <typename T>
inline constexpr auto operator==(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch;
}

template <typename T>
inline constexpr auto operator!=(const version3<T> &lhs, const version3<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const version3<T> &v) -> std::ostream &
{
    return os << v.major << "." << v.minor << "." << v.patch;
}

template <typename T>
inline constexpr auto operator<(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) < std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline constexpr auto operator<=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) <= std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline constexpr auto operator>(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) > std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline constexpr auto operator>=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return std::tie(lhs.major, lhs.minor, lhs.patch, lhs.build) >= std::tie(rhs.major, rhs.minor, rhs.patch, rhs.build);
}

template <typename T>
inline constexpr auto operator==(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return lhs.major == rhs.major && lhs.minor == rhs.minor && lhs.patch == rhs.patch && lhs.build == rhs.build;
}

template <typename T>
inline constexpr auto operator!=(const version4<T> &lhs, const version4<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline constexpr auto operator<<(std::ostream &os, const version4<T> &v) -> std::ostream &
{
    return os << v.major << "." << v.minor << "." << v.patch << "." << v.build;
}

} // namespace aeon::common

// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <algorithm>

namespace aeon::math
{

template <typename T>
inline size2d<T>::size2d() noexcept
    : width{}
    , height{}
{
}

template <typename T>
inline size2d<T>::size2d(const T width, const T height) noexcept
    : width{width}
    , height{height}
{
}

template <typename T>
template <typename U>
inline size2d<T>::size2d(const U width, const U height) noexcept
    : width{static_cast<T>(width)}
    , height{static_cast<T>(height)}
{
}

template <typename T>
template <typename U>
inline size2d<T>::size2d(const convert_type, const U &t) noexcept
    : width{static_cast<T>(t.width)}
    , height{static_cast<T>(t.height)}
{
}

template <typename T>
template <typename U>
auto size2d<T>::convert_to() const noexcept -> U
{
    return U{static_cast<decltype(U::width)>(width), static_cast<decltype(U::height)>(height)};
}

template <typename T>
[[nodiscard]] inline auto width(const size2d<T> &size) noexcept -> T
{
    return size.width;
}

template <typename T>
[[nodiscard]] inline auto height(const size2d<T> &size) noexcept -> T
{
    return size.height;
}

template <typename T>
[[nodiscard]] inline auto area(const size2d<T> &size) noexcept -> T
{
    return width(size) * height(size);
}

template <typename T>
[[nodiscard]] inline auto empty(const size2d<T> &size) noexcept -> bool
{
    return width(size) == T(0) || height(size) == T(0);
}

template <typename T>
[[nodiscard]] inline auto null(const size2d<T> &size) noexcept -> bool
{
    return width(size) == T(0) && height(size) == T(0);
}

template <typename T>
[[nodiscard]] inline auto valid(const size2d<T> &size) noexcept -> bool
{
    return width(size) >= T(0) && height(size) >= T(0);
}

template <typename T>
[[nodiscard]] inline auto rect(const size2d<T> &size) noexcept -> rectangle<T>
{
    return {0, 0, width(size), height(size)};
}

template <typename T>
[[nodiscard]] inline auto contains(const vector2<T> &vec, const size2d<T> size) noexcept -> bool
{
    return (vec.x < width(size) && vec.y < height(size));
}

template <typename T>
inline constexpr void inflate(size2d<T> &size, const T val) noexcept
{
    size = inflated(size, val);
}

template <typename T>
inline constexpr auto inflated(const size2d<T> &size, const T val) noexcept -> size2d<T>
{
    return size + val;
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const T val) noexcept
{
    size = scaled(size, val);
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const T x, const T y) noexcept
{
    size = scaled(size, x, y);
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const vector2<T> &vec) noexcept
{
    size = scaled(size, vec);
}

template <typename T>
inline constexpr void scale(size2d<T> &size, const size2d<T> &val) noexcept
{
    size = scaled(size, val);
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const T val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const T x, const T y) noexcept -> size2d<T>
{
    return scaled(size, {x, y});
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const vector2<T> &vec) noexcept -> size2d<T>
{
    return size * vec;
}

template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const size2d<T> &val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const U val) noexcept
{
    size = scaled(size, val);
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const U x, const U y) noexcept
{
    size = scaled(size, x, y);
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const vector2<U> &vec) noexcept
{
    size = scaled(size, vec);
}

template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const size2d<U> &val) noexcept
{
    size = scaled(size, val);
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const U val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const U x, const U y) noexcept -> size2d<T>
{
    return scaled(size, {x, y});
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const vector2<U> &vec) noexcept -> size2d<T>
{
    return size * vec;
}

template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const size2d<U> &val) noexcept -> size2d<T>
{
    return size * val;
}

template <typename T>
constexpr auto min(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>
{
    return {std::min(width(a), width(b)), std::min(height(a), height(b))};
}

template <typename T>
constexpr auto max(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>
{
    return {std::max(width(a), width(b)), std::max(height(a), height(b))};
}

template <typename T>
constexpr auto clamp(const size2d<T> &val, const size2d<T> &min_size, const size2d<T> &max_size) noexcept -> size2d<T>
{
    return max(min_size, min(max_size, val));
}

template <typename T>
inline auto operator==(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return width(lhs) == width(rhs) && height(lhs) == height(rhs);
}

template <typename T>
inline auto operator!=(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator+(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) + width(rhs), height(lhs) + height(rhs)};
}

template <typename T>
inline auto operator+=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) + rhs, height(lhs) + rhs};
}

template <typename T>
inline auto operator+=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) - width(rhs), height(lhs) - height(rhs)};
}

template <typename T>
inline auto operator-=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) - rhs, height(lhs) - rhs};
}

template <typename T>
inline auto operator-=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) * width(rhs), height(lhs) * height(rhs)};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>
{
    return {width(lhs) * rhs.x, height(lhs) * rhs.y};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    return {width(lhs) * rhs, height(lhs) * rhs};
}

template <typename T>
inline auto operator*=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * width(rhs)),
            static_cast<T>(static_cast<U>(height(lhs)) * height(rhs))};
}

template <typename T, typename U>
inline auto operator*=(size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs.x), static_cast<T>(static_cast<U>(height(lhs)) * rhs.y)};
}

template <typename T, typename U>
inline auto operator*=(size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs), static_cast<T>(static_cast<U>(height(lhs)) * rhs)};
}

template <typename T, typename U>
inline auto operator*=(size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

} // namespace aeon::math

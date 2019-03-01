// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/math/vector3.h>
#include <aeon/math/size2d.h>
#include <algorithm>

namespace aeon::math
{

template <typename T>
inline size3d<T>::size3d() noexcept
    : width{}
    , height{}
    , depth{}
{
}

template <typename T>
inline size3d<T>::size3d(const T width, const T height, const T depth) noexcept
    : width{width}
    , height{height}
    , depth{depth}
{
}

template <typename T>
template <typename U>
inline size3d<T>::size3d(const U width, const U height, const U depth) noexcept
    : width{static_cast<T>(width)}
    , height{static_cast<T>(height)}
    , depth{static_cast<T>(depth)}
{
}

template <typename T>
inline size3d<T>::size3d(const size2d<T> &size, const T depth) noexcept
    : width{math::width(size)}
    , height{math::height(size)}
    , depth{depth}
{
}

template <typename T>
template <typename U>
inline size3d<T>::size3d(const size2d<U> &size, const U depth) noexcept
    : width{static_cast<T>(math::width(size))}
    , height{static_cast<T>(math::height(size))}
    , depth{static_cast<T>(depth)}
{
}

template <typename T>
[[nodiscard]] inline auto width(const size3d<T> &size) noexcept -> T
{
    return size.width;
}

template <typename T>
[[nodiscard]] inline auto height(const size3d<T> &size) noexcept -> T
{
    return size.height;
}

template <typename T>
[[nodiscard]] inline auto depth(const size3d<T> &size) noexcept -> T
{
    return size.depth;
}

template <typename T>
[[nodiscard]] inline auto volume(const size3d<T> &size) noexcept -> T
{
    return width(size) * height(size) * depth(size);
}

template <typename T>
[[nodiscard]] inline auto empty(const size3d<T> &size) noexcept -> bool
{
    return width(size) == T(0) || height(size) == T(0) || depth(size) == T(0);
}

template <typename T>
[[nodiscard]] inline auto null(const size3d<T> &size) noexcept -> bool
{
    return width(size) == T(0) && height(size) == T(0) && depth(size) == T(0);
}

template <typename T>
[[nodiscard]] inline auto valid(const size3d<T> &size) noexcept -> bool
{
    return width(size) >= T(0) && height(size) >= T(0) && depth(size) >= T(0);
}

template <typename T>
[[nodiscard]] inline auto contains(const vector3<T> &vec, const size3d<T> size) noexcept -> bool
{
    return (vec.x < width(size) && vec.y < height(size) && vec.z < depth(size));
}

template <typename T>
inline constexpr void inflate(size3d<T> &size, const T val) noexcept
{
    size = inflated(size, val);
}

template <typename T>
inline constexpr auto inflated(const size3d<T> &size, const T val) noexcept -> size3d<T>
{
    return size + val;
}

template <typename T>
inline constexpr void scale(size3d<T> &size, const T val) noexcept
{
    size = scaled(size, val);
}

template <typename T>
inline constexpr void scale(size3d<T> &size, const T x, const T y, const T z) noexcept
{
    size = scaled(size, x, y, z);
}

template <typename T>
inline constexpr void scale(size3d<T> &size, const vector3<T> &vec) noexcept
{
    size = scaled(size, vec);
}

template <typename T>
inline constexpr void scale(size3d<T> &size, const size3d<T> &val) noexcept
{
    size = scaled(size, val);
}

template <typename T>
inline constexpr auto scaled(const size3d<T> &size, const T val) noexcept -> size3d<T>
{
    return size * val;
}

template <typename T>
inline constexpr auto scaled(const size3d<T> &size, const T x, const T y, const T z) noexcept -> size3d<T>
{
    return scaled(size, {x, y, z});
}

template <typename T>
inline constexpr auto scaled(const size3d<T> &size, const vector3<T> &vec) noexcept -> size3d<T>
{
    return size * vec;
}

template <typename T>
inline constexpr auto scaled(const size3d<T> &size, const size3d<T> &val) noexcept -> size3d<T>
{
    return size * val;
}

template <typename T, typename U>
inline constexpr void scale(size3d<T> &size, const U val) noexcept
{
    size = scaled(size, val);
}

template <typename T, typename U>
inline constexpr void scale(size3d<T> &size, const U x, const U y, const U z) noexcept
{
    size = scaled(size, x, y, z);
}

template <typename T, typename U>
inline constexpr void scale(size3d<T> &size, const vector3<U> &vec) noexcept
{
    size = scaled(size, vec);
}

template <typename T, typename U>
inline constexpr void scale(size3d<T> &size, const size3d<U> &val) noexcept
{
    size = scaled(size, val);
}

template <typename T, typename U>
inline constexpr auto scaled(const size3d<T> &size, const U val) noexcept -> size3d<T>
{
    return size * val;
}

template <typename T, typename U>
inline constexpr auto scaled(const size3d<T> &size, const U x, const U y, const U z) noexcept -> size3d<T>
{
    return scaled(size, {x, y, z});
}

template <typename T, typename U>
inline constexpr auto scaled(const size3d<T> &size, const vector3<U> &vec) noexcept -> size3d<T>
{
    return size * vec;
}

template <typename T, typename U>
inline constexpr auto scaled(const size3d<T> &size, const size3d<U> &val) noexcept -> size3d<T>
{
    return size * val;
}

template <typename T>
constexpr auto min(const size3d<T> &a, const size3d<T> &b) noexcept -> size3d<T>
{
    return {std::min(width(a), width(b)), std::min(height(a), height(b)), std::min(depth(a), depth(b))};
}

template <typename T>
constexpr auto max(const size3d<T> &a, const size3d<T> &b) noexcept -> size3d<T>
{
    return {std::max(width(a), width(b)), std::max(height(a), height(b)), std::max(depth(a), depth(b))};
}

template <typename T>
constexpr auto clamp(const size3d<T> &val, const size3d<T> &min_size, const size3d<T> &max_size) noexcept -> size3d<T>
{
    return max(min_size, min(max_size, val));
}

template <typename T>
inline auto operator==(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> bool
{
    return width(lhs) == width(rhs) && height(lhs) == height(rhs) && depth(lhs) == depth(rhs);
}

template <typename T>
inline auto operator!=(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

template <typename T>
inline auto operator+(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) + width(rhs), height(lhs) + height(rhs), depth(lhs) + depth(rhs)};
}

template <typename T>
inline auto operator+=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator+(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) + rhs, height(lhs) + rhs, depth(lhs) + rhs};
}

template <typename T>
inline auto operator+=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs + rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) - width(rhs), height(lhs) - height(rhs), depth(lhs) - depth(rhs)};
}

template <typename T>
inline auto operator-=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator-(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) - rhs, height(lhs) - rhs, depth(lhs) - rhs};
}

template <typename T>
inline auto operator-=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs - rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) * width(rhs), height(lhs) * height(rhs), depth(lhs) * depth(rhs)};
}

template <typename T>
inline auto operator*=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size3d<T> &lhs, const vector3<T> &rhs) noexcept -> size3d<T>
{
    return {width(lhs) * rhs.x, height(lhs) * rhs.y, depth(lhs) * rhs.z};
}

template <typename T>
inline auto operator*=(size3d<T> &lhs, const vector3<T> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T>
inline auto operator*(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    return {width(lhs) * rhs, height(lhs) * rhs, depth(lhs) * rhs};
}

template <typename T>
inline auto operator*=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size3d<T> &lhs, const size3d<U> &rhs) noexcept -> size3d<T>
{
    return {
        static_cast<T>(static_cast<U>(width(lhs)) * width(rhs)),
        static_cast<T>(static_cast<U>(height(lhs)) * height(rhs)),
        static_cast<T>(static_cast<U>(depth(lhs)) * depth(rhs)),
    };
}

template <typename T, typename U>
inline auto operator*=(size3d<T> &lhs, const size3d<U> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size3d<T> &lhs, const vector3<U> &rhs) noexcept -> size3d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs.x), static_cast<T>(static_cast<U>(height(lhs)) * rhs.y),
            static_cast<T>(static_cast<U>(depth(lhs)) * rhs.z)};
}

template <typename T, typename U>
inline auto operator*=(size3d<T> &lhs, const vector3<U> &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

template <typename T, typename U>
inline auto operator*(const size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>
{
    return {static_cast<T>(static_cast<U>(width(lhs)) * rhs), static_cast<T>(static_cast<U>(height(lhs)) * rhs),
            static_cast<T>(static_cast<U>(depth(lhs)) * rhs)};
}

template <typename T, typename U>
inline auto operator*=(size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>
{
    lhs = lhs * rhs;
    return lhs;
}

} // namespace aeon::math

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for size3d.
 */

#pragma once

#include <aeon/math/math_fwd.h>
#include <aeon/common/concepts.h>

namespace aeon::math
{

/*!
 * Class that represents a 3d size (width, height and depth).
 */
template <common::concepts::arithmetic_convertible T>
class size3d
{
public:
    /*!
     * Create an empty rectangle. This initializes all values to 0.
     */
    constexpr size3d() noexcept;

    /*!
     * Create a size based on the given width, height and depth.
     */
    constexpr size3d(const T width, const T height, const T depth) noexcept;

    /*!
     * Create a size based on the given width and height.
     * Converting constructor
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr size3d(const U width, const U height, const U depth) noexcept;

    /*!
     * Create a size based on the given width, height and depth.
     */
    constexpr size3d(const size2d<T> &size, const T depth) noexcept;

    /*!
     * Create a size based on the given width and height.
     * Converting constructor
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr size3d(const size2d<U> &size, const U depth) noexcept;

    ~size3d() noexcept = default;

    constexpr size3d(const size3d &) noexcept = default;
    constexpr auto operator=(const size3d &) noexcept -> size3d & = default;

    constexpr size3d(size3d &&) noexcept = default;
    constexpr auto operator=(size3d &&) noexcept -> size3d & = default;

    T width;
    T height;
    T depth;
};

/*!
 * Get the width value of a given size.
 * \param[in] size - Size3d
 * \return The width value
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto width(const size3d<T> &size) noexcept -> T;

/*!
 * Get the height value of a given size.
 * \param[in] size - Size3d
 * \return The height value
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto height(const size3d<T> &size) noexcept -> T;

/*!
 * Get the depth value of a given size.
 * \param[in] size - Size3d
 * \return The depth value
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto depth(const size3d<T> &size) noexcept -> T;

/*!
 * Get the volume of a given size.
 * \param[in] size - Size3d
 * \return The area (width * height)
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto volume(const size3d<T> &size) noexcept -> T;

/*!
 * Check if a size is empty (width == 0 or height == 0 or depth == 0)
 * \param[in] size - Size3d
 * \return True if the size is empty
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto empty(const size3d<T> &size) noexcept -> bool;

/*!
 * Check if a size is null (width == 0, height == 0 and depth == 0)
 * \param[in] size - Size3d
 * \return True if the size is null
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto null(const size3d<T> &size) noexcept -> bool;

/*!
 * Check if a size is valid (width >= 0, height >= 0, depth >= 0)
 * \param[in] size - Size3d
 * \return True if the size is valid
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto valid(const size3d<T> &size) noexcept -> bool;

/*!
 * Check if the given inner point is completely contained within the given size.
 * \param[in] vec - A point
 * \param[in] size - Size3d
 * \return True if the point is contained with in the size.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto contains(const vector3<T> &vec, const size3d<T> size) noexcept -> bool;

/*!
 * Inflate (grow, add) a size in all directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] val - Value to inflate with
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void inflate(size3d<T> &size, const T val) noexcept;

/*!
 * Inflate (grow, add) a size in all directions by a given value to a new copy.
 * \param[in] size - Size3d
 * \param[in] val - Value to inflate with
 * \return Inflated size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto inflated(const size3d<T> &size, const T val) noexcept -> size3d<T>;

/*!
 * Scale (multiply) a size in all directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] val - Value to scale with
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const T val) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] x - Width scale value
 * \param[in] y - Height scale value
 * \param[in] z - Depth scale value
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const T x, const T y, const T z) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] vec - Scale values
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const vector3<T> &vec) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] val - Scale values
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(size3d<T> &size, const size3d<T> &val) noexcept;

/*!
 * Scale (multiply) a size in all directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] val - Value to scale with
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const T val) noexcept -> size3d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] x - Width scale value
 * \param[in] y - Height scale value
 * \param[in] z - Depth scale value
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const T x, const T y, const T z) noexcept
    -> size3d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] vec - Scale values
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const vector3<T> &vec) noexcept -> size3d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] val - Scale values
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const size3d<T> &val) noexcept -> size3d<T>;

/*!
 * Scale (multiply) a size in all directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] val - Value to scale with
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const U val) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] x - Width scale value
 * \param[in] y - Height scale value
 * \param[in] z - Depth scale value
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const U x, const U y, const U z) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] vec - Scale values
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const vector3<U> &vec) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in,out] size - Size3d
 * \param[in] val - Scale values
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr void scale(size3d<T> &size, const size3d<U> &val) noexcept;

/*!
 * Scale (multiply) a size in all directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] val - Value to scale with
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const U val) noexcept -> size3d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] x - Width scale value
 * \param[in] y - Height scale value
 * \param[in] z - Depth scale value
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const U x, const U y, const U z) noexcept
    -> size3d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] vec - Horizontal and vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const vector3<U> &vec) noexcept -> size3d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size3d
 * \param[in] val - Horizontal and vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
[[nodiscard]] inline constexpr auto scaled(const size3d<T> &size, const size3d<U> &val) noexcept -> size3d<T>;

/*!
 * Get the minimum values from the given size3d for both width, height and depth.
 * \param[in] a - Size3d
 * \param[in] b - Size3d
 * \return The minimum values for width, height and depth.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const size3d<T> &a, const size3d<T> &b) noexcept -> size3d<T>;

/*!
 * Get the maximum values from the given size3d for both width, height and depth.
 * \param[in] a - Size3d
 * \param[in] b - Size3d
 * \return The maximum values for width, height and depth.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const size3d<T> &a, const size3d<T> &b) noexcept -> size3d<T>;

/*!
 * Clamp the values of the given width, height and depth in val to min and max.
 * \param[in] val - Size3d value
 * \param[in] min_size - Size3d minimum
 * \param[in] max_size - Size3d maximum
 * \return Clamped value between min and max.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto clamp(const size3d<T> &val, const size3d<T> &min_size,
                                          const size3d<T> &max_size) noexcept -> size3d<T>;

/*!
 * Calculates the smallest power of two that is not smaller than the given size.
 * \param[in] val - Size3d value
 */
template <std::unsigned_integral T>
inline constexpr void bit_ceil(size3d<T> &val) noexcept;

/*!
 * Calculates the smallest power of two that is not smaller than the given size.
 * \param[in] val - Size3d value
 * \return Size of the smallest power of two that is not smaller than the given size
 */
template <std::unsigned_integral T>
[[nodiscard]] inline constexpr auto bit_ceiled(const size3d<T> &val) noexcept -> size3d<T>;

/*!
 * If the size is not zero, calculates the largest integral power of two that is not greater than the given size. If the
 * size is zero, the result is also zero.
 * \param[in] val - Size3d value
 */
template <std::unsigned_integral T>
inline constexpr void bit_floor(size3d<T> &val) noexcept;

/*!
 * If the size is not zero, calculates the largest integral power of two that is not greater than the given size. If the
 * size is zero, the result is also zero.
 * \param[in] val - Size3d value
 * \return Size of the largest integral power of two that is not greater than the given size
 */
template <std::unsigned_integral T>
[[nodiscard]] inline constexpr auto bit_floored(const size3d<T> &val) noexcept -> size3d<T>;

/*!
 * Calculate rounded values of a given size
 * \param[in] val - Size3d
 * \return Rounded values of a given size
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const size3d<T> &val) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto operator==(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto operator!=(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size3d<T> &lhs, const size3d<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size3d<T> &lhs, const vector3<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size3d<T> &lhs, const vector3<T> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(size3d<T> &lhs, const T &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const size3d<T> &lhs, const size3d<U> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(size3d<T> &lhs, const size3d<U> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const size3d<T> &lhs, const vector3<U> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(size3d<T> &lhs, const vector3<U> &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(size3d<T> &lhs, const U &rhs) noexcept -> size3d<T>;

} // namespace aeon::math

#include <aeon/math/impl/size3d_impl.h>

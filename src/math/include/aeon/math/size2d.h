// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for size2d.
 */

#pragma once

#include <aeon/math/convert_type.h>
#include <aeon/math/math_fwd.h>

namespace aeon::math
{

template <typename T>
class rectangle;

/*!
 * Class that represents a size (width and height).
 */
template <typename T>
class size2d
{
public:
    /*!
     * Create an empty rectangle. This initializes all values to 0.
     */
    constexpr size2d() noexcept;

    /*!
     * Create a size based on the given width and height.
     */
    constexpr size2d(const T width, const T height) noexcept;

    /*!
     * Create a size based on the given width and height.
     * Converting constructor
     */
    template <typename U>
    explicit constexpr size2d(const size2d<U> size) noexcept;

    /*!
     * Create a size based on the given width and height.
     * Converting constructor
     */
    template <typename U>
    explicit constexpr size2d(const U width, const U height) noexcept;

    template <typename U>
    explicit constexpr size2d(const convert_type, const U &t) noexcept;

    ~size2d() noexcept = default;

    constexpr size2d(const size2d &) noexcept = default;
    constexpr auto operator=(const size2d &) noexcept -> size2d & = default;

    constexpr size2d(size2d &&) noexcept = default;
    constexpr auto operator=(size2d &&) noexcept -> size2d & = default;

    template <typename U>
    [[nodiscard]] constexpr auto convert_to() const noexcept -> U;

    T width;
    T height;
};

/*!
 * Get the width value of a given size.
 * \param[in] size - Size2d
 * \return The width value
 */
template <typename T>
[[nodiscard]] inline constexpr auto width(const size2d<T> &size) noexcept -> T;

/*!
 * Get the height value of a given size.
 * \param[in] size - Size2d
 * \return The height value
 */
template <typename T>
[[nodiscard]] inline constexpr auto height(const size2d<T> &size) noexcept -> T;

/*!
 * Get the area of a given size.
 * \param[in] size - Size2d
 * \return The area (width * height)
 */
template <typename T>
[[nodiscard]] inline constexpr auto area(const size2d<T> &size) noexcept -> T;

/*!
 * Check if a size is empty (width == 0 or height == 0)
 * \param[in] size - Size2d
 * \return True if the size is empty
 */
template <typename T>
[[nodiscard]] inline constexpr auto empty(const size2d<T> &size) noexcept -> bool;

/*!
 * Check if a size is null (width == 0 and height == 0)
 * \param[in] size - Size2d
 * \return True if the size is null
 */
template <typename T>
[[nodiscard]] inline constexpr auto null(const size2d<T> &size) noexcept -> bool;

/*!
 * Check if a size is valid (width >= 0 and height >= 0)
 * \param[in] size - Size2d
 * \return True if the size is valid
 */
template <typename T>
[[nodiscard]] inline constexpr auto valid(const size2d<T> &size) noexcept -> bool;

/*!
 * Get the rectangle for a given size with left-top at [0, 0].
 * \param[in] size - Size2d
 * \return Rectangle
 */
template <typename T>
[[nodiscard]] inline constexpr auto rect(const size2d<T> &size) noexcept -> rectangle<T>;

/*!
 * Check if the given inner point is completely contained within the given size.
 * \param[in] vec - A point
 * \param[in] size - Size2d
 * \return True if the point is contained with in the size.
 */
template <typename T>
[[nodiscard]] inline constexpr auto contains(const vector2<T> &vec, const size2d<T> size) noexcept -> bool;

/*!
 * Inflate (grow, add) a size in all directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] val - Value to inflate with
 */
template <typename T>
inline constexpr void inflate(size2d<T> &size, const T val) noexcept;

/*!
 * Inflate (grow, add) a size in all directions by a given value to a new copy.
 * \param[in] size - Size2d
 * \param[in] val - Value to inflate with
 * \return Inflated size copy based on the given one.
 */
template <typename T>
inline constexpr auto inflated(const size2d<T> &size, const T val) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] val - Value to scale with
 */
template <typename T>
inline constexpr void scale(size2d<T> &size, const T val) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 */
template <typename T>
inline constexpr void scale(size2d<T> &size, const T x, const T y) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] vec - Horizontal and vertical scale value
 */
template <typename T>
inline constexpr void scale(size2d<T> &size, const vector2<T> &vec) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] val - Horizontal and vertical scale value
 */
template <typename T>
inline constexpr void scale(size2d<T> &size, const size2d<T> &val) noexcept;

/*!
 * Scale (multiply) a size in all directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] val - Value to scale with
 * \return A scaled size copy based on the given one.
 */
template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const T val) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const T x, const T y) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] vec - Horizontal and vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const vector2<T> &vec) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] val - Horizontal and vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <typename T>
inline constexpr auto scaled(const size2d<T> &size, const size2d<T> &val) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] val - Value to scale with
 */
template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const U val) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 */
template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const U x, const U y) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] vec - Horizontal and vertical scale value
 */
template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const vector2<U> &vec) noexcept;

/*!
 * Scale (multiply) a size in all two directions by a given value.
 * \param[in, out] size - Size2d
 * \param[in] val - Horizontal and vertical scale value
 */
template <typename T, typename U>
inline constexpr void scale(size2d<T> &size, const size2d<U> &val) noexcept;

/*!
 * Scale (multiply) a size in all directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] val - Value to scale with
 * \return A scaled size copy based on the given one.
 */
template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const U val) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const U x, const U y) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] vec - Horizontal and vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const vector2<U> &vec) noexcept -> size2d<T>;

/*!
 * Scale (multiply) a size in all two directions by a given value to a copy.
 * \param[in] size - Size2d
 * \param[in] val - Horizontal and vertical scale value
 * \return A scaled size copy based on the given one.
 */
template <typename T, typename U>
inline constexpr auto scaled(const size2d<T> &size, const size2d<U> &val) noexcept -> size2d<T>;

/*!
 * Get the minimum values from the given size2d for both width and height.
 * \param[in] a - Size2d
 * \param[in] b - Size2d
 * \return The minimum values for width and height.
 */
template <typename T>
inline constexpr auto min(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>;

/*!
 * Get the maximum values from the given size2d for both width and height.
 * \param[in] a - Size2d
 * \param[in] b - Size2d
 * \return The maximum values for width and height.
 */
template <typename T>
inline constexpr auto max(const size2d<T> &a, const size2d<T> &b) noexcept -> size2d<T>;

/*!
 * Clamp the values of the given width and height in val to min and max.
 * \param[in] val - Size2d value
 * \param[in] min_size - Size2d minimum
 * \param[in] max_size - Size2d maximum
 * \return Clamped value between min and max.
 */
template <typename T>
inline constexpr auto clamp(const size2d<T> &val, const size2d<T> &min_size, const size2d<T> &max_size) noexcept
    -> size2d<T>;

/*!
 * Returns the aspect ratio of the given size (width / height).
 * \param[in] val - Size2d value
 * \return Float aspect ratio (width / height)
 */
template <typename T>
inline constexpr auto ratio(const size2d<T> &val) noexcept -> float;

template <typename T>
inline constexpr auto operator==(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator+(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator+=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator+(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator+=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator-(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator-=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator-(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator-=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator*(const size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator*=(size2d<T> &lhs, const size2d<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator*(const size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator*=(size2d<T> &lhs, const vector2<T> &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator*(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator*=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator/(const size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T>
inline constexpr auto operator/=(size2d<T> &lhs, const T &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator*(const size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator*=(size2d<T> &lhs, const size2d<U> &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator*(const size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator*=(size2d<T> &lhs, const vector2<U> &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator*(const size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator*=(size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator/(const size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>;

template <typename T, typename U>
inline constexpr auto operator/=(size2d<T> &lhs, const U &rhs) noexcept -> size2d<T>;

} // namespace aeon::math

#include <aeon/math/impl/size2d_impl.h>

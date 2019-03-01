// Copyright (c) 2012-2019 Robin Degen

/*!
 * \file
 * \brief Mathmatical operations for a rectangle.
 */

#pragma once

#include <aeon/math/anchor_point.h>
#include <aeon/math/math_fwd.h>
#include <type_traits>
#include <tuple>

namespace aeon::math
{

template <typename T>
class size2d;

/*!
 * Class that represents an equiangular rectangle (left, top, right and bottom)
 */
template <typename T>
class rectangle
{
public:
    /*!
     * Create an empty rectangle. This initializes all values to 0.
     */
    constexpr rectangle() noexcept;

    /*!
     * Create a rectangle based on the given values.
     */
    constexpr rectangle(const T left, const T top, const T right, const T bottom) noexcept;

    /*!
     * Create a rectangle based on the given values.
     * \param[in] left_top - The coordinates of the left-top corner of the rectangle
     * \param[in] right_bottom - The coordinates of the right-bottom corner of the rectangle
     */
    constexpr rectangle(const vector2<T> left_top, const vector2<T> right_bottom) noexcept;

    /*!
     * Create a rectangle based on the given values.
     * \param[in] left - The left value
     * \param[in] top - The top value
     * \param[in] size - The size of the rectangle (right=left+width, bottom=top+height)
     */
    constexpr rectangle(const T left, const T top, const size2d<T> size) noexcept;

    /*!
     * Create a rectangle based on the given values.
     * \param[in] left_top - The coordinates of the left-top corner of the rectangle
     * \param[in] size - The size of the rectangle (right=left+width, bottom=top+height)
     */
    constexpr rectangle(const vector2<T> left_top, const size2d<T> size) noexcept;

    /*!
     * Create a rectangle based on the given values.
     * \note
     * \param[in] position - The coordinates of an anchor point within the rectangle.
     * \param[in] size - The size of the rectangle. The size of the rectangle is guaranteed.
     *                   This means that for example a given anchor point in the middle, may
     *                   actually be off-center for even sized rectangles.
     * \param[in] anchor - Anchor point for the given position
     * \see anchor_point
     */
    constexpr rectangle(const vector2<T> position, const size2d<T> size, const anchor_point anchor) noexcept;

    ~rectangle() noexcept = default;

    constexpr rectangle(const rectangle<T> &) noexcept = default;
    constexpr auto operator=(const rectangle<T> &) noexcept -> rectangle<T> & = default;

    constexpr rectangle(rectangle<T> &&) noexcept = default;
    constexpr auto operator=(rectangle<T> &&) noexcept -> rectangle<T> & = default;

    T left;
    T top;
    T right;
    T bottom;
};

/*!
 * Get the left value of a given rectangle.
 * \param[in] rect - Rectangle
 * \return The left value
 */
template <typename T>
[[nodiscard]] inline constexpr auto left(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the top value of a given rectangle.
 * \param[in] rect - Rectangle
 * \return The top value
 */
template <typename T>
[[nodiscard]] inline constexpr auto top(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the right value of a given rectangle.
 * \param[in] rect - Rectangle
 * \return The right value
 */
template <typename T>
[[nodiscard]] inline constexpr auto right(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the bottom value of a given rectangle.
 * \param[in] rect - Rectangle
 * \return The bottom value
 */
template <typename T>
[[nodiscard]] inline constexpr auto bottom(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the width of a given rectangle.
 * \param[in] rect - Rectangle
 * \return The width (right-left)
 */
template <typename T>
[[nodiscard]] inline constexpr auto width(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the height of a given rectangle.
 * \param[in] rect - Rectangle
 * \return The height (bottom-top)
 */
template <typename T>
[[nodiscard]] inline constexpr auto height(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the left-top coordinate of a given rectangle
 * \param[in] rect - Rectangle
 * \return Left-top coordinates
 */
template <typename T>
[[nodiscard]] inline constexpr auto left_top(const rectangle<T> &rect) noexcept -> vector2<T>;

/*!
 * Get the right-top coordinate of a given rectangle
 * \param[in] rect - Rectangle
 * \return Right-top coordinates
 */
template <typename T>
[[nodiscard]] inline constexpr auto right_top(const rectangle<T> &rect) noexcept -> vector2<T>;

/*!
 * Get the left-bottom coordinate of a given rectangle
 * \param[in] rect - Rectangle
 * \return Left-bottom coordinates
 */
template <typename T>
[[nodiscard]] inline constexpr auto left_bottom(const rectangle<T> &rect) noexcept -> vector2<T>;

/*!
 * Get the right-bottom coordinate of a given rectangle
 * \param[in] rect - Rectangle
 * \return Right-bottom coordinates
 */
template <typename T>
[[nodiscard]] inline constexpr auto right_bottom(const rectangle<T> &rect) noexcept -> vector2<T>;

/*!
 * Get the center coordinate of a given rectangle.
 * \note This point may not be exactly in the center for int type rectangles with an even value size.
 * \param[in] rect - Rectangle
 * \return Center coordinates
 */
template <typename T>
[[nodiscard]] inline constexpr auto center(const rectangle<T> &rect) noexcept -> vector2<T>;

/*!
 * Check if a rectangle is empty (left == right or top == bottom)
 * \param[in] rect - Rectangle
 * \return True if the rectangle is empty
 */
template <typename T>
[[nodiscard]] inline constexpr auto empty(const rectangle<T> &rect) noexcept -> bool;

/*!
 * Check if a rectangle is null (left == right and top == bottom)
 * \param[in] rect - Rectangle
 * \return True if the rectangle is null
 */
template <typename T>
[[nodiscard]] inline constexpr auto null(const rectangle<T> &rect) noexcept -> bool;

/*!
 * Check if a rectangle is valid (left < right and top < bottom)
 * \param[in] rect - Rectangle
 * \return True if the rectangle is valid
 */
template <typename T>
[[nodiscard]] inline constexpr auto valid(const rectangle<T> &rect) noexcept -> bool;

/*!
 * Get the size of a rectangle
 * \param[in] rect - Rectangle
 * \return The size of the rectangle (width, height)
 */
template <typename T>
[[nodiscard]] inline constexpr auto size(const rectangle<T> &rect) noexcept -> size2d<T>;

/*!
 * Translate (move) an existing rectangle.
 * \param[in, out] rect - Rectangle
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 */
template <typename T>
inline constexpr void translate(rectangle<T> &rect, const T x, const T y) noexcept;

/*!
 * Translate (move) an existing rectangle.
 * \param[in, out] rect - Rectangle
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 */
template <typename T, typename U>
inline constexpr void translate(rectangle<T> &rect, const U x, const U y) noexcept;

/*!
 * Translate (move) an existing rectangle.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - Relative X and Y coordinates.
 */
template <typename T>
inline constexpr void translate(rectangle<T> &rect, const vector2<T> &vec) noexcept;

/*!
 * Translate (move) an existing rectangle.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - Relative X and Y coordinates.
 */
template <typename T, typename U>
inline constexpr void translate(rectangle<T> &rect, const vector2<U> &vec) noexcept;

/*!
 * Translate (move) a rectangle to a new copy
 * \param[in] rect - Rectangle
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \return A new rectangle moved with the given offset
 */
template <typename T>
[[nodiscard]] inline constexpr auto translated(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

/*!
 * Translate (move) a rectangle to a new copy
 * \param[in] rect - Rectangle
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \return A new rectangle moved with the given offset
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto translated(const rectangle<T> &rect, const U x, const U y) noexcept -> rectangle<T>;

/*!
 * Translate (move) a rectangle to a new copy
 * \param[in] rect - Rectangle
 * \param[in] vec - Relative X and Y coordinates.
 * \return A new rectangle moved with the given offset
 */
template <typename T>
[[nodiscard]] inline constexpr auto translated(const rectangle<T> &rect, const vector2<T> &vec) noexcept
    -> rectangle<T>;

/*!
 * Translate (move) a rectangle to a new copy
 * \param[in] rect - Rectangle
 * \param[in] vec - Relative X and Y coordinates.
 * \return A new rectangle moved with the given offset
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto translated(const rectangle<T> &rect, const vector2<U> &vec) noexcept
    -> rectangle<T>;

/*!
 * Set the position of an existing rectangle.
 * \param[in, out] rect - Rectangle
 * \param[in] x - New X coordinate of the left-top.
 * \param[in] y - New Y coordinate of the left-top.
 */
template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const T x, const T y) noexcept;

/*!
 * Set the position of an existing rectangle.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - New X and Y coordinates of the left-top.
 */
template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const vector2<T> &vec) noexcept;

/*!
 * Set the position of an existing rectangle. The given coordinate
 * \param[in, out] rect - Rectangle
 * \param[in] x - New X coordinate of an anchor point within the rectangle.
 * \param[in] y - New Y coordinate of an anchor point within the rectangle.
 * \param[in] anchor - Anchor point for the given position
 */
template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const T x, const T y, const anchor_point anchor) noexcept;

/*!
 * Set the position of an existing rectangle. The given coordinate
 * \param[in, out] rect - Rectangle
 * \param[in] vec - New X and Y coordinates of an anchor point within the rectangle.
 * \param[in] anchor - Anchor point for the given position
 */
template <typename T>
inline constexpr void set_position(rectangle<T> &rect, const vector2<T> &vec, const anchor_point anchor) noexcept;

/*!
 * Set the position of a rectangle to a new copy.
 * \param[in] rect - Rectangle
 * \param[in] x - New X coordinate of the left-top.
 * \param[in] y - New Y coordinate of the left-top.
 * \return A moved copy of the given rectangle.
 */
template <typename T>
[[nodiscard]] inline constexpr auto positioned(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

/*!
 * Set the position of a rectangle to a new copy.
 * \param[in] rect - Rectangle
 * \param[in] vec - New X and Y coordinates of the left-top.
 * \return A moved copy of the given rectangle.
 */
template <typename T>
[[nodiscard]] inline constexpr auto positioned(const rectangle<T> &rect, const vector2<T> &vec) noexcept
    -> rectangle<T>;

/*!
 * Set the position of a rectangle to a new copy.
 * \param[in] rect - Rectangle
 * \param[in] x - New X coordinate of an anchor point within the rectangle.
 * \param[in] y - New Y coordinate of an anchor point within the rectangle.
 * \param[in] anchor - Anchor point for the given position
 * \return A moved copy of the given rectangle.
 */
template <typename T>
[[nodiscard]] inline constexpr auto positioned(const rectangle<T> &rect, const T x, const T y,
                                               const anchor_point anchor) noexcept -> rectangle<T>;

/*!
 * Set the position of a rectangle to a new copy.
 * \param[in] rect - Rectangle
 * \param[in] vec - New X and Y coordinate of an anchor point within the rectangle.
 * \param[in] anchor - Anchor point for the given position
 * \return A moved copy of the given rectangle.
 */
template <typename T>
[[nodiscard]] inline constexpr auto positioned(const rectangle<T> &rect, const vector2<T> &vec,
                                               const anchor_point anchor) noexcept -> rectangle<T>;

/*!
 * Check if the given inner rectangle is completely contained within the given outer rectangle.
 * \param[in] inner - Inner rectangle
 * \param[in] outer - Outer rectangle
 * \return True if the inner rectangle is completely contained with in the outer rectangle.
 */
template <typename T>
[[nodiscard]] inline constexpr auto contains(const rectangle<T> &inner, const rectangle<T> &outer) noexcept -> bool;

/*!
 * Check if the given inner point is completely contained within the given rectangle.
 * \param[in] vec - A point
 * \param[in] rect - Rectangle
 * \return True if the point is contained with in the rectangle.
 */
template <typename T>
[[nodiscard]] inline constexpr auto contains(const vector2<T> &vec, const rectangle<T> &rect) noexcept -> bool;

/*!
 * Check if the given rectangles overlap each other.
 * \param[in] rect1 - Rectangle
 * \param[in] rect2 - Rectangle
 * \return True if the given rectangles overlap each other.
 */
template <typename T>
[[nodiscard]] inline constexpr auto overlaps(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> bool;

/*!
 * Get the intersection of two given rectangles (the area where the 2 rectangles overlap).
 * \param[in] rect1 - Rectangle
 * \param[in] rect2 - Rectangle
 * \return Intersection rectangle
 */
template <typename T>
[[nodiscard]] inline constexpr auto intersection(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept
    -> rectangle<T>;

/*!
 * Get the bounding box (or union) out of a list of given rectangles.
 * \param[in] first - Rectangle
 * \param[in] rectangles - One or more rectangles. Must have the same type as first.
 * \return Bounding box/union of all given rectangles.
 */
template <typename T, typename... U>
[[nodiscard]] inline constexpr auto bounding_box(const rectangle<T> &first, const rectangle<U> &... rectangles) noexcept
    -> rectangle<T>;

/*!
 * Inflate (grow, add) a rectangle in all directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] val - Value to inflate with
 */
template <typename T>
inline constexpr void inflate(rectangle<T> &rect, const T val) noexcept;

/*!
 * Inflate (grow, add) a rectangle in all directions by a given value to a new copy.
 * \param[in] rect - Rectangle
 * \param[in] val - Value to inflate with
 * \return Inflated rectangle copy based on the given one.
 */
template <typename T>
[[nodiscard]] inline constexpr auto inflated(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] val - Value to scale with
 */
template <typename T>
inline constexpr void scale(rectangle<T> &rect, const T val) noexcept;

/*!
 * Scale (multiply) a rectangle in all directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] val - Value to scale with
 */
template <typename T, typename U>
inline constexpr void scale(rectangle<T> &rect, const U val) noexcept;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 */
template <typename T>
inline constexpr void scale(rectangle<T> &rect, const T x, const T y) noexcept;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 */
template <typename T, typename U>
inline constexpr void scale(rectangle<T> &rect, const U x, const U y) noexcept;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - Horizontal and vertical scale value
 */
template <typename T>
inline constexpr void scale(rectangle<T> &rect, const vector2<T> &vec) noexcept;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - Horizontal and vertical scale value
 */
template <typename T, typename U>
inline constexpr void scale(rectangle<T> &rect, const vector2<U> &vec) noexcept;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] size - Horizontal and vertical scale value
 */
template <typename T>
inline constexpr void scale(rectangle<T> &rect, const size2d<T> &size) noexcept;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value.
 * \param[in, out] rect - Rectangle
 * \param[in] size - Horizontal and vertical scale value
 */
template <typename T, typename U>
inline constexpr void scale(rectangle<T> &rect, const size2d<U> &size) noexcept;

/*!
 * Scale (multiply) a rectangle in all directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] val - Value to scale with
 * \return Scaled rectangle based on given one.
 */
template <typename T>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const T val) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] val - Value to scale with
 * \return Scaled rectangle based on given one.
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const U val) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 * \return Scaled rectangle based on given one.
 */
template <typename T>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const T x, const T y) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] x - Horizontal scale value
 * \param[in] y - Vertical scale value
 * \return Scaled rectangle based on given one.
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const U x, const U y) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - Horizontal and vertical scale value
 * \return Scaled rectangle based on given one.
 */
template <typename T>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] vec - Horizontal and vertical scale value
 * \return Scaled rectangle based on given one.
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const vector2<U> &vec) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] size - Horizontal and vertical scale value
 * \return Scaled rectangle based on given one.
 */
template <typename T>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const size2d<T> &size) noexcept -> rectangle<T>;

/*!
 * Scale (multiply) a rectangle in all two directions by a given value to a new copy.
 * \param[in, out] rect - Rectangle
 * \param[in] size - Horizontal and vertical scale value
 * \return Scaled rectangle based on given one.
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto scaled(const rectangle<T> &rect, const size2d<U> &size) noexcept -> rectangle<T>;

/*!
 * Get the distance between the centers of 2 rectangles.
 * \param[in] rect1 - Rectangle
 * \param[in] rect2 - Rectangle
 * \return The distance between the centers of 2 rectangles.
 */
template <typename T>
[[nodiscard]] inline constexpr auto distance(const rectangle<T> &rect1, const rectangle<T> &rect2) noexcept -> T;

/*!
 * Get the distance between the center of a rectangle and a point.
 * \param[in] rect - Rectangle
 * \param[in] vec - Point
 * \return The distance between the center of a rectangle and a point.
 */
template <typename T>
[[nodiscard]] inline constexpr auto distance(const rectangle<T> &rect, const vector2<T> &vec) noexcept -> T;

/*!
 * Get the area of a given rectangle (width * height)
 * \param[in] rect - Rectangle
 * \return The area
 */
template <typename T>
[[nodiscard]] inline constexpr auto area(const rectangle<T> &rect) noexcept -> T;

/*!
 * Get the closest point on a given rectangle for a given point.
 * A point on a rectangle can be equal to left-top, left-bottom, right-top and right-bottom.
 * \param[in] rect - Rectangle
 * \param[in] vec - A point
 * \return Coordinates of a point on the rectangle closest to the given point.
 */
template <typename T>
[[nodiscard]] inline constexpr auto closest_point(const rectangle<T> &rect, const vector2<T> &vec) noexcept
    -> vector2<T>;

/*!
 * Normalize a rectangle (make sure that left < right and top < bottom)
 * \param[in, out] rect - Rectangle
 */
template <typename T>
inline constexpr void normalize(rectangle<T> &rect) noexcept;

/*!
 * Normalize a rectangle (make sure that left < right and top < bottom) to a copy
 * \param[in] rect - Rectangle
 * \return Normalized rectangle
 */
template <typename T>
[[nodiscard]] inline constexpr auto normalized(const rectangle<T> &rect) noexcept -> rectangle<T>;

/*!
 * Slice a rectangle horizontally (X-axis) on a given ratio (between 0.0 - 1.0)
 * \param[in] rect - Rectangle
 * \param[in] ratio - A ratio between 0.0 and 1.0
 * \return Tuple of the 2 sliced rectangles.
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto
    slice_horizontal(const rectangle<T> &rect, const U ratio,
                     typename std::enable_if<std::is_floating_point_v<U>>::type *dummy = nullptr) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

/*!
 * Slice a rectangle horizontally (X-axis) on a given value (must be >= top and <= bottom)
 * \param[in] rect - Rectangle
 * \param[in] value - Coordinate on X-axis on where to slice (must be >= top and <= bottom)
 * \return Tuple of the 2 sliced rectangles.
 */
template <typename T>
[[nodiscard]] inline constexpr auto slice_horizontal_absolute(const rectangle<T> &rect, const T value) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

/*!
 * Slice a rectangle vertically (Y-axis) on a given ratio (between 0.0 - 1.0)
 * \param[in] rect - Rectangle
 * \param[in] ratio - A ratio between 0.0 and 1.0
 * \return Tuple of the 2 sliced rectangles.
 */
template <typename T, typename U>
[[nodiscard]] inline constexpr auto
    slice_vertical(const rectangle<T> &rect, const U ratio,
                   typename std::enable_if<std::is_floating_point_v<U>>::type *dummy = nullptr) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

/*!
 * Slice a rectangle vertically (Y-axis) on a given value (must be >= left and <= right)
 * \param[in] rect - Rectangle
 * \param[in] value - Coordinate on Y-axis on where to slice (must be >= left and <= right)
 * \return Tuple of the 2 sliced rectangles.
 */
template <typename T>
[[nodiscard]] inline constexpr auto slice_vertical_absolute(const rectangle<T> &rect, const T value) noexcept
    -> std::tuple<rectangle<T>, rectangle<T>>;

template <typename T>
inline constexpr auto operator==(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator!=(const rectangle<T> &lhs, const rectangle<T> &rhs) noexcept -> bool;

template <typename T>
inline constexpr auto operator+(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator+=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator+(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator+=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator-=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*(const rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*=(rectangle<T> &lhs, const T &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*(const rectangle<T> &lhs, const size2d<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*=(rectangle<T> &lhs, const size2d<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*(const rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

template <typename T>
inline constexpr auto operator*=(rectangle<T> &lhs, const vector2<T> &rhs) noexcept -> rectangle<T>;

} // namespace aeon::math

#include <aeon/math/impl/rectangle_impl.h>

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for a 2D circle.
 */

#pragma once

#include <aeon/math/math_fwd.h>
#include <aeon/math/vector2.h>
#include <aeon/common/concepts.h>

namespace aeon::math
{

/*!
 * Class that represents a circle as a position (center) and a radius.
 */
template <common::concepts::arithmetic_convertible T>
class circle
{
public:
    /*!
     * Create a circle at position 0, 0 with a given radius.
     * \param[in] radius - Radius
     */
    explicit constexpr circle(const T radius) noexcept;

    /*!
     * Create a circle at position x, y with a given radius.
     * \param[in] x - X position
     * \param[in] y - Y position
     * \param[in] radius - Radius
     */
    constexpr circle(const T x, const T y, const T radius) noexcept;

    /*!
     * Create a circle at position x, y with a given radius.
     * \param[in] position - Position
     * \param[in] radius - Radius
     */
    constexpr circle(const vector2<T> position, const T radius) noexcept;

    ~circle() noexcept = default;

    constexpr circle(const circle &) noexcept = default;
    constexpr auto operator=(const circle &) noexcept -> circle & = default;

    constexpr circle(circle &&) noexcept = default;
    constexpr auto operator=(circle &&) noexcept -> circle & = default;

    vector2<T> position;
    T radius;
};

/*!
 * Get the center position of a circle as a point.
 * \param[in] c - Circle
 * \return position
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto position(const circle<T> &c) noexcept -> vector2<T>;

/*!
 * Get the center position of a circle as a point.
 * \param[in] c - Circle
 * \return position
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto center(const circle<T> &c) noexcept -> vector2<T>;

/*!
 * Returns if a circle is empty or not. A circle is considered empty if the radius is 0.
 * \param[in] c - Circle
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto empty(const circle<T> &c) noexcept -> bool;

/*!
 * Returns if a circle is empty or not. A circle is considered null if the radius is 0.
 * \param[in] c - Circle
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto null(const circle<T> &c) noexcept -> bool;

/*!
 * Returns if a circle is valid. A circle is considered valid if the radius is positive (>= 0).
 * \param[in] c - Circle
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto valid(const circle<T> &c) noexcept -> bool;

/*!
 * Returns the dimensions of a circle.
 * \param[in] c - Circle
 * \return The dimensions of a circle (from the left edge to the right, and top to bottom; or diameter).
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto dimensions(const circle<T> &c) noexcept -> size2d<T>;

/*!
 * Returns the radius of a circle.
 * \param[in] c - Circle
 * \return Radius
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto radius(const circle<T> &c) noexcept -> T;

/*!
 * Returns the squared radius of a circle (radius ^ 2).
 * \param[in] c - Circle
 * \return Radius&sup2;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto radius_squared(const circle<T> &c) noexcept -> T;

/*!
 * Returns the diameter of a circle.
 * \param[in] c - Circle
 * \return Diameter
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto diameter(const circle<T> &c) noexcept -> T;

/*!
 * Returns the circumference of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Circumference
 */
template <common::concepts::arithmetic_convertible T, std::enable_if_t<!std::is_floating_point_v<T>> * = nullptr>
[[nodiscard]] inline constexpr auto circumference(const circle<T> &c) noexcept -> float;

/*!
 * Returns the circumference of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Circumference
 */
template <common::concepts::arithmetic_convertible T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
[[nodiscard]] inline constexpr auto circumference(const circle<T> &c) noexcept -> T;

/*!
 * Returns the area of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Area
 */
template <common::concepts::arithmetic_convertible T, std::enable_if_t<!std::is_floating_point_v<T>> * = nullptr>
[[nodiscard]] inline constexpr auto area(const circle<T> &c) noexcept -> float;

/*!
 * Returns the area of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Area
 */
template <common::concepts::arithmetic_convertible T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
[[nodiscard]] inline constexpr auto area(const circle<T> &c) noexcept -> T;

/*!
 * Change the position of the center of the given circle.
 * \param[in,out] c - Circle to move
 * \param[in] x - X position
 * \param[in] y - Y position
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(circle<T> &c, const T x, const T y) noexcept;

/*!
 * Change the position of the center of the given circle.
 * \param[in,out] c - Circle to move
 * \param[in] vec - Position
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void set_position(circle<T> &c, const vector2<T> &vec) noexcept;

/*!
 * Change the position of the center of a circle. The returned value is a copy of the given circle.
 * \param[in] c - Circle to move
 * \param[in] x - X position
 * \param[in] y - Y position
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto positioned(const circle<T> &c, const T x, const T y) noexcept -> circle<T>;

/*!
 * Change the position of the center of a circle. The returned value is a copy of the given circle.
 * \param[in] c - Circle to move
 * \param[in] vec - Position
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto positioned(const circle<T> &c, const vector2<T> &vec) noexcept -> circle<T>;

/*!
 * Inflate a circle (add a value to the radius)
 * \param[in,out] c - Circle to inflate
 * \param[in] val - How much to inflate the radius by
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void inflate(circle<T> &c, const T val) noexcept;

/*!
 * Inflate a circle (add a value to the radius). The returned value is a copy of the given circle.
 * \param[in] c - Circle to inflate
 * \param[in] val - How much to inflate the radius by
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto inflated(const circle<T> &c, const T val) noexcept -> circle<T>;

/*!
 * Scale a circle (multiply the radius with a value)
 * \param[in,out] c - Circle to scale
 * \param[in] val - How much to scale the radius by
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void scale(circle<T> &c, const T val) noexcept;

/*!
 * Scale a circle (multiply the radius with a value). The returned value is a copy of the given circle.
 * \param[in] c - Circle to scale
 * \param[in] val - How much to scale the radius by
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto scaled(const circle<T> &c, const T val) noexcept -> circle<T>;

/*!
 * Get the bounding box rectangle for a circle.
 * \param[in] c - Circle
 * \return An axis-aligned rectangle that fits exactly around the circle.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rect(const circle<T> &c) noexcept -> rectangle<T>;

/*!
 * Get the distance between the centers of 2 circles.
 * \param[in] lhs - Circle
 * \param[in] rhs - Circle
 * \return The distance between the center of 2 circles.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const circle<T> &lhs, const circle<T> &rhs) noexcept -> T;

/*!
 * Get the distance between the center of a circle and a point.
 * \param[in] lhs - Circle
 * \param[in] rhs - Point
 * \return The distance between the center of a circle and a point.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const circle<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Check if a point is within a given circle.
 * \param[in] c - Circle
 * \param[in] vec - Point
 * \return Boolean. True if the given point is within the circle.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto contains(const circle<T> &c, const vector2<T> &vec) noexcept -> bool;

/*!
 * Check if a rectangle overlaps with a circle (ie. collides)
 * \param[in] c - Circle
 * \param[in] rect - Rectangle
 * \return Boolean. True if the given rectangle overlaps with the circle.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto overlaps(const circle<T> &c, const rectangle<T> &rect) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator!=(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/circle_impl.h>

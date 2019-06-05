// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

/*!
 * \file
 * \brief Mathmatical operations for a 2D circle.
 */

#pragma once

#include <aeon/math/vector2.h>
#include <type_traits>

namespace aeon::math
{

template <typename T>
class size2d;

template <typename T>
class rectangle;

/*!
 * Class that represents a circle as a position (center) and a radius.
 */
template <typename T>
class circle
{
public:
    /*!
     * Create a circle at position 0, 0 with a given radius.
     * \param[in] radius - Radius
     */
    explicit circle(const T radius) noexcept;

    /*!
     * Create a circle at position x, y with a given radius.
     * \param[in] x - X position
     * \param[in] y - Y position
     * \param[in] radius - Radius
     */
    circle(const T x, const T y, const T radius) noexcept;

    /*!
     * Create a circle at position x, y with a given radius.
     * \param[in] position - Position
     * \param[in] radius - Radius
     */
    circle(const vector2<T> position, const T radius) noexcept;

    ~circle() noexcept = default;

    circle(const circle &) noexcept = default;
    auto operator=(const circle &) noexcept -> circle & = default;

    circle(circle &&) noexcept = default;
    auto operator=(circle &&) noexcept -> circle & = default;

    vector2<T> position;
    T radius;
};

/*!
 * Get the center position of a circle as a point.
 * \param[in] c - Circle
 * \return position
 */
template <typename T>
[[nodiscard]] inline auto position(const circle<T> &c) noexcept -> vector2<T>;

/*!
 * Get the center position of a circle as a point.
 * \param[in] c - Circle
 * \return position
 */
template <typename T>
[[nodiscard]] inline auto center(const circle<T> &c) noexcept -> vector2<T>;

/*!
 * Returns if a circle is empty or not. A circle is considered empty if the radius is 0.
 * \param[in] c - Circle
 */
template <typename T>
[[nodiscard]] inline auto empty(const circle<T> &c) noexcept -> bool;

/*!
 * Returns if a circle is empty or not. A circle is considered null if the radius is 0.
 * \param[in] c - Circle
 */
template <typename T>
[[nodiscard]] inline auto null(const circle<T> &c) noexcept -> bool;

/*!
 * Returns if a circle is valid. A circle is considered valid if the radius is positive (>= 0).
 * \param[in] c - Circle
 */
template <typename T>
[[nodiscard]] inline auto valid(const circle<T> &c) noexcept -> bool;

/*!
 * Returns the size of a circle.
 * \param[in] c - Circle
 * \return The size of a circle (from the left edge to the right, and top to bottom; or diameter).
 */
template <typename T>
[[nodiscard]] inline auto size(const circle<T> &c) noexcept -> size2d<T>;

/*!
 * Returns the radius of a circle.
 * \param[in] c - Circle
 * \return Radius
 */
template <typename T>
[[nodiscard]] inline auto radius(const circle<T> &c) noexcept -> T;

/*!
 * Returns the squared radius of a circle (radius ^ 2).
 * \param[in] c - Circle
 * \return Radius&sup2;
 */
template <typename T>
[[nodiscard]] inline auto radius_squared(const circle<T> &c) noexcept -> T;

/*!
 * Returns the diameter of a circle.
 * \param[in] c - Circle
 * \return Diameter
 */
template <typename T>
[[nodiscard]] inline auto diameter(const circle<T> &c) noexcept -> T;

/*!
 * Returns the circumference of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Circumference
 */
template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type * = nullptr>
[[nodiscard]] inline auto circumference(const circle<T> &c) noexcept -> float;

/*!
 * Returns the circumference of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Circumference
 */
template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type * = nullptr>
[[nodiscard]] inline auto circumference(const circle<T> &c) noexcept -> T;

/*!
 * Returns the area of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Area
 */
template <typename T, typename std::enable_if<!std::is_floating_point_v<T>>::type * = nullptr>
[[nodiscard]] inline auto area(const circle<T> &c) noexcept -> float;

/*!
 * Returns the area of a circle. If T=int, the type of the returned value is float,
 * otherwise the returned value type is T.
 * \param[in] c - Circle
 * \return Area
 */
template <typename T, typename std::enable_if<std::is_floating_point_v<T>>::type * = nullptr>
[[nodiscard]] inline auto area(const circle<T> &c) noexcept -> T;

/*!
 * Change the position of the center of the given circle.
 * \param[in, out] c - Circle to move
 * \param[in] x - X position
 * \param[in] y - Y position
 */
template <typename T>
inline void set_position(circle<T> &c, const T x, const T y) noexcept;

/*!
 * Change the position of the center of the given circle.
 * \param[in, out] c - Circle to move
 * \param[in] vec - Position
 */
template <typename T>
inline void set_position(circle<T> &c, const vector2<T> &vec) noexcept;

/*!
 * Change the position of the center of a circle. The returned value is a copy of the given circle.
 * \param[in] c - Circle to move
 * \param[in] x - X position
 * \param[in] y - Y position
 */
template <typename T>
[[nodiscard]] inline auto positioned(const circle<T> &c, const T x, const T y) noexcept -> circle<T>;

/*!
 * Change the position of the center of a circle. The returned value is a copy of the given circle.
 * \param[in] c - Circle to move
 * \param[in] vec - Position
 */
template <typename T>
[[nodiscard]] inline auto positioned(const circle<T> &c, const vector2<T> &vec) noexcept -> circle<T>;

/*!
 * Inflate a circle (add a value to the radius)
 * \param[in, out] c - Circle to inflate
 * \param[in] val - How much to inflate the radius by
 */
template <typename T>
inline void inflate(circle<T> &c, const T val) noexcept;

/*!
 * Inflate a circle (add a value to the radius). The returned value is a copy of the given circle.
 * \param[in] c - Circle to inflate
 * \param[in] val - How much to inflate the radius by
 */
template <typename T>
[[nodiscard]] inline auto inflated(const circle<T> &c, const T val) noexcept -> circle<T>;

/*!
 * Scale a circle (multiply the radius with a value)
 * \param[in, out] c - Circle to scale
 * \param[in] val - How much to scale the radius by
 */
template <typename T>
inline void scale(circle<T> &c, const T val) noexcept;

/*!
 * Scale a circle (multiply the radius with a value). The returned value is a copy of the given circle.
 * \param[in] c - Circle to scale
 * \param[in] val - How much to scale the radius by
 */
template <typename T>
[[nodiscard]] inline auto scaled(const circle<T> &c, const T val) noexcept -> circle<T>;

/*!
 * Get the bounding box rectangle for a circle.
 * \param[in] c - Circle
 * \return An axis-aligned rectangle that fits exactly around the circle.
 */
template <typename T>
[[nodiscard]] inline auto rect(const circle<T> &c) noexcept -> rectangle<T>;

/*!
 * Get the distance between the centers of 2 circles.
 * \param[in] lhs - Circle
 * \param[in] rhs - Circle
 * \return The distance between the center of 2 circles.
 */
template <typename T>
[[nodiscard]] inline auto distance(const circle<T> &lhs, const circle<T> &rhs) noexcept -> T;

/*!
 * Get the distance between the center of a circle and a point.
 * \param[in] lhs - Circle
 * \param[in] rhs - Point
 * \return The distance between the center of a circle and a point.
 */
template <typename T>
[[nodiscard]] inline auto distance(const circle<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Check if a point is within a given circle.
 * \param[in] c - Circle
 * \param[in] vec - Point
 * \return Boolean. True if the given point is within the circle.
 */
template <typename T>
[[nodiscard]] inline auto contains(const circle<T> &c, const vector2<T> &vec) noexcept -> bool;

/*!
 * Check if a rectangle overlaps with a circle (ie. collides)
 * \param[in] c - Circle
 * \param[in] rect - Rectangle
 * \return Boolean. True if the given rectangle overlaps with the circle.
 */
template <typename T>
[[nodiscard]] inline auto overlaps(const circle<T> &c, const rectangle<T> &rect) noexcept -> bool;

template <typename T>
inline auto operator==(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const circle<T> &lhs, const circle<T> &rhs) noexcept -> bool;

} // namespace aeon::math

#include <aeon/math/impl/circle_impl.h>

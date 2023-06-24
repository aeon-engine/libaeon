// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for vector2.
 */

#pragma once

#include <aeon/math/units.h>
#include <aeon/math/winding_order.h>
#include <aeon/common/concepts.h>
#include <cstddef>
#include <compare>

namespace aeon::math
{

/*!
 * Class that represents a 2D vector.
 */
template <common::concepts::arithmetic_convertible T>
class vector2
{
public:
    /*!
     * Create an empty vector. This initializes all values to 0.
     */
    constexpr vector2() noexcept;

    /*!
     * Create a vector. Both X and Y will be initialized to the given value.
     */
    explicit constexpr vector2(const T xy) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    constexpr vector2(const T x, const T y) noexcept;

    /*!
     * Create a vector based on the given values. Converting constructor.
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr vector2(const U x, const U y) noexcept;

    /*!
     * Create a vector based on the given vector. Converting constructor.
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr vector2(const vector2<U> &vec) noexcept;

    /*!
     * Create a vector based on the given array values (index 0 is X, 1 is Y)
     */
    explicit constexpr vector2(const T xy[2]) noexcept;

    ~vector2() noexcept = default;

    constexpr vector2(const vector2<T> &) noexcept = default;
    constexpr auto operator=(const vector2<T> &) noexcept -> vector2<T> & = default;

    constexpr vector2(vector2<T> &&) noexcept = default;
    constexpr auto operator=(vector2<T> &&) noexcept -> vector2<T> & = default;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y)
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) noexcept -> T &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y)
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) const noexcept -> const T &;

    /*!
     * Create an empty vector (all values are 0).
     */
    [[nodiscard]] static constexpr auto zero() noexcept -> vector2<T>;

    /*!
     * Change the values of an existing vector.
     */
    constexpr void set(const T new_x, const T new_y) noexcept;

    T x;
    T y;
};

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector2<T> &vec) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const T lhs, const vector2<U> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const vector2<T> &lhs, const U rhs) noexcept -> vector2<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(vector2<T> &lhs, const vector2<U> &rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(vector2<T> &lhs, const U rhs) noexcept -> vector2<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator<=>(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> std::strong_ordering;

/*!
 * Translate (move) an existing vector.
 * \param[in,out] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector2<T> &lhs, const T x, const T y) noexcept;

/*!
 * Translate (move) an existing vector.
 * \param[in,out] lhs - Vector
 * \param[in] rhs - Relative X and Y coordinates
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector2<T> &lhs, const vector2<T> &rhs) noexcept;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \return A new vector moved with the given offset
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector2<T> &lhs, const T x, const T y) noexcept -> vector2<T>;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] rhs - Relative X and Y coordinates.
 * \return A new vector moved with the given offset
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate the sum of each component (X+Y) for a given vector
 * \param[in] vec - Vector
 * \return The sum of each component (X+Y);
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sum(const vector2<T> &vec) noexcept -> T;

/*!
 * Calculate the dot product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Dot product
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto dot(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the cross product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Cross product
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cross(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the length of a given vector.
 * \param[in] vec - Vector
 * \return Vector length
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto length(const vector2<T> &vec) noexcept -> T;

/*!
 * Calculate the length of a given vector as a squared value to avoid having to do a square root.
 * \param[in] vec - Vector
 * \return Vector length&sup2;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_length(const vector2<T> &vec) noexcept -> T;

/*!
 * Normalize a given directional vector (so that length = 1)
 * \param[in,out] vec - Vector
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void normalize(vector2<T> &vec) noexcept;

/*!
 * Normalize a given directional vector (so that length = 1) to a new copy
 * \param[in] vec - Vector
 * \return Normalized vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normalized(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Determine the lowest value component (min(x, y))
 * \param[in] vec - Vector
 * \return The lowest value component
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const vector2<T> &vec) noexcept -> T;

/*!
 * Determine the highest value component (max(x, y))
 * \param[in] vec - Vector
 * \return The highest value component
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const vector2<T> &vec) noexcept -> T;

/*!
 * Calculate the sine values of a given vector.
 * \param[in] vec - Vector
 * \return Sine values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sin(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Cosine values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cos(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Tangent values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto tan(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc sine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc since values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto asin(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc cosine values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto acos(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Arc tangent values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto atan(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc tangent values of a given vector y/x values.
 * \param[in] vec - Vector
 * \return Arc tangent value of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto atan2(const vector2<T> &vec) noexcept -> T;

/*!
 * Calculate the absolute values of a given vector.
 * \param[in] vec - Vector
 * \return Absolute values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto abs(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the squared distance between 2 given vector points. This avoids having to do a square root.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance&sup2;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the absolute distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Vector with the absolute distances for each component;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto absolute_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept
    -> vector2<T>;

/*!
 * Calculate the manhattan distance ("taxicab geometry") between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Manhattan distance
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto manhattan_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the Chebyshev distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Chebyshev distance
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto chebyshev_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate middle point between two given points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Middle point
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto midpoint(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate floor for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Floor from 2 given vectors
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate floor values of a given vector
 * \param[in] vec - Vector
 * \return Floored values of a given vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate ceil for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Ceil from 2 given vectors
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate ceil values of a given vector
 * \param[in] vec - Vector
 * \return Ceiled values of a given vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate rounded values of a given vector
 * \param[in] vec - Vector
 * \return Rounded values of a given vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the angle of the vector in radians
 * \param[in] vec - Vector
 * \return The angle of the vector in radians
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto angle(const vector2<T> &vec) -> T;

/*!
 * Rotate a point counterclockwise around a center point by a given angle
 * \param[in] vec - The point to rotate
 * \param[in] angle - The angle to rotate by
 * \param[in] center - The center point to rotate the point around
 * \return The rotated point
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_by(const vector2<T> &vec, const unitf<radian> angle,
                                              const vector2<T> &center = {}) noexcept -> vector2<T>;

/*!
 * Interpolate between the given vectors with a ratio
 * \param[in] val1 - Vector (result at 0.0 ratio)
 * \param[in] val2 - Vector (result at 1.0 ratio)
 * \param[in] ratio - A ratio between 0.0 and 1.0
 * \return Interpolated vector
 */
template <common::concepts::arithmetic_convertible T, std::floating_point U>
[[nodiscard]] inline constexpr auto interpolate(const vector2<T> &val1, const vector2<T> &val2, const U ratio) noexcept
    -> vector2<T>;

/*!
 * Determine the winding order of three given vectors. If the given vectors are colinear, the behavior is undefined.
 * \param[in] vec1 - Vector
 * \param[in] vec2 - Vector
 * \param[in] vec3 - Vector
 * \return The winding order of the 3 given vectors
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto winding(const vector2<T> &vec1, const vector2<T> &vec2,
                                            const vector2<T> &vec3) noexcept -> winding_order;

/*!
 * Get a pointer into the underlying data structure of a given vector.
 * The vector data layout is [X Y]
 * \param[in] vec - Vector
 * \return Pointer to vector data.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(vector2<T> &vec) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given vector.
 * The vector data layout is [X Y]
 * \param[in] vec - Vector
 * \return Const pointer to vector data.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(const vector2<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector2_impl.h>
#include <aeon/math/impl/vector2_operators_impl.h>

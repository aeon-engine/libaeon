// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for vector3.
 */

#pragma once

#include <aeon/math/math_fwd.h>
#include <aeon/common/concepts.h>
#include <cstddef>
#include <compare>

namespace aeon::math
{

/*!
 * Class that represents a 3D vector.
 */
template <common::concepts::arithmetic_convertible T>
class vector3
{
public:
    /*!
     * Create an empty vector. This initializes all values to 0.
     */
    constexpr vector3() noexcept;

    /*!
     * Create a vector. Both X, Y and Z will be initialized to the given value.
     */
    explicit constexpr vector3(const T xyz) noexcept;

    /*!
     * Create a vector based on the given values. Z will be initialized to 0.
     */
    constexpr vector3(const T x, const T y) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    constexpr vector3(const T x, const T y, const T z) noexcept;

    /*!
     * Create a vector based on the given values. Converting constructor.
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr vector3(const U x, const U y) noexcept;

    /*!
     * Create a vector based on the given vector. Converting constructor.
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr vector3(const vector3<U> &vec) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    template <common::concepts::arithmetic_convertible U>
    explicit constexpr vector3(const U x, const U y, const U z) noexcept;

    /*!
     * Create a vector based on the given 2D vector. Z will be initialized to 0.
     */
    explicit constexpr vector3(const vector2<T> vec) noexcept;

    /*!
     * Create a vector based on the given 2D vector and Z value.
     */
    explicit constexpr vector3(const vector2<T> vec, const T z) noexcept;

    /*!
     * Create a vector based on the given array values (index 0 is X, 1 is Y, and 2 is Z)
     */
    explicit constexpr vector3(const T xyz[3]) noexcept;

    ~vector3() noexcept = default;

    constexpr vector3(const vector3<T> &) noexcept = default;
    constexpr auto operator=(const vector3<T> &) noexcept -> vector3<T> & = default;

    constexpr vector3(vector3<T> &&) noexcept = default;
    constexpr auto operator=(vector3<T> &&) noexcept -> vector3<T> & = default;

    constexpr auto operator=(const vector2<T> &vec) noexcept -> vector3<T> &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y, and 2 is Z)
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) noexcept -> T &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y, and 2 is Z)
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) const noexcept -> const T &;

    /*!
     * Create an empty vector (all values are 0).
     */
    [[nodiscard]] static constexpr auto zero() noexcept -> vector3<T>;

    /*!
     * Change the values of an existing vector.
     */
    constexpr void set(const T new_x, const T new_y, const T new_z) noexcept;

    T x;
    T y;
    T z;
};

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-(const vector3<T> &vec) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator+=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator-=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator*=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator/=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator*=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T, common::concepts::arithmetic_convertible U>
inline constexpr auto operator/=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator==(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool;

template <common::concepts::arithmetic_convertible T>
inline constexpr auto operator<=>(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> std::strong_ordering;

/*!
 * Translate (move) an existing vector.
 * \param[in,out] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \param[in] z - Relative Z coordinate
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector3<T> &lhs, const T x, const T y, const T z) noexcept;

/*!
 * Translate (move) an existing vector.
 * \param[in,out] lhs - Vector
 * \param[in] rhs - Relative X, Y and Z coordinates
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void translate(vector3<T> &lhs, const vector3<T> &rhs) noexcept;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \param[in] z - Relative Z coordinate
 * \return A new vector moved with the given offset
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector3<T> &lhs, const T x, const T y, const T z) noexcept
    -> vector3<T>;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] rhs - Relative X, Y and Z coordinates.
 * \return A new vector moved with the given offset
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto translated(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate the sum of each component (X+Y+Z) for a given vector
 * \param[in] vec - Vector
 * \return The sum of each component (X+Y+Z);
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sum(const vector3<T> &vec) noexcept -> T;

/*!
 * Calculate the dot product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Dot product
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto dot(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate the cross product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Cross product
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cross(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate the length of a given vector.
 * \param[in] vec - Vector
 * \return Vector length
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto length(const vector3<T> &vec) noexcept -> T;

/*!
 * Calculate the length of a given vector as a squared value to avoid having to do a square root.
 * \param[in] vec - Vector
 * \return Vector length&sup2;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_length(const vector3<T> &vec) noexcept -> T;

/*!
 * Normalize a given directional vector (so that length = 1)
 * \param[in,out] vec - Vector
 */
template <common::concepts::arithmetic_convertible T>
inline constexpr void normalize(vector3<T> &vec) noexcept;

/*!
 * Normalize a given directional vector (so that length = 1) to a new copy
 * \param[in] vec - Vector
 * \return Normalized vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto normalized(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Determine the lowest value component (min(x, y, z))
 * \param[in] vec - Vector
 * \return The lowest value component
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto min(const vector3<T> &vec) noexcept -> T;

/*!
 * Determine the highest value component (max(x, y, z))
 * \param[in] vec - Vector
 * \return The highest value component
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto max(const vector3<T> &vec) noexcept -> T;

/*!
 * Calculate the sine values of a given vector.
 * \param[in] vec - Vector
 * \return Sine values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto sin(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Cosine values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto cos(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Tangent values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto tan(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the arc sine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc since values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto asin(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the arc cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc cosine values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto acos(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the arc tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Arc tangent values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto atan(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the absolute values of a given vector.
 * \param[in] vec - Vector
 * \return Absolute values of the given vector.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto abs(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate the squared distance between 2 given vector points. This avoids having to do a square root.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance&sup2;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto squared_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate the absolute distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Vector with the absolute distances for each component;
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto absolute_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept
    -> vector3<T>;

/*!
 * Calculate the manhattan distance ("taxicab geometry") between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Manhattan distance
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto manhattan_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate the Chebyshev distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Chebyshev distance
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto chebyshev_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate middle point between two given points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Middle point
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto midpoint(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate floor for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Floor from 2 given vectors
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate floor values of a given vector
 * \param[in] vec - Vector
 * \return Floored values of a given vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto floor(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate ceil for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Ceil from 2 given vectors
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate ceil values of a given vector
 * \param[in] vec - Vector
 * \return Ceiled values of a given vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ceil(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate rounded values of a given vector
 * \param[in] vec - Vector
 * \return Rounded values of a given vector
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto round(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Rotate a point over the X, Y axis counterclockwise around a center point by a given angle
 * \param[in] vec - The point to rotate
 * \param[in] angle - The angle to rotate by
 * \param[in] center - The center point to rotate the point around
 * \return The rotated point
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_xy_by(const vector3<T> &vec, const unitf<radian> angle,
                                                 const vector3<T> &center = {}) noexcept -> vector3<T>;

/*!
 * Rotate a point over the X, Z axis counterclockwise around a center point by a given angle
 * \param[in] vec - The point to rotate
 * \param[in] angle - The angle to rotate by
 * \param[in] center - The center point to rotate the point around
 * \return The rotated point
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_xz_by(const vector3<T> &vec, const unitf<radian> angle,
                                                 const vector3<T> &center = {}) noexcept -> vector3<T>;

/*!
 * Rotate a point over the Y, Z axis counterclockwise around a center point by a given angle
 * \param[in] vec - The point to rotate
 * \param[in] angle - The angle to rotate by
 * \param[in] center - The center point to rotate the point around
 * \return The rotated point
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto rotate_yz_by(const vector3<T> &vec, const unitf<radian> angle,
                                                 const vector3<T> &center = {}) noexcept -> vector3<T>;

/*!
 * Get a pointer into the underlying data structure of a given vector.
 * The vector data layout is [X Y Z]
 * \param[in] vec - Vector
 * \return Pointer to vector data.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(vector3<T> &vec) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given vector.
 * The vector data layout is [X Y Z]
 * \param[in] vec - Vector
 * \return Const pointer to vector data.
 */
template <common::concepts::arithmetic_convertible T>
[[nodiscard]] inline constexpr auto ptr(const vector3<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector3_impl.h>
#include <aeon/math/impl/vector3_operators_impl.h>

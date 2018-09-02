/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
 * \file
 * \brief Mathmatical operations for vector3.
 */

#pragma once

#include <cstddef>

namespace aeon::math
{

template <typename T>
class vector2;

/*!
 * Class that represents a 3D vector.
 */
template <typename T>
class vector3
{
public:
    /*!
     * Create an empty vector. This initializes all values to 0.
     */
    vector3() noexcept;

    /*!
     * Create a vector. Both X, Y and Z will be initialized to the given value.
     */
    explicit vector3(const T xyz) noexcept;

    /*!
     * Create a vector based on the given values. Z will be initialized to 0.
     */
    vector3(const T x, const T y) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    vector3(const T x, const T y, const T z) noexcept;

    /*!
     * Create a vector based on the given values. Converting constructor.
     */
    template <typename U>
    explicit vector3(const U x, const U y) noexcept;

    /*!
     * Create a vector based on the given vector. Converting constructor.
     */
    template <typename U>
    explicit vector3(const vector3<U> &vec) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    template <typename U>
    explicit vector3(const U x, const U y, const U z) noexcept;

    /*!
     * Create a vector based on the given 2D vector. Z will be initialized to 0.
     */
    explicit vector3(const vector2<T> vec) noexcept;

    /*!
     * Create a vector based on the given 2D vector and Z value.
     */
    explicit vector3(const vector2<T> vec, const T z) noexcept;

    /*!
     * Create a vector based on the given array values (index 0 is X, 1 is Y, and 2 is Z)
     */
    explicit vector3(const T xyz[3]) noexcept;

    ~vector3() noexcept = default;

    vector3(const vector3<T> &) noexcept = default;
    auto operator=(const vector3<T> &) noexcept -> vector3<T> & = default;

    vector3(vector3<T> &&) noexcept = default;
    auto operator=(vector3<T> &&) noexcept -> vector3<T> & = default;

    auto operator=(const vector2<T> &vec) noexcept -> vector3<T> &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y, and 2 is Z)
     */
    auto operator[](const std::size_t i) noexcept -> T &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y, and 2 is Z)
     */
    auto operator[](const std::size_t i) const noexcept -> const T &;

    /*!
     * Create an empty vector (all values are 0).
     */
    static auto zero() noexcept -> vector3<T>;

    /*!
     * Change the values of an existing vector.
     */
    void set(const T new_x, const T new_y, const T new_z) noexcept;

    union {
        struct
        {
            T x;
            T y;
            T z;
        };
        T value[3];
    };
};

template <typename T>
inline auto operator+(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator+(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator+(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator-(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator-(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator-(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator-(const vector3<T> &vec) noexcept -> vector3<T>;

template <typename T>
inline auto operator*(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator*(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator*(const T lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator/(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator/(const vector3<T> &lhs, const T rhs) noexcept -> vector3<T>;

template <typename T, typename U>
inline auto operator*(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>;

template <typename T, typename U>
inline auto operator*(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>;

template <typename T, typename U>
inline auto operator/(const vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T>;

template <typename T, typename U>
inline auto operator/(const vector3<T> &lhs, const U rhs) noexcept -> vector3<T>;

template <typename T>
inline auto operator+=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator+=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator-=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator-=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator*=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator*=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator/=(vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator/=(vector3<T> &lhs, const T rhs) noexcept -> vector3<T> &;

template <typename T, typename U>
inline auto operator*=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &;

template <typename T, typename U>
inline auto operator*=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &;

template <typename T, typename U>
inline auto operator/=(vector3<T> &lhs, const vector3<U> &rhs) noexcept -> vector3<T> &;

template <typename T, typename U>
inline auto operator/=(vector3<T> &lhs, const U rhs) noexcept -> vector3<T> &;

template <typename T>
inline auto operator==(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> bool;

/*!
 * Translate (move) an existing vector.
 * \param[in, out] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \param[in] z - Relative Z coordinate
 */
template <typename T>
inline void translate(vector3<T> &lhs, const T x, const T y, const T z) noexcept;

/*!
 * Translate (move) an existing vector.
 * \param[in, out] lhs - Vector
 * \param[in] rhs - Relative X, Y and Z coordinates
 */
template <typename T>
inline void translate(vector3<T> &lhs, const vector3<T> &rhs) noexcept;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \param[in] z - Relative Z coordinate
 * \return A new vector moved with the given offset
 */
template <typename T>
inline auto translated(const vector3<T> &lhs, const T x, const T y, const T z) noexcept -> vector3<T>;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] rhs - Relative X, Y and Z coordinates.
 * \return A new vector moved with the given offset
 */
template <typename T>
inline auto translated(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate the dot product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Dot product
 */
template <typename T>
inline auto dot(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate the cross product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Cross product
 */
template <typename T>
inline auto cross(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate the length of a given vector.
 * \param[in] vec - Vector
 * \return Vector length
 */
template <typename T>
inline auto length(const vector3<T> &vec) noexcept -> T;

/*!
 * Calculate the length of a given vector as a squared value to avoid having to do a square root.
 * \param[in] vec - Vector
 * \return Vector length&sup2;
 */
template <typename T>
inline auto squared_length(const vector3<T> &vec) noexcept -> T;

/*!
 * Normalize a given directional vector (so that length = 1)
 * \param[in, out] vec - Vector
 */
template <typename T>
inline void normalize(vector3<T> &vec) noexcept;

/*!
 * Normalize a given directional vector (so that length = 1) to a new copy
 * \param[in] vec - Vector
 * \return Normalized vector
 */
template <typename T>
inline auto normalized(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the sine values of a given vector.
 * \param[in] vec - Vector
 * \return Sine values of the given vector.
 */
template <typename T>
inline auto sin(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Cosine values of the given vector.
 */
template <typename T>
inline auto cos(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Tangent values of the given vector.
 */
template <typename T>
inline auto tan(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the arc sine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc since values of the given vector.
 */
template <typename T>
inline auto asin(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the arc cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc cosine values of the given vector.
 */
template <typename T>
inline auto acos(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the arc tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Arc tangent values of the given vector.
 */
template <typename T>
inline auto atan(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the absolute values of a given vector.
 * \param[in] vec - Vector
 * \return Absolute values of the given vector.
 */
template <typename T>
inline auto abs(const vector3<T> &vec) noexcept -> vector3<T>;

/*!
 * Calculate the distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance
 */
template <typename T>
inline auto distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate the squared distance between 2 given vector points. This avoids having to do a square root.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance&sup2;
 */
template <typename T>
inline auto squared_distance(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> T;

/*!
 * Calculate middle point between two given points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Middle point
 */
template <typename T>
inline auto midpoint(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate floor for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Floor from 2 given vectors
 */
template <typename T>
inline auto floor(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Calculate ceil for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Ceil from 2 given vectors
 */
template <typename T>
inline auto ceil(const vector3<T> &lhs, const vector3<T> &rhs) noexcept -> vector3<T>;

/*!
 * Get a pointer into the underlaying data structure of a given vector.
 * The vector data layout is [X Y Z]
 * \param[in] vec - Vector
 * \return Pointer to vector data.
 */
template <typename T>
inline auto ptr(vector3<T> &vec) noexcept -> T *;

/*!
 * Get a pointer into the underlaying data structure of a given vector.
 * The vector data layout is [X Y Z]
 * \param[in] vec - Vector
 * \return Const pointer to vector data.
 */
template <typename T>
inline auto ptr(const vector3<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector3_impl.h>
#include <aeon/math/impl/vector3_operators_impl.h>

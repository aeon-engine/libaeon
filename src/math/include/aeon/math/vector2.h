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
 * \brief Mathmatical operations for vector2.
 */

#pragma once

#include <cstddef>

namespace aeon::math
{

/*!
 * Class that represents a 2D vector.
 */
template <typename T>
class vector2
{
public:
    /*!
     * Create an empty vector. This initializes all values to 0.
     */
    vector2() noexcept;

    /*!
     * Create a vector. Both X and Y will be initialized to the given value.
     */
    explicit vector2(const T xy) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    vector2(const T x, const T y) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    template <typename U>
    explicit vector2(const U x, const U y) noexcept;

    /*!
     * Create a vector based on the given array values (index 0 is X, 1 is Y)
     */
    explicit vector2(const T xy[2]) noexcept;

    ~vector2() noexcept = default;

    vector2(const vector2<T> &) noexcept = default;
    auto operator=(const vector2<T> &) noexcept -> vector2<T> & = default;

    vector2(vector2<T> &&) noexcept = default;
    auto operator=(vector2<T> &&) noexcept -> vector2<T> & = default;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y)
     */
    auto operator[](const std::size_t i) noexcept -> T &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y)
     */
    auto operator[](const std::size_t i) const noexcept -> const T &;

    /*!
     * Create an empty vector (all values are 0).
     */
    static auto zero() noexcept -> vector2<T>;

    /*!
     * Change the values of an existing vector.
     */
    void set(const T new_x, const T new_y) noexcept;

    union {
        struct
        {
            T x;
            T y;
        };
        T value[2];
    };
};

template <typename T>
inline auto operator+(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator+(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator+(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator-(const vector2<T> &vec) noexcept -> vector2<T>;

template <typename T>
inline auto operator*(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator*(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator*(const T lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator/(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator/(const vector2<T> &lhs, const T rhs) noexcept -> vector2<T>;

template <typename T>
inline auto operator+=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator+=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator+=(T &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator-=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator-=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator-=(T &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator*=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator*=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator*=(T &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator/=(vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator/=(vector2<T> &lhs, const T rhs) noexcept -> vector2<T> &;

template <typename T>
inline auto operator==(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> bool;

/*!
 * Translate (move) an existing vector.
 * \param[in, out] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 */
template <typename T>
inline void translate(vector2<T> &lhs, const T x, const T y) noexcept;

/*!
 * Translate (move) an existing vector.
 * \param[in, out] lhs - Vector
 * \param[in] rhs - Relative X and Y coordinates
 */
template <typename T>
inline void translate(vector2<T> &lhs, const vector2<T> &rhs) noexcept;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \return A new vector moved with the given offset
 */
template <typename T>
inline auto translated(const vector2<T> &lhs, const T x, const T y) noexcept -> vector2<T>;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] rhs - Relative X and Y coordinates.
 * \return A new vector moved with the given offset
 */
template <typename T>
inline auto translated(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate the dot product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Dot product
 */
template <typename T>
inline auto dot(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the cross product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Cross product
 */
template <typename T>
inline auto cross(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the length of a given vector.
 * \param[in] vec - Vector
 * \return Vector length
 */
template <typename T>
inline auto length(const vector2<T> &vec) noexcept -> T;

/*!
 * Calculate the length of a given vector as a squared value to avoid having to do a square root.
 * \param[in] vec - Vector
 * \return Vector length&sup2;
 */
template <typename T>
inline auto squared_length(const vector2<T> &vec) noexcept -> T;

/*!
 * Normalize a given directional vector (so that length = 1)
 * \param[in, out] vec - Vector
 */
template <typename T>
inline void normalize(vector2<T> &vec) noexcept;

/*!
 * Normalize a given directional vector (so that length = 1) to a new copy
 * \param[in] vec - Vector
 * \return Normalized vector
 */
template <typename T>
inline auto normalized(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the sine values of a given vector.
 * \param[in] vec - Vector
 * \return Sine values of the given vector.
 */
template <typename T>
inline auto sin(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Cosine values of the given vector.
 */
template <typename T>
inline auto cos(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Tangent values of the given vector.
 */
template <typename T>
inline auto tan(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc sine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc since values of the given vector.
 */
template <typename T>
inline auto asin(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc cosine values of the given vector.
 */
template <typename T>
inline auto acos(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Arc tangent values of the given vector.
 */
template <typename T>
inline auto atan(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the arc tangent values of a given vector y/x values.
 * \param[in] vec - Vector
 * \return Arc tangent value of the given vector.
 */
template <typename T>
inline auto atan2(const vector2<T> &vec) noexcept -> T;

/*!
 * Calculate the absolute values of a given vector.
 * \param[in] vec - Vector
 * \return Absolute values of the given vector.
 */
template <typename T>
inline auto abs(const vector2<T> &vec) noexcept -> vector2<T>;

/*!
 * Calculate the distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance
 */
template <typename T>
inline auto distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate the squared distance between 2 given vector points. This avoids having to do a square root.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance&sup2;
 */
template <typename T>
inline auto squared_distance(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> T;

/*!
 * Calculate middle point between two given points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Middle point
 */
template <typename T>
inline auto midpoint(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate floor for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Floor from 2 given vectors
 */
template <typename T>
inline auto floor(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Calculate ceil for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Ceil from 2 given vectors
 */
template <typename T>
inline auto ceil(const vector2<T> &lhs, const vector2<T> &rhs) noexcept -> vector2<T>;

/*!
 * Get a pointer into the underlaying data structure of a given vector.
 * The vector data layout is [X Y]
 * \param[in] vec - Vector
 * \return Pointer to vector data.
 */
template <typename T>
inline auto ptr(vector2<T> &vec) noexcept -> T *;

/*!
 * Get a pointer into the underlaying data structure of a given vector.
 * The vector data layout is [X Y]
 * \param[in] vec - Vector
 * \return Const pointer to vector data.
 */
template <typename T>
inline auto ptr(const vector2<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector2_impl.h>
#include <aeon/math/impl/vector2_operators_impl.h>

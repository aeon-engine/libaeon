// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for vector3.
 */

#pragma once

#include <cstddef>

namespace aeon::math
{

template <typename T>
class vector2;

template <typename T>
class vector3;

/*!
 * Class that represents a 4D vector.
 *
 * The class is 16-bytes aligned to allow for SIMD optimizations (data layout [X Y Z W]).
 */
template <typename T>
class alignas(16) vector4
{
public:
    /*!
     * Create an empty vector. This initializes all values to 0.
     */
    vector4() noexcept;

    /*!
     * Create a vector. Both X, Y, Z and W will be initialized to the given value.
     */
    explicit vector4(const T xyzw) noexcept;

    /*!
     * Create a vector based on the given values. Z and W will be initialized to 0.
     */
    vector4(const T x, const T y) noexcept;

    /*!
     * Create a vector based on the given values. W will be initialized to 0.
     */
    vector4(const T x, const T y, const T z) noexcept;

    /*!
     * Create a vector based on the given values.
     */
    vector4(const T x, const T y, const T z, const T w) noexcept;

    /*!
     * Create a vector based on the given values. Z and W will be initialized to 0.
     */
    template <typename U>
    explicit vector4(const U x, const U y) noexcept;

    /*!
     * Create a vector based on the given values. W will be initialized to 0.
     * Converting contstructor.
     */
    template <typename U>
    explicit vector4(const U x, const U y, const U z) noexcept;

    /*!
     * Create a vector based on the given values. Converting constructor
     */
    template <typename U>
    explicit vector4(const U x, const U y, const U z, const U w) noexcept;

    /*!
     * Create a vector based on the given vector. Converting constructor.
     */
    template <typename U>
    explicit vector4(const vector4<U> &vec) noexcept;

    /*!
     * Create a vector based on the given 2D vector. Z and W will be initialized to 0.
     */
    explicit vector4(const vector2<T> vec) noexcept;

    /*!
     * Create a vector based on the given 2D vector and a Z value. W will be initialized to 0.
     */
    explicit vector4(const vector2<T> vec, const T z) noexcept;

    /*!
     * Create a vector based on the given 2D vector and seperate Z and W values.
     */
    explicit vector4(const vector2<T> vec, const T z, const T w) noexcept;

    /*!
     * Create a vector based on the given 3D vector. W will be initialized to 0.
     */
    explicit vector4(const vector3<T> vec) noexcept;

    /*!
     * Create a vector based on the given 3D vector and a W value.
     */
    explicit vector4(const vector3<T> vec, const T w) noexcept;

    /*!
     * Create a vector based on the given array values (index 0 is X, 1 is Y, 2 is Z, 3 is W)
     */
    explicit vector4(const T xyzw[4]) noexcept;

    ~vector4() noexcept = default;

    vector4(const vector4<T> &) noexcept = default;
    auto operator=(const vector4<T> &) noexcept -> vector4<T> & = default;

    vector4(vector4<T> &&) noexcept = default;
    auto operator=(vector4<T> &&) noexcept -> vector4<T> & = default;

    auto operator=(const vector2<T> &vec) noexcept -> vector4<T> &;

    auto operator=(const vector3<T> &vec) noexcept -> vector4<T> &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y, 2 is Z, 3 is W)
     */
    [[nodiscard]] auto operator[](const std::size_t i) noexcept -> T &;

    /*!
     * Access vector values based on index. (index 0 is X, 1 is Y, 2 is Z, 3 is W)
     */
    [[nodiscard]] auto operator[](const std::size_t i) const noexcept -> const T &;

    /*!
     * Create an empty vector (all values are 0).
     */
    [[nodiscard]] static auto zero() noexcept -> vector4<T>;

    /*!
     * Change the values of an existing vector.
     */
    void set(const T new_x, const T new_y, const T new_z, const T new_w) noexcept;

    union {
        struct
        {
            T x;
            T y;
            T z;
            T w;
        };
        T value[4];
    };
};

template <typename T>
inline auto operator+(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator+(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator+(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator-(const vector4<T> &vec) noexcept -> vector4<T>;

template <typename T>
inline auto operator*(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator*(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator*(const T lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator/(const vector4<T> &lhs, const T rhs) noexcept -> vector4<T>;

template <typename T, typename U>
inline auto operator*(const vector4<T> &lhs, const vector4<U> &rhs) noexcept -> vector4<T>;

template <typename T, typename U>
inline auto operator*(const vector4<T> &lhs, const U rhs) noexcept -> vector4<T>;

template <typename T, typename U>
inline auto operator/(const vector4<T> &lhs, const U rhs) noexcept -> vector4<T>;

template <typename T>
inline auto operator+=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator+=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator-=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator-=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator*=(vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator*=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator/=(vector4<T> &lhs, const T rhs) noexcept -> vector4<T> &;

template <typename T, typename U>
inline auto operator*=(vector4<T> &lhs, const vector4<U> &rhs) noexcept -> vector4<T> &;

template <typename T, typename U>
inline auto operator*=(vector4<T> &lhs, const U rhs) noexcept -> vector4<T> &;

template <typename T, typename U>
inline auto operator/=(vector4<T> &lhs, const U rhs) noexcept -> vector4<T> &;

template <typename T>
inline auto operator==(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator!=(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator<(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator>(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> bool;

/*!
 * Translate (move) an existing vector.
 * \param[in, out] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \param[in] z - Relative Z coordinate
 * \param[in] w - Relative W coordinate
 */
template <typename T>
inline void translate(vector4<T> &lhs, const T x, const T y, const T z, const T w) noexcept;

/*!
 * Translate (move) an existing vector.
 * \param[in, out] lhs - Vector
 * \param[in] rhs - Relative X, Y, Z and W coordinates
 */
template <typename T>
inline void translate(vector4<T> &lhs, const vector4<T> &rhs) noexcept;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] x - Relative X coordinate
 * \param[in] y - Relative Y coordinate
 * \param[in] z - Relative Z coordinate
 * \param[in] w - Relative W coordinate
 * \return A new vector moved with the given offset
 */
template <typename T>
[[nodiscard]] inline auto translated(const vector4<T> &lhs, const T x, const T y, const T z, const T w) noexcept
    -> vector4<T>;

/*!
 * Translate (move) a vector to a new copy
 * \param[in] lhs - Vector
 * \param[in] rhs - Relative X, Y, Z and W coordinates.
 * \return A new vector moved with the given offset
 */
template <typename T>
[[nodiscard]] inline auto translated(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

/*!
 * Calculate the dot product of 2 given vectors.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Dot product
 */
template <typename T>
[[nodiscard]] inline auto dot(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T;

/*!
 * Calculate the length of a given vector.
 * \param[in] vec - Vector
 * \return Vector length
 */
template <typename T>
[[nodiscard]] inline auto length(const vector4<T> &vec) noexcept -> T;

/*!
 * Calculate the length of a given vector as a squared value to avoid having to do a square root.
 * \param[in] vec - Vector
 * \return Vector length&sup2;
 */
template <typename T>
[[nodiscard]] inline auto squared_length(const vector4<T> &vec) noexcept -> T;

/*!
 * Normalize a given directional vector (so that length = 1)
 * \param[in, out] vec - Vector
 */
template <typename T>
inline void normalize(vector4<T> &vec) noexcept;

/*!
 * Normalize a given directional vector (so that length = 1) to a new copy
 * \param[in] vec - Vector
 * \return Normalized vector
 */
template <typename T>
[[nodiscard]] inline auto normalized(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the sine values of a given vector.
 * \param[in] vec - Vector
 * \return Sine values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto sin(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Cosine values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto cos(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Tangent values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto tan(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the arc sine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc since values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto asin(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the arc cosine values of a given vector.
 * \param[in] vec - Vector
 * \return Arc cosine values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto acos(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the arc tangent values of a given vector.
 * \param[in] vec - Vector
 * \return Arc tangent values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto atan(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the absolute values of a given vector.
 * \param[in] vec - Vector
 * \return Absolute values of the given vector.
 */
template <typename T>
[[nodiscard]] inline auto abs(const vector4<T> &vec) noexcept -> vector4<T>;

/*!
 * Calculate the distance between 2 given vector points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance
 */
template <typename T>
[[nodiscard]] inline auto distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T;

/*!
 * Calculate the squared distance between 2 given vector points. This avoids having to do a square root.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Distance&sup2;
 */
template <typename T>
[[nodiscard]] inline auto squared_distance(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> T;

/*!
 * Calculate middle point between two given points.
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Middle point
 */
template <typename T>
[[nodiscard]] inline auto midpoint(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

/*!
 * Calculate floor for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Floor from 2 given vectors
 */
template <typename T>
[[nodiscard]] inline auto floor(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

/*!
 * Calculate ceil for 2 given vectors
 * \param[in] lhs - Vector
 * \param[in] rhs - Vector
 * \return Ceil from 2 given vectors
 */
template <typename T>
[[nodiscard]] inline auto ceil(const vector4<T> &lhs, const vector4<T> &rhs) noexcept -> vector4<T>;

/*!
 * Get a pointer into the underlying data structure of a given vector.
 * The vector data layout is [X Y Z W]
 * \param[in] vec - Vector
 * \return Pointer to vector data.
 */
template <typename T>
[[nodiscard]] inline auto ptr(vector4<T> &vec) noexcept -> T *;

/*!
 * Get a pointer into the underlying data structure of a given vector.
 * The vector data layout is [X Y Z W]
 * \param[in] vec - Vector
 * \return Const pointer to vector data.
 */
template <typename T>
[[nodiscard]] inline auto ptr(const vector4<T> &vec) noexcept -> const T *;

} // namespace aeon::math

#include <aeon/math/impl/vector4_impl.h>
#include <aeon/math/impl/vector4_operators_impl.h>

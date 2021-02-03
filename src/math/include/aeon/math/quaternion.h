// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for a quaternion.
 */

#pragma once

namespace aeon::math
{

template <typename T>
class vector3;

class mat3;

/*!
 * Class that represents a quaternion.
 */
class quaternion
{
public:
    /*!
     * Create an empty (all zeros) quaternion. This will NOT initialize to identity.
     */
    constexpr quaternion() noexcept;

    /*!
     * Create a quaternion based on the given values.
     */
    constexpr quaternion(const float w, const float x, const float y, const float z) noexcept;

    /*!
     * Create a quaternion based on the given values.
     */
    template <typename T>
    explicit constexpr quaternion(const T w, const T x, const T y, const T z) noexcept;

    /*!
     * Create a quaternion based on the given euler angles in radians.
     * Given euler angles must be X=pitch, Y=yaw, Z=roll.
     * \param[in] euler - Vector of Yaw, Pitch, Roll euler angles in radians.
     */
    explicit quaternion(const vector3<float> &euler) noexcept;

    /*!
     * Create a quaternion based on the given 3x3 matrix
     * \param[in] mat - 3x3 rotation matrix
     */
    explicit quaternion(const mat3 &mat) noexcept;

    ~quaternion() noexcept = default;

    constexpr quaternion(const quaternion &) noexcept = default;
    constexpr auto operator=(const quaternion &) noexcept -> quaternion & = default;

    constexpr quaternion(quaternion &&) noexcept = default;
    constexpr auto operator=(quaternion &&) noexcept -> quaternion & = default;

    /*!
     * Create an identity quaternion.
     * \return An identity quaternion.
     */
    [[nodiscard]] static constexpr auto indentity() noexcept -> quaternion;

    /*!
     * Set new values for an existing quaternion.
     */
    constexpr void set(const float new_w, const float new_x, const float new_y, const float new_z) noexcept;

    float w;
    float x;
    float y;
    float z;
};

inline constexpr auto operator+(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline constexpr auto operator-(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline constexpr auto operator*(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline constexpr auto operator*(const quaternion &lhs, const float rhs) noexcept -> quaternion;

inline constexpr auto operator/(const quaternion &lhs, const quaternion &rhs) noexcept -> quaternion;

inline constexpr auto operator/(const quaternion &lhs, const float rhs) noexcept -> quaternion;

inline constexpr auto operator+=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &;

inline constexpr auto operator-=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &;

inline constexpr auto operator*=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &;

inline constexpr auto operator*=(quaternion &lhs, const float rhs) noexcept -> quaternion &;

inline constexpr auto operator/=(quaternion &lhs, const quaternion &rhs) noexcept -> quaternion &;

inline constexpr auto operator/=(quaternion &lhs, const float rhs) noexcept -> quaternion &;

inline constexpr auto operator==(const quaternion &lhs, const quaternion &rhs) noexcept -> bool;

inline constexpr auto operator!=(const quaternion &lhs, const quaternion &rhs) noexcept -> bool;

/*!
 * Get the pitch rotation in radians from a given quaternion.
 * \param[in] quat - Quaternion
 * \return Pitch in radians.
 */
[[nodiscard]] inline auto pitch(const quaternion &quat) noexcept -> float;

/*!
 * Get the yaw rotation in radians from a given quaternion.
 * \param[in] quat - Quaternion
 * \return Yaw in radians.
 */
[[nodiscard]] inline auto yaw(const quaternion &quat) noexcept -> float;

/*!
 * Get the roll rotation in radians from a given quaternion.
 * \param[in] quat - Quaternion
 * \return Roll in radians.
 */
[[nodiscard]] inline auto roll(const quaternion &quat) noexcept -> float;

/*!
 * Get the euler angles in radians from a given quaternion.
 * \param[in] quat - Quaternion
 * \return Euler angles in radians where X=pitch, Y=yaw, Z=roll.
 */
[[nodiscard]] inline auto euler(const quaternion &quat) noexcept -> vector3<float>;

/*!
 * Calculate a dot product of 2 quaternions.
 * \param[in] a - Quaternion
 * \param[in] b - Quaternion
 * \return dot product of a and b.
 */
[[nodiscard]] inline constexpr auto dot(const quaternion &a, const quaternion &b) noexcept -> float;

/*!
 * Get a pointer into the underlying data structure of a given quaternion.
 * The quaternion data layout is [W X Y Z]
 * \param[in] quat - Quaternion
 * \return Pointer to quaternion floating point data.
 */
[[nodiscard]] inline constexpr auto ptr(quaternion &quat) noexcept -> float *;

/*!
 * Get a pointer into the underlying data structure of a given quaternion.
 * The quaternion data layout is [W X Y Z]
 * \param[in] quat - Quaternion
 * \return Const pointer to quaternion floating point data.
 */
[[nodiscard]] inline constexpr auto ptr(const quaternion &quat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/quaternion_impl.h>
#include <aeon/math/impl/quaternion_operators_impl.h>

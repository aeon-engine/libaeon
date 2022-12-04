// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for a 3x3 matrix.
 */

#pragma once

#include <aeon/math/math_fwd.h>
#include <aeon/math/vector3.h>
#include <aeon/math/units.h>
#include <aeon/common/concepts.h>
#include <array>

namespace aeon::math
{

/*!
 * Class that represents a 3x3 matrix.
 *
 * Data is laid out in column order so that the class can be used with OpenGL.
 */
class mat3
{
public:
    /*!
     * Create an empty (all zeros) matrix. This will NOT initialize to identity.
     */
    constexpr mat3() noexcept;

    /*!
     * Create a matrix based on the given values. Values are in column-major order
     */
    constexpr mat3(const float m00, const float m10, const float m20, const float m01, const float m11, const float m21,
                   const float m02, const float m12, const float m22) noexcept;

    /*!
     * Create a matrix based on the given values. Values are in column-major order
     */
    constexpr mat3(const vector3<float> &c1, const vector3<float> &c2, const vector3<float> &c3) noexcept;

    ~mat3() noexcept = default;

    /*!
     * Create a matrix based on a given 4x4 matrix.
     */
    explicit constexpr mat3(const mat4 &m) noexcept;

    /*!
     * Create a rotation matrix based on a given quaternion.
     */
    explicit mat3(const quaternion &q) noexcept;

    constexpr mat3(const mat3 &) noexcept = default;
    constexpr auto operator=(const mat3 &) noexcept -> mat3 & = default;

    constexpr mat3(mat3 &&) noexcept = default;
    constexpr auto operator=(mat3 &&) noexcept -> mat3 & = default;

    /*!
     * Access a column within this matrix.
     * \return A reference to the entire column.
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) noexcept -> vector3<float> &;

    /*!
     * Access a column within this matrix.
     * \return A const reference to the entire column.
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) const noexcept -> const vector3<float> &;

    /*!
     * Access a value within this matrix based on a given column and row index.
     * \param[in] column_index - Column
     * \param[in] row_index - Row
     * \return Value based on the given column and row index.
     */
    [[nodiscard]] constexpr auto at(const int column_index, const int row_index) const noexcept -> float;

    /*!
     * Create an empty matrix (all values are zero)
     * \return An empty matrix.
     */
    [[nodiscard]] static constexpr auto zero() noexcept -> mat3;

    /*!
     * Create an identity matrix.
     * \return An identity matrix.
     */
    [[nodiscard]] static constexpr auto identity() noexcept -> mat3;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] xy - Amount of scaling done over the X and Y axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto scale(const float xy) noexcept -> mat3;

    /*!
     * Create a scaling matrix based on given values.
     * \param[in] x - Amount of scaling done over the X axis.
     * \param[in] y - Amount of scaling done over the Y axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto scale(const float x, const float y) noexcept -> mat3;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] vec - Amount of scaling done over the X and Y axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto scale(const vector2<float> &vec) noexcept -> mat3;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] xy - Amount of scaling done over the X and Y axis.
     * \return A scaling matrix.
     */
    template <common::concepts::arithmetic_convertible T>
    [[nodiscard]] static constexpr auto scale(const T xy) noexcept -> mat3;

    /*!
     * Create a scaling matrix based on given values.
     * \param[in] x - Amount of scaling done over the X axis.
     * \param[in] y - Amount of scaling done over the Y axis.
     * \return A scaling matrix.
     */
    template <common::concepts::arithmetic_convertible T>
    [[nodiscard]] static constexpr auto scale(const T x, const T y) noexcept -> mat3;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] vec - Amount of scaling done over the X and Y axis.
     * \return A scaling matrix.
     */
    template <common::concepts::arithmetic_convertible T>
    [[nodiscard]] static constexpr auto scale(const vector2<T> &vec) noexcept -> mat3;

    /*!
     * Create a translation matrix based on given values.
     * \param[in] x - Amount of translation done over the X axis.
     * \param[in] y - Amount of translation done over the Y axis.
     * \return A translation matrix.
     */
    [[nodiscard]] static constexpr auto translate(const float x, const float y) noexcept -> mat3;

    /*!
     * Create a translation matrix based on a given value.
     * \param[in] vec - Amount of translation done over the X and Y axis.
     * \return A translation matrix.
     */
    [[nodiscard]] static constexpr auto translate(const vector2<float> &vec) noexcept -> mat3;

    /*!
     * Create a translation matrix based on given values.
     * \param[in] x - Amount of translation done over the X axis.
     * \param[in] y - Amount of translation done over the Y axis.
     * \return A translation matrix.
     */
    template <common::concepts::arithmetic_convertible T>
    [[nodiscard]] static constexpr auto translate(const T x, const T y) noexcept -> mat3;

    /*!
     * Create a translation matrix based on a given value.
     * \param[in] vec - Amount of translation done over the X and Y axis.
     * \return A translation matrix.
     */
    template <common::concepts::arithmetic_convertible T>
    [[nodiscard]] static constexpr auto translate(const vector2<T> &vec) noexcept -> mat3;

    /*!
     * Create a rotation matrix based on a given value.
     * \param[in] angle - Angle in radians.
     * \return A rotation matrix.
     */
    [[nodiscard]] static auto rotate(const unitf<radian> angle) noexcept -> mat3;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] auto data() noexcept -> std::byte *;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] auto data() const noexcept -> const std::byte *;

    std::array<vector3<float>, 3> column;
};

inline auto operator*(const mat3 &lhs, const mat3 &rhs) noexcept -> mat3;

inline auto operator*(const mat3 &lhs, const vector3<float> &rhs) noexcept -> vector3<float>;

inline auto operator*(const mat3 &lhs, const float rhs) noexcept -> mat3;

inline constexpr auto operator-(const mat3 &mat) noexcept -> mat3;

inline auto operator*=(mat3 &lhs, const mat3 &rhs) noexcept -> mat3 &;

inline auto operator*=(mat3 &lhs, const float rhs) noexcept -> mat3 &;

inline constexpr auto operator==(const mat3 &lhs, const mat3 &rhs) noexcept -> bool;

inline constexpr auto operator!=(const mat3 &lhs, const mat3 &rhs) noexcept -> bool;

/*!
 * Calculate the determinant of a given matrix.
 * \param[in] mat - Matrix
 * \return Determinant (ie. |mat|)
 */
[[nodiscard]] inline constexpr auto determinant(const mat3 &mat) noexcept -> float;

/*!
 * Decompose a given matrix into a scale and shear using QR decomposition (factorization).
 * \param[in] mat - Matrix
 * \param[out] scale - Decomposed scale (taken from the triangular matrix R)
 * \param[out] shear - Decomposed shear (taken from the triangular matrix R)
 * \return Orthogonal matrix Q
 */
[[nodiscard]] inline constexpr auto qr_decompose(const mat3 &mat, vector3<float> &scale, vector3<float> &shear) noexcept
    -> mat3;

/*!
 * Get a pointer into the underlying data structure of a given matrix.
 * The matrix data layout is column major.
 * \param[in] mat - Matrix
 * \return Pointer to column major floating point data.
 */
[[nodiscard]] inline constexpr auto ptr(mat3 &mat) noexcept -> float *;

/*!
 * Get a pointer into the underlying data structure of a given matrix.
 * The matrix data layout is column major.
 * \param[in] mat - Matrix
 * \return Const pointer to column major floating point data.
 */
[[nodiscard]] inline constexpr auto ptr(const mat3 &mat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/mat3_impl.h>
#include <aeon/math/impl/mat3_operators_impl.h>

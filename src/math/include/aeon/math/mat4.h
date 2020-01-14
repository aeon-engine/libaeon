// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

/*!
 * \file
 * \brief Mathematical operations for a 4x4 matrix.
 */

#pragma once

#include <aeon/math/vector4.h>
#include <aeon/math/units.h>
#include <array>

namespace aeon::math
{

template <typename T>
class rectangle;

template <typename T>
class vector3;

class mat3;
class quaternion;

/*!
 * Class that represents a 4x4 matrix.
 *
 * Interface (like constructor) is row order.
 * Data is laid out in column order so that the class can be used with OpenGL.
 *
 * The class is 16-bytes aligned to allow for SIMD optimizations.
 */
class alignas(16) mat4
{
public:
    /*!
     * Create an empty (all zeros) matrix. This will NOT initialize to identity.
     */
    constexpr mat4() noexcept;

    /*!
     * Create a matrix based on the given values. Values are in row order.
     */
    constexpr mat4(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11,
                   const float m12, const float m13, const float m20, const float m21, const float m22, const float m23,
                   const float m30, const float m31, const float m32, const float m33) noexcept;

    ~mat4() noexcept = default;

    /*!
     * Create a matrix based on a given 3x3 matrix.
     *
     * The 4x4 matrix will be constructed as follows (x is a value in the 3x3 matrix):
     *
     *\verbatim
     * x x x 0
     * x x x 0
     * x x x 0
     * 0 0 0 1
     *\endverbatim
     */
    explicit constexpr mat4(const mat3 &m) noexcept;

    /*!
     * Create a rotation matrix based on a given quaternion.
     */
    explicit mat4(const quaternion &q) noexcept;

    constexpr mat4(const mat4 &) noexcept = default;
    constexpr auto operator=(const mat4 &) noexcept -> mat4 & = default;

    constexpr mat4(mat4 &&) noexcept = default;
    constexpr auto operator=(mat4 &&) noexcept -> mat4 & = default;

    /*!
     * Access a column within this matrix.
     * \return A reference to the entire column.
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) noexcept -> vector4<float> &;

    /*!
     * Access a column within this matrix.
     * \return A const reference to the entire column.
     */
    [[nodiscard]] constexpr auto operator[](const std::size_t i) const noexcept -> const vector4<float> &;

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
    [[nodiscard]] static constexpr auto zero() noexcept -> mat4;

    /*!
     * Create an identity matrix.
     * \return An identity matrix.
     */
    [[nodiscard]] static constexpr auto indentity() noexcept -> mat4;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] xyz - Amount of scaling done over the X, Y and Z axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto scale(const float xyz) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on given values.
     * \param[in] x - Amount of scaling done over the X axis.
     * \param[in] y - Amount of scaling done over the Y axis.
     * \param[in] z - Amount of scaling done over the Z axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto scale(const float x, const float y, const float z) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] vec - Amount of scaling done over the X, Y and Z axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto scale(const vector3<float> &vec) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] xyz - Amount of scaling done over the X, Y and Z axis.
     * \return A scaling matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto scale(const T xyz) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on given values.
     * \param[in] x - Amount of scaling done over the X axis.
     * \param[in] y - Amount of scaling done over the Y axis.
     * \param[in] z - Amount of scaling done over the Z axis.
     * \return A scaling matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto scale(const T x, const T y, const T z) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] vec - Amount of scaling done over the X, Y and Z axis.
     * \return A scaling matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto scale(const vector3<T> &vec) noexcept -> mat4;

    /*!
     * Create a translation matrix based on given values.
     * \param[in] x - Amount of translation done over the X axis.
     * \param[in] y - Amount of translation done over the Y axis.
     * \return A translation matrix.
     */
    [[nodiscard]] static constexpr auto translate(const float x, const float y) noexcept -> mat4;

    /*!
     * Create a translation matrix based on given values.
     * \param[in] x - Amount of translation done over the X axis.
     * \param[in] y - Amount of translation done over the Y axis.
     * \param[in] z - Amount of translation done over the Z axis.
     * \return A translation matrix.
     */
    [[nodiscard]] static constexpr auto translate(const float x, const float y, const float z) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] vec - Amount of scaling done over the X, Y and Z axis.
     * \return A scaling matrix.
     */
    [[nodiscard]] static constexpr auto translate(const vector3<float> &vec) noexcept -> mat4;

    /*!
     * Create a translation matrix based on given values.
     * \param[in] x - Amount of translation done over the X axis.
     * \param[in] y - Amount of translation done over the Y axis.
     * \return A translation matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto translate(const T x, const T y) noexcept -> mat4;

    /*!
     * Create a translation matrix based on given values.
     * \param[in] x - Amount of translation done over the X axis.
     * \param[in] y - Amount of translation done over the Y axis.
     * \param[in] z - Amount of translation done over the Z axis.
     * \return A translation matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto translate(const T x, const T y, const T z) noexcept -> mat4;

    /*!
     * Create a scaling matrix based on a given value.
     * \param[in] vec - Amount of scaling done over the X, Y and Z axis.
     * \return A scaling matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto translate(const vector3<T> &vec) noexcept -> mat4;

    /*!
     * Create a rotation matrix based on given values.
     * \param[in] angle - Angle in radians.
     * \param[in] vec - Vector that determines which axis will be rotated with the given angle.
     * \return A rotation matrix.
     */
    [[nodiscard]] static auto rotate(const unitf<radian> angle, const vector3<float> &vec) noexcept -> mat4;

    /*!
     * Create a rotation matrix based on given values.
     * \param[in] angle - Angle in radians.
     * \param[in] vec - Vector that determines which axis will be rotated with the given angle.
     * \return A rotation matrix.
     */
    template <typename T>
    [[nodiscard]] static auto rotate(const unitf<radian> angle, const vector3<T> &vec) noexcept -> mat4;

    /*!
     * Create an orthographic matrix based on given values.
     * \param[in] left - Left value
     * \param[in] right - Right value
     * \param[in] bottom - Bottom value
     * \param[in] top - Top value
     * \return An orthographic matrix.
     */
    [[nodiscard]] static constexpr auto ortho(const float left, const float right, const float bottom,
                                              const float top) noexcept -> mat4;

    /*!
     * Create an orthographic matrix based on given values.
     * \param[in] left - Left value
     * \param[in] right - Right value
     * \param[in] bottom - Bottom value
     * \param[in] top - Top value
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return An orthographic matrix.
     */
    [[nodiscard]] static constexpr auto ortho(const float left, const float right, const float bottom, const float top,
                                              const float near, const float far) noexcept -> mat4;

    /*!
     * Create an orthographic matrix based on given values.
     * \param[in] left - Left value
     * \param[in] right - Right value
     * \param[in] bottom - Bottom value
     * \param[in] top - Top value
     * \return An orthographic matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto ortho(const T left, const T right, const T bottom, const T top) noexcept
        -> mat4;

    /*!
     * Create an orthographic matrix based on given values.
     * \param[in] left - Left value
     * \param[in] right - Right value
     * \param[in] bottom - Bottom value
     * \param[in] top - Top value
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return An orthographic matrix.
     */
    template <typename T, typename U>
    [[nodiscard]] static constexpr auto ortho(const T left, const T right, const T bottom, const T top, const U near,
                                              const U far) noexcept -> mat4;

    /*!
     * Create an orthographic matrix based on given values.
     * \param[in] rect - Left, Right, Bottom and Top values
     * \return An orthographic matrix.
     */
    template <typename T>
    [[nodiscard]] static constexpr auto ortho(const rectangle<T> &rect) noexcept -> mat4;

    /*!
     * Create an orthographic matrix based on given values.
     * \param[in] rect - Left, Right, Bottom and Top values
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return An orthographic matrix.
     */
    template <typename T, typename U>
    [[nodiscard]] static constexpr auto ortho(const rectangle<T> &rect, const U near, const U far) noexcept -> mat4;

    /*!
     * Create a projection (perspective) matrix based on given values.
     * \param[in] fov_y - Horizontal field of view in radians
     * \param[in] aspect_ratio - Aspect ratio
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return A projection (perspective) matrix.
     */
    [[nodiscard]] static auto projection(const unitf<radian> fov_y, const float aspect_ratio, const float near,
                                         const float far) noexcept -> mat4;

    /*!
     * Create a projection (perspective) matrix based on given values.
     * \param[in] fov_y - Horizontal field of view in radians
     * \param[in] aspect_ratio - Aspect ratio
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return A projection (perspective) matrix.
     */
    template <typename T, typename U>
    [[nodiscard]] static auto projection(const unit_base<radian, void, U> fov_y, const T aspect_ratio, const U near,
                                         const U far) noexcept -> mat4;

    /*!
     * Create a projection (perspective) matrix based on given values.
     * \param[in] fov - Full field of view in radians
     * \param[in] width - Width of the view
     * \param[in] height - Height of the view
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return A projection (perspective) matrix.
     */
    [[nodiscard]] static auto projection_fov(const unitf<radian> fov, const float width, const float height,
                                             const float near, const float far) noexcept -> mat4;

    /*!
     * Create a projection (perspective) matrix based on given values.
     * \param[in] fov - Full field of view in radians
     * \param[in] width - Width of the view
     * \param[in] height - Height of the view
     * \param[in] near - Near clip plane
     * \param[in] far - Far clip plane
     * \return A projection (perspective) matrix.
     */
    template <typename T, typename U>
    [[nodiscard]] static auto projection_fov(const unit_base<radian, void, U> fov, const T width, const T height,
                                             const U near, const U far) noexcept -> mat4;

    std::array<vector4<float>, 4> column;
};

inline auto operator*(const mat4 &lhs, const mat4 &rhs) noexcept -> mat4;

inline constexpr auto operator*(const mat4 &lhs, const vector4<float> &rhs) noexcept -> vector4<float>;

inline constexpr auto operator*(const mat4 &lhs, const float rhs) noexcept -> mat4;

inline auto operator*=(mat4 &lhs, const mat4 &rhs) noexcept -> mat4 &;

inline constexpr auto operator*=(mat4 &lhs, const float rhs) noexcept -> mat4 &;

inline constexpr auto operator==(const mat4 &lhs, const mat4 &rhs) noexcept -> bool;

inline constexpr auto operator!=(const mat4 &lhs, const mat4 &rhs) noexcept -> bool;

/*!
 * Calculate the determinant of a given matrix.
 * \param[in] mat - Matrix
 * \return Determinant (ie. |mat|)
 */
[[nodiscard]] inline constexpr auto determinant(const mat4 &mat) noexcept -> float;

/*!
 * Calculate the inverse of a given matrix
 * \param[in] mat - Matrix
 * \return Inverse of mat (mat<SUP>-1</SUP>)
 */
[[nodiscard]] inline constexpr auto inverse(const mat4 &mat) noexcept -> mat4;

/*!
 * Check if a given matrix is affine.
 * A matrix is affine if the 4th row is equal to [0 0 0 1] and thus has no projective coefficients.
 * \param[in] mat - Matrix
 * \return True if the matrix is affine.
 */
[[nodiscard]] inline constexpr auto is_affine(const mat4 &mat) noexcept -> bool;

/*!
 * Decompose a matrix into a translation, scale and orientation.
 * Internally this is done through a QR decomposition.
 * \param[in] mat - Matrix
 * \param[out] translation - Decomposed translation
 * \param[out] scale - Decomposed scale
 * \param[out] orientation - Decomposed orientation (rotation)
 */
inline void decompose(const mat4 &mat, vector3<float> &translation, vector3<float> &scale,
                      quaternion &orientation) noexcept;

/*!
 * Get a pointer into the underlying data structure of a given matrix.
 * The matrix data layout is column major.
 * \param[in] mat - Matrix
 * \return Pointer to column major floating point data.
 */
[[nodiscard]] inline constexpr auto ptr(mat4 &mat) noexcept -> float *;

/*!
 * Get a pointer into the underlying data structure of a given matrix.
 * The matrix data layout is column major.
 * \param[in] mat - Matrix
 * \return Const pointer to column major floating point data.
 */
[[nodiscard]] inline constexpr auto ptr(const mat4 &mat) noexcept -> const float *;

} // namespace aeon::math

#include <aeon/math/impl/mat4_impl.h>
#include <aeon/math/impl/mat4_operators_impl.h>

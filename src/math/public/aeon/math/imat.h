// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <aeon/common/element_type.h>

namespace aeon::math
{

/*!
 * Base class that represents a matrix of dynamic size that does not own the data
 * Unlike mat3 and mat4, data is laid out in row order
 */
class imat
{
public:
    using underlying_type = std::byte;
    using dimensions_type = std::int32_t;
    using size_type = std::size_t;
    using stride_type = std::size_t;

    imat() noexcept = default;
    virtual ~imat() noexcept = default;

    imat(const imat &) noexcept = default;
    auto operator=(const imat &) noexcept -> imat & = default;

    imat(imat &&) noexcept = default;
    auto operator=(imat &&) noexcept -> imat & = default;

    /*!
     * Get the element type of the matrix.
     * \return The element type of the matrix
     */
    [[nodiscard]] virtual auto element_type() const noexcept -> common::element_type = 0;

    /*!
     * Get the width of the matrix.
     * \return The width of the matrix.
     */
    [[nodiscard]] virtual auto width() const noexcept -> dimensions_type = 0;

    /*!
     * Get the height of the matrix.
     * \return The height of the matrix.
     */
    [[nodiscard]] virtual auto height() const noexcept -> dimensions_type = 0;

    /*!
     * Get the size of the matrix (width, height).
     * \return The size of the matrix.
     */
    [[nodiscard]] virtual auto dimensions() const noexcept -> size2d<dimensions_type> = 0;

    /*!
     * Get the stride of the matrix. The stride is the amount of bytes between 2 lines/rows.
     * \return The stride of the matrix.
     */
    [[nodiscard]] virtual auto stride() const noexcept -> stride_type = 0;

    /*!
     * Get the size of the data based on the stride and height.
     * \return The size of the data in bytes (unsigned)
     */
    [[nodiscard]] virtual auto size() const noexcept -> size_type = 0;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] virtual auto data() noexcept -> underlying_type * = 0;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] virtual auto data() const noexcept -> const underlying_type * = 0;
};

/*!
 * Compare two matrices. The comparison should only really be used for (unit)testing as it is very slow.
 * Also note that components are compared on byte level which may yield unexpected results for floating point
 * components.
 */
inline auto operator==(const imat &lhs, const imat &rhs) noexcept -> bool;

/*!
 * Compare two matrices. The comparison should only really be used for (unit)testing as it is very slow.
 * Also note that components are compared on byte level which may yield unexpected results for floating point
 * components.
 */
inline auto operator!=(const imat &lhs, const imat &rhs) noexcept -> bool;

/*!
 * Get the element type of the matrix.
 * \param[in] m - A matrix
 * \return The element type of the matrix
 */
[[nodiscard]] inline auto element_type(const imat &m) noexcept -> common::element_type;

/*!
 * Get the width of the given matrix.
 * \param[in] m - A matrix
 * \return The width of the matrix.
 */
[[nodiscard]] inline auto width(const imat &m) noexcept -> imat::dimensions_type;

/*!
 * Get the height of the given matrix.
 * \param[in] m - A matrix
 * \return The height of the matrix.
 */
[[nodiscard]] inline auto height(const imat &m) noexcept -> imat::dimensions_type;

/*!
 * Get the dimensions of the given matrix (width, height).
 * \param[in] m - A matrix
 * \return The dimensions of the matrix.
 */
[[nodiscard]] inline auto dimensions(const imat &m) noexcept -> size2d<imat::dimensions_type>;

/*!
 * Get the stride of the given matrix.
 * The stride is the amount of bytes between 2 lines/rows.
 * \param[in] m - A matrix
 * \return The stride of the matrix.
 */
[[nodiscard]] inline auto stride(const imat &m) noexcept -> imat::stride_type;

/*!
 * Returns true if the data described by the given matrix is laid out in memory in a
 * continuous fashion
 * (ie. stride = element_type.size * width)
 * \param[in] m - A mat
 * \return True if the matrix's data is continuous.
 */
[[nodiscard]] inline auto continuous(const imat &m) noexcept -> bool;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given matrix.
 * \param[in] m - A matrix
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimensions of the matrix.
 */
[[nodiscard]] inline auto contains(const imat &m, const vector2<typename imat::dimensions_type> coord) noexcept -> bool;

/*!
 * Get the full size in bytes of the data described by the matrix in memory (stride * height).
 * \param[in] m - A matrix
 * \return The size in bytes.
 */
[[nodiscard]] inline auto size(const imat &m) noexcept -> imat::size_type;

/*!
 * Returns true if the matrix is null. A matrix is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] m - A matrix
 * \return Returns true if the matrix  is null.
 */
[[nodiscard]] inline auto null(const imat &m) noexcept -> bool;

/*!
 * Returns true if the matrix is valid. A matrix is valid when it is not null.
 * \see null(const imat &m)
 * \param[in] m - A matrix
 * \return Returns true if the matrix is valid.
 */
[[nodiscard]] inline auto valid(const imat &m) noexcept -> bool;

/*!
 * Returns the pointer to the start of the element data within the given matrix. This is a relatively slow convenience
 * function that should not be used in a loop. Instead, access the data and use common::offset_of to calculate the
 * offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] coord - The coordinates to get the pointer to
 * \return The pointer to where the element data begins
 */
[[nodiscard]] inline auto at(imat &m, const vector2<imat::dimensions_type> coord) noexcept -> imat::underlying_type *;

/*!
 * Returns the pointer to the start of the element data within the given matrix. This is a relatively slow convenience
 * function that should not be used in a loop. Instead, access the data and use common::offset_of to calculate the
 * offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] coord - The coordinates to get the pointer to
 * \return The pointer to where the element data begins
 */
[[nodiscard]] inline auto at(const imat &m, const vector2<imat::dimensions_type> coord) noexcept
    -> const imat::underlying_type *;

/*!
 * Returns the typed pointer (T) to the start of the element data within the given matrix. This is a relatively slow
 * convenience function that should not be used in a loop. Instead, access the data and use common::offset_of to
 * calculate the offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] coord - The coordinates to get the pointer to
 * \return The typed pointer to where the element data begins
 */
template <typename T>
[[nodiscard]] inline auto at(imat &m, const vector2<imat::dimensions_type> coord) noexcept -> T *;

/*!
 * Returns the typed pointer (T) to the start of the element data within the given matrix. This is a relatively slow
 * convenience function that should not be used in a loop. Instead, access the data and use common::offset_of to
 * calculate the offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] coord - The coordinates to get the pointer to
 * \return The typed pointer to where the element data begins
 */
template <typename T>
[[nodiscard]] inline auto at(const imat &m, const vector2<imat::dimensions_type> coord) noexcept -> const T *;

/*!
 * Returns the pointer to the start of the element data within the given matrix. This is a relatively slow convenience
 * function that should not be used in a loop. Instead, access the data and use common::offset_of to calculate the
 * offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] x - The X coordinate to get the pointer to
 * \param[in] y - The Y coordinate to get the pointer to
 * \return The pointer to where the element data begins
 */
[[nodiscard]] inline auto at(imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept
    -> imat::underlying_type *;

/*!
 * Returns the pointer to the start of the element data within the given matrix. This is a relatively slow convenience
 * function that should not be used in a loop. Instead, access the data and use common::offset_of to calculate the
 * offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] x - The X coordinate to get the pointer to
 * \param[in] y - The Y coordinate to get the pointer to
 * \return The pointer to where the element data begins
 */
[[nodiscard]] inline auto at(const imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept
    -> const imat::underlying_type *;

/*!
 * Returns the typed pointer (T) to the start of the element data within the given matrix. This is a relatively slow
 * convenience function that should not be used in a loop. Instead, access the data and use common::offset_of to
 * calculate the offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] x - The X coordinate to get the pointer to
 * \param[in] y - The Y coordinate to get the pointer to
 * \return The typed pointer to where the element data begins
 */
template <typename T>
[[nodiscard]] inline auto at(imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept -> T *;

/*!
 * Returns the typed pointer (T) to the start of the element data within the given matrix. This is a relatively slow
 * convenience function that should not be used in a loop. Instead, access the data and use common::offset_of to
 * calculate the offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] x - The X coordinate to get the pointer to
 * \param[in] y - The Y coordinate to get the pointer to
 * \return The typed pointer to where the element data begins
 */
template <typename T>
[[nodiscard]] inline auto at(const imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept
    -> const T *;

/*!
 * Fill the given matrix with a value. The given type must match the element_type, otherwise it will trigger undefined
 * behavior.
 */
template <typename T>
inline void fill(imat &m, const T value) noexcept;

/*!
 * Fill a part of the given matrix with a value. The given type must match the element_type, otherwise it will trigger
 * undefined behavior.
 */
template <typename T>
inline void fill(imat &m, const math::rectangle<imat::dimensions_type> rect, const T value) noexcept;

/*!
 * Blit the contents of one matrix into another
 */
inline void blit(const imat &src, imat &dst, const vector2<imat::dimensions_type> pos) noexcept;

/*!
 * Invert the given matrix vertically (flip upside-down)
 */
inline void invert_vertically(imat &m);

} // namespace aeon::math

#include <aeon/math/impl/imat_impl.h>

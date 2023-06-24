// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/math_fwd.h>
#include <aeon/math/size2d.h>
#include <aeon/math/swizzle_component.h>
#include <aeon/common/element_type.h>

namespace aeon::math
{

/*!
 * Class that represents a matrix of dynamic size that does not own the data
 * Unlike mat3 and mat4, data is laid out in row order
 */
class mat_view
{
public:
    using underlying_type = std::byte;
    using dimensions_type = std::int32_t;
    using size_type = std::size_t;
    using stride_type = std::size_t;

    /*!
     * Create an empty matrix.
     */
    mat_view() noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Raw matrix data
     */
    explicit mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                      underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Raw matrix data
     */
    explicit mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                      underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     */
    explicit mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                      const stride_type stride, underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     */
    explicit mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                      const stride_type stride, underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Raw matrix data
     * \param[in] size - The size of the data (usually this is stride * height, but not always)
     */
    explicit mat_view(const common::element_type type, const size2d<dimensions_type> dimensions, underlying_type *data,
                      const size_type size) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Raw matrix data
     * \param[in] size - The size of the data (usually this is stride * height, but not always)
     */
    explicit mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                      underlying_type *data, const size_type size) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     * \param[in] size - The size of the data (usually this is stride * height, but not always)
     */
    explicit mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                      const stride_type stride, underlying_type *data, const size_type size) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     * \param[in] size - The size of the data (usually this is stride * height, but not always)
     */
    explicit mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                      const stride_type stride, underlying_type *data, const size_type size) noexcept;

    ~mat_view() noexcept = default;

    mat_view(const mat_view &) noexcept = default;
    auto operator=(const mat_view &) noexcept -> mat_view & = default;

    mat_view(mat_view &&) noexcept = default;
    auto operator=(mat_view &&) noexcept -> mat_view & = default;

    /*!
     * Get the element type of the matrix.
     * \return The element type of the matrix
     */
    [[nodiscard]] auto element_type() const noexcept -> common::element_type;

    /*!
     * Get the width of the matrix.
     * \return The width of the matrix.
     */
    [[nodiscard]] auto width() const noexcept -> dimensions_type;

    /*!
     * Get the height of the matrix.
     * \return The height of the matrix.
     */
    [[nodiscard]] auto height() const noexcept -> dimensions_type;

    /*!
     * Get the size of the matrix (width, height).
     * \return The size of the matrix.
     */
    [[nodiscard]] auto dimensions() const noexcept -> size2d<dimensions_type>;

    /*!
     * Get the stride of the matrix. The stride is the amount of bytes between 2 lines/rows.
     * \return The stride of the matrix.
     */
    [[nodiscard]] auto stride() const noexcept -> stride_type;

    /*!
     * Get the size of the data. Usually this is based on the stride and height.
     * \return The size of the data in bytes (unsigned)
     */
    [[nodiscard]] auto size() const noexcept -> size_type;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] auto data() noexcept -> underlying_type *;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] auto data() const noexcept -> const underlying_type *;

protected:
    common::element_type type_;
    underlying_type *data_ptr_;
    size2d<dimensions_type> dimensions_;
    stride_type stride_;
    size_type size_;
};

/*!
 * Compare two matrices. The comparison should only really be used for (unit)testing as it is very slow.
 * Also note that components are compared on byte level which may yield unexpected results for floating point
 * components.
 */
[[nodiscard]] inline auto operator==(const mat_view &lhs, const mat_view &rhs) noexcept -> bool;

/*!
 * Compare two matrices. The comparison should only really be used for (unit)testing as it is very slow.
 * Also note that components are compared on byte level which may yield unexpected results for floating point
 * components.
 */
[[nodiscard]] inline auto operator!=(const mat_view &lhs, const mat_view &rhs) noexcept -> bool;

/*!
 * Get the element type of the matrix.
 * \param[in] m - A matrix
 * \return The element type of the matrix
 */
[[nodiscard]] inline auto element_type(const mat_view &m) noexcept -> common::element_type;

/*!
 * Get the width of the given matrix.
 * \param[in] m - A matrix
 * \return The width of the matrix.
 */
[[nodiscard]] inline auto width(const mat_view &m) noexcept -> mat_view::dimensions_type;

/*!
 * Get the height of the given matrix.
 * \param[in] m - A matrix
 * \return The height of the matrix.
 */
[[nodiscard]] inline auto height(const mat_view &m) noexcept -> mat_view::dimensions_type;

/*!
 * Get the dimensions of the given matrix (width, height).
 * \param[in] m - A matrix
 * \return The dimensions of the matrix.
 */
[[nodiscard]] inline auto dimensions(const mat_view &m) noexcept -> size2d<mat_view::dimensions_type>;

/*!
 * Get the stride of the given matrix.
 * The stride is the amount of bytes between 2 lines/rows.
 * \param[in] m - A matrix
 * \return The stride of the matrix.
 */
[[nodiscard]] inline auto stride(const mat_view &m) noexcept -> mat_view::stride_type;

/*!
 * Returns true if the data described by the given matrix is laid out in memory in a
 * continuous fashion
 * (ie. stride = element_type.size * width)
 * \param[in] m - A mat
 * \return True if the matrix's data is continuous.
 */
[[nodiscard]] inline auto continuous(const mat_view &m) noexcept -> bool;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given matrix.
 * \param[in] m - A matrix
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimensions of the matrix.
 */
[[nodiscard]] inline auto contains(const mat_view &m, const vector2<typename mat_view::dimensions_type> coord) noexcept
    -> bool;

/*!
 * Get the full size in bytes of the data described by the matrix in memory (stride * height).
 * \param[in] m - A matrix
 * \return The size in bytes.
 */
[[nodiscard]] inline auto size(const mat_view &m) noexcept -> mat_view::size_type;

/*!
 * Returns true if the matrix is null. A matrix is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] m - A matrix
 * \return Returns true if the matrix  is null.
 */
[[nodiscard]] inline auto null(const mat_view &m) noexcept -> bool;

/*!
 * Returns true if the matrix is valid. A matrix is valid when it is not null.
 * \see null(const mat_view &m)
 * \param[in] m - A matrix
 * \return Returns true if the matrix is valid.
 */
[[nodiscard]] inline auto valid(const mat_view &m) noexcept -> bool;

/*!
 * Returns the pointer to the start of the element data within the given matrix. This is a relatively slow convenience
 * function that should not be used in a loop. Instead, access the data and use common::offset_of to calculate the
 * offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] coord - The coordinates to get the pointer to
 * \return The pointer to where the element data begins
 */
[[nodiscard]] inline auto at(mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept
    -> mat_view::underlying_type *;

/*!
 * Returns the pointer to the start of the element data within the given matrix. This is a relatively slow convenience
 * function that should not be used in a loop. Instead, access the data and use common::offset_of to calculate the
 * offset on the raw data.
 * \see common::offset_of()
 * \param[in] m - A matrix
 * \param[in] coord - The coordinates to get the pointer to
 * \return The pointer to where the element data begins
 */
[[nodiscard]] inline auto at(const mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept
    -> const mat_view::underlying_type *;

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
[[nodiscard]] inline auto at(mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept -> T *;

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
[[nodiscard]] inline auto at(const mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept -> const T *;

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
[[nodiscard]] inline auto at(mat_view &m, const mat_view::dimensions_type x, const mat_view::dimensions_type y) noexcept
    -> mat_view::underlying_type *;

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
[[nodiscard]] inline auto at(const mat_view &m, const mat_view::dimensions_type x,
                             const mat_view::dimensions_type y) noexcept -> const mat_view::underlying_type *;

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
[[nodiscard]] inline auto at(mat_view &m, const mat_view::dimensions_type x, const mat_view::dimensions_type y) noexcept
    -> T *;

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
[[nodiscard]] inline auto at(const mat_view &m, const mat_view::dimensions_type x,
                             const mat_view::dimensions_type y) noexcept -> const T *;

/*!
 * Fill the given matrix with a value. The given type must match the element_type, otherwise it will trigger undefined
 * behavior.
 */
template <typename T>
inline void fill(mat_view &m, const T value) noexcept;

/*!
 * Fill a part of the given matrix with a value. The given type must match the element_type, otherwise it will trigger
 * undefined behavior.
 */
template <typename T>
inline void fill(mat_view &m, const math::rectangle<mat_view::dimensions_type> rect, const T value) noexcept;

/*!
 * Blit the contents of one matrix into another
 */
inline void blit(const mat_view &src, mat_view &dst, const vector2<mat_view::dimensions_type> pos) noexcept;

/*!
 * Invert the given matrix vertically (flip upside-down)
 */
inline void invert_vertically(mat_view &m);

/*!
 * Create a new view on an existing view based on a given rectangle. This will essentially
 * crop the view on the matrix data without modifying or copying the data itself.
 * The given rectangle must fit within the dimensions of the view.
 * \param[in] view - A matrix view
 * \param[in] rect - A rectangle to 'crop' the view.
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(mat_view &view, const rectangle<int> &rect) noexcept -> mat_view;

/*!
 * Create a new view on an existing view based on a given mat3.
 * \param[in] mat - A 3x3 matrix
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(mat3 &mat) noexcept -> mat_view;

/*!
 * Create a new view on an existing view based on a given mat3.
 * \param[in] mat - A 4x4 matrix
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(mat4 &mat) noexcept -> mat_view;

/*!
 * Swizzle elements of all components in a mat_view. This can for example be used for rgb->bgr conversion
 * if the mat_view is an image.
 * \param[in] view - A mat view to be swizzled
 */
template <swizzle_component... components>
inline void swizzle(mat_view &view) noexcept;

namespace internal
{
template <typename T, swizzle_component component>
void swizzle_apply(const T *src, T *dst, const std::size_t index) noexcept;
} // namespace internal

} // namespace aeon::math

#include <aeon/math/impl/mat_view_impl.h>

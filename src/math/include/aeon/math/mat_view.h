// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <aeon/common/element_type.h>
#include <type_traits>

namespace aeon::math
{

template <typename T>
class vector2;

template <typename T>
class rectangle;

class mat3;

class mat4;

/*!
 * Class that represents a matrix of dynamic size that does not own the data
 * Unlike mat3 and mat4, data is laid out in row order
 */
template <typename T>
class mat_view_base
{
public:
    static_assert(std::is_same_v<T, std::byte> || std::is_same_v<T, const std::byte>,
                  "T must be std::byte or const std::byte.");

    using underlying_type = T;
    using value_type = std::remove_cv_t<underlying_type>;
    using dimensions_type = std::int32_t;
    using size_type = std::size_t;
    using ssize_type = std::ptrdiff_t;
    using stride_type = std::size_t;

    /*!
     * Create an empty matrix.
     */
    constexpr mat_view_base() noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Raw matrix data
     */
    constexpr explicit mat_view_base(const common::element_type type, const size2d<dimensions_type> dimensions,
                                     underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Raw matrix data
     */
    constexpr explicit mat_view_base(const common::element_type type, const dimensions_type width,
                                     const dimensions_type height, underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     */
    constexpr explicit mat_view_base(const common::element_type type, const size2d<dimensions_type> dimensions,
                                     const stride_type stride, underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     */
    constexpr explicit mat_view_base(const common::element_type type, const dimensions_type width,
                                     const dimensions_type height, const stride_type stride,
                                     underlying_type *data) noexcept;

    virtual ~mat_view_base() noexcept = default;

    constexpr mat_view_base(const mat_view_base &) noexcept = default;
    constexpr auto operator=(const mat_view_base &) noexcept -> mat_view_base & = default;

    constexpr mat_view_base(mat_view_base &&) noexcept = default;
    constexpr auto operator=(mat_view_base &&) noexcept -> mat_view_base & = default;

    /*!
     * Get the element type of the matrix.
     * \return The element type of the matrix
     */
    [[nodiscard]] constexpr auto element_type() const noexcept -> common::element_type;

    /*!
     * Get the width of the matrix.
     * \return The width of the matrix.
     */
    [[nodiscard]] constexpr auto width() const noexcept -> dimensions_type;

    /*!
     * Get the height of the matrix.
     * \return The height of the matrix.
     */
    [[nodiscard]] constexpr auto height() const noexcept -> dimensions_type;

    /*!
     * Get the size of the matrix (width, height).
     * \return The size of the matrix.
     */
    [[nodiscard]] constexpr auto dimensions() const noexcept -> size2d<dimensions_type>;

    /*!
     * Get the stride of the matrix. The stride is the amount of bytes between 2 lines/rows.
     * \return The stride of the matrix.
     */
    [[nodiscard]] constexpr auto stride() const noexcept -> stride_type;

    /*!
     * Get the size of the data based on the stride and height.
     * \return The size of the data in bytes (unsigned)
     */
    [[nodiscard]] constexpr auto size() const noexcept -> size_type;

    /*!
     * Get the size of the data based on the stride and height.
     * \return The size of the data in bytes (signed)
     */
    [[nodiscard]] constexpr auto ssize() const noexcept -> ssize_type;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] coord - A coordinate
     * \return Value based on the given column and row index.
     */
    [[nodiscard]] constexpr auto at(const vector2<dimensions_type> coord) noexcept -> value_type *;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] coord - A coordinate
     * \return Value based on the given column and row index.
     */
    [[nodiscard]] constexpr auto at(const vector2<dimensions_type> coord) const noexcept -> const value_type *;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] column_index - Column
     * \param[in] row_index - Row
     * \return Value based on the given column and row index.
     */
    [[nodiscard]] constexpr auto at(const dimensions_type column_index, const dimensions_type row_index) noexcept
        -> value_type *;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] column_index - Column
     * \param[in] row_index - Row
     * \return Value based on the given column and row index.
     */
    [[nodiscard]] constexpr auto at(const dimensions_type column_index, const dimensions_type row_index) const noexcept
        -> const value_type *;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] coord - A coordinate
     * \return Value based on the given column and row index.
     */
    template <typename U>
    [[nodiscard]] constexpr auto at(const vector2<dimensions_type> coord) noexcept -> U &;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] coord - A coordinate
     * \return Value based on the given column and row index.
     */
    template <typename U>
    [[nodiscard]] constexpr auto at(const vector2<dimensions_type> coord) const noexcept -> const U &;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] column_index - Column
     * \param[in] row_index - Row
     * \return Value based on the given column and row index.
     */
    template <typename U>
    [[nodiscard]] constexpr auto at(const dimensions_type column_index, const dimensions_type row_index) noexcept
        -> U &;

    /*!
     * Access a value within this matrix based on a given coordinate
     * \param[in] column_index - Column
     * \param[in] row_index - Row
     * \return Value based on the given column and row index.
     */
    template <typename U>
    [[nodiscard]] constexpr auto at(const dimensions_type column_index, const dimensions_type row_index) const noexcept
        -> const U &;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] constexpr auto data() noexcept -> value_type *;

    /*!
     * Get a pointer to the raw matrix data buffer
     * \return Pointer to raw data.
     */
    [[nodiscard]] constexpr auto data() const noexcept -> const value_type *;

protected:
    common::element_type type_;
    underlying_type *data_ptr_;
    size2d<dimensions_type> dimensions_;
    stride_type stride_;
};

using mat_view = mat_view_base<std::byte>;
using const_mat_view = mat_view_base<const std::byte>;

template <typename T>
inline constexpr auto operator+=(mat_view &lhs, const T rhs) noexcept -> mat_view &;

template <typename T>
inline constexpr auto operator-=(mat_view &lhs, const T rhs) noexcept -> mat_view &;

template <typename T>
inline constexpr auto operator*=(mat_view &lhs, const T rhs) noexcept -> mat_view &;

template <typename T>
inline constexpr auto operator/=(mat_view &lhs, const T rhs) noexcept -> mat_view &;

template <typename T, typename U>
inline constexpr auto operator==(const mat_view_base<T> &lhs, const mat_view_base<U> &rhs) noexcept -> bool;

template <typename T, typename U>
inline constexpr auto operator!=(const mat_view_base<T> &lhs, const mat_view_base<U> &rhs) noexcept -> bool;

/*!
 * Get the element type of the matrix.
 * \param[in] view - A matrix view
 * \return The element type of the matrix
 */
template <typename T>
[[nodiscard]] inline constexpr auto element_type(const mat_view_base<T> &view) noexcept;

/*!
 * Get the width of the given matrix view.
 * \param[in] view - A matrix view
 * \return The width of the matrix view.
 */
template <typename T>
[[nodiscard]] inline constexpr auto width(const mat_view_base<T> &view) noexcept;

/*!
 * Get the height of the given matrix view.
 * \param[in] view - A matrix view
 * \return The height of the matrix view.
 */
template <typename T>
[[nodiscard]] inline constexpr auto height(const mat_view_base<T> &view) noexcept;

/*!
 * Get the dimensions of the given matrix view (width, height).
 * \param[in] view - A matrix view
 * \return The dimensions of the matrix view.
 */
template <typename T>
[[nodiscard]] inline constexpr auto dimensions(const mat_view_base<T> &view) noexcept;

/*!
 * Get the stride of the given matrix view.
 * The stride is the amount of bytes between 2 lines/rows.
 * \param[in] view - A matrix view
 * \return The stride of the matrix view.
 */
template <typename T>
[[nodiscard]] inline constexpr auto stride(const mat_view_base<T> &view) noexcept;

/*!
 * Returns true if the data described by the given matrix view is laid out in memory in a
 * continuous fashion
 * (ie. stride=sizeof(T)*width)
 * \param[in] view - A mat view
 * \return True if the mat view's data is continuous.
 */
template <typename T>
[[nodiscard]] inline constexpr auto continuous(const mat_view_base<T> &view) noexcept;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given matrix view.
 * \param[in] view - A matrix view
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimensions of the matrix view.
 */
template <typename T>
[[nodiscard]] inline constexpr auto contains(const mat_view_base<T> &view,
                                             const vector2<typename mat_view_base<T>::dimensions_type> coord) noexcept;

/*!
 * Get the full size in bytes of the data described by the matrix view in
 * memory (stride * height).
 * \param[in] view - A matrix view
 * \return The size in bytes.
 */
template <typename T>
[[nodiscard]] inline constexpr auto size(const mat_view_base<T> &view) noexcept -> typename mat_view_base<T>::size_type;

/*!
 * Returns true if the matrix view is null. A matrix view is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] view - A matrix view
 * \return Returns true if the matrix view is null.
 */
template <typename T>
[[nodiscard]] inline constexpr auto null(const mat_view_base<T> &view) noexcept -> bool;

/*!
 * Returns true if the matrix view is valid. A matrix view is valid when it is not null.
 * \see null(const mat_view<T> &view)
 * \param[in] view - A matrix view
 * \return Returns true if the matrix view is valid.
 */
template <typename T>
[[nodiscard]] inline constexpr auto valid(const mat_view_base<T> &view) noexcept -> bool;

/*!
 * Create a new view on an existing view based on a given rectangle. This will essentially
 * crop the view on the matrix data without modifying or copying the data itself.
 * The given rectangle must fit within the dimensions of the view.
 * \param[in] view - A matrix view
 * \param[in] rect - A rectangle to 'crop' the view.
 * \return Returns A new view
 */
template <typename T>
[[nodiscard]] inline auto make_view(const mat_view_base<T> &view, const rectangle<int> &rect) noexcept
    -> mat_view_base<T>;

/*!
 * Create a new view on an existing view based on a given mat3.
 * \param[in] mat - A 3x3 matrix
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(mat3 &mat) noexcept -> mat_view;

/*!
 * Create a new view on an existing view based on a given mat3.
 * \param[in] mat - A 3x3 matrix
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(const mat3 &mat) noexcept -> const_mat_view;

/*!
 * Create a new view on an existing view based on a given mat3.
 * \param[in] mat - A 4x4 matrix
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(mat4 &mat) noexcept -> mat_view;

/*!
 * Create a new view on an existing view based on a given mat3.
 * \param[in] mat - A 4x4 matrix
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(const mat4 &mat) noexcept -> const_mat_view;

} // namespace aeon::math

#include <aeon/math/impl/mat_view_impl.h>
#include <aeon/math/impl/mat_view_operators_impl.h>

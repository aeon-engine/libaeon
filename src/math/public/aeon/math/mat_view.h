// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/imat.h>

namespace aeon::math
{

template <typename T>
class rectangle;

class mat3;

class mat4;

/*!
 * Class that represents a matrix of dynamic size that does not own the data
 * Unlike mat3 and mat4, data is laid out in row order
 */
class mat_view : public imat
{
public:
    using underlying_type = imat::underlying_type;
    using dimensions_type = imat::dimensions_type;
    using size_type = imat::size_type;
    using stride_type = imat::stride_type;

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

    ~mat_view() noexcept override = default;

    mat_view(const mat_view &) noexcept = default;
    auto operator=(const mat_view &) noexcept -> mat_view & = default;

    mat_view(mat_view &&) noexcept = default;
    auto operator=(mat_view &&) noexcept -> mat_view & = default;

    [[nodiscard]] auto element_type() const noexcept -> common::element_type override;
    [[nodiscard]] auto width() const noexcept -> dimensions_type override;
    [[nodiscard]] auto height() const noexcept -> dimensions_type override;
    [[nodiscard]] auto dimensions() const noexcept -> size2d<dimensions_type> override;
    [[nodiscard]] auto stride() const noexcept -> stride_type override;
    [[nodiscard]] auto size() const noexcept -> size_type override;
    [[nodiscard]] auto data() noexcept -> underlying_type * override;
    [[nodiscard]] auto data() const noexcept -> const underlying_type * override;

protected:
    common::element_type type_;
    underlying_type *data_ptr_;
    size2d<dimensions_type> dimensions_;
    stride_type stride_;
};

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

} // namespace aeon::math

#include <aeon/math/impl/mat_view_impl.h>

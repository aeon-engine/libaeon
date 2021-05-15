// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/mat_view.h>

namespace aeon::math
{

/*!
 * Class that represents a matrix of dynamic size
 * Unlike mat3 and mat4, data is laid out in row order
 */
class mat : public mat_view
{
public:
    using underlying_type = mat_view::underlying_type;
    using dimensions_type = mat_view::dimensions_type;
    using size_type = mat_view::size_type;
    using stride_type = mat_view::stride_type;

    /*!
     * Create an empty matrix.
     */
    mat() noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     */
    explicit mat(const common::element_type type, const size2d<dimensions_type> dimensions) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     */
    explicit mat(const common::element_type type, const dimensions_type width, const dimensions_type height) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit mat(const common::element_type type, const size2d<dimensions_type> dimensions,
                 const stride_type stride) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                 const stride_type stride) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const common::element_type type, const size2d<dimensions_type> dimensions,
                 std::vector<underlying_type> data) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                 std::vector<underlying_type> data) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions and
     * stride.
     */
    explicit mat(const common::element_type type, const size2d<dimensions_type> dimensions, const stride_type stride,
                 std::vector<underlying_type> data) noexcept;

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the matrix. The size of the data must match the given dimensions and
     * stride.
     */
    explicit mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                 const stride_type stride, std::vector<underlying_type> data) noexcept;

    /*!
     * Create a matrix with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const common::element_type type, const size2d<dimensions_type> dimensions,
                 const underlying_type *data);

    /*!
     * Create a matrix with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     */
    explicit mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                 const underlying_type *data);

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     * stride.
     */
    explicit mat(const common::element_type type, const size2d<dimensions_type> dimensions, const stride_type stride,
                 const underlying_type *data);

    /*!
     * Create a matrix with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the matrix. The size of the data must match the given dimensions.
     * stride.
     */
    explicit mat(const common::element_type type, const dimensions_type width, const dimensions_type height,
                 const stride_type stride, const underlying_type *data);

    ~mat() noexcept = default;

    mat(const mat &) = delete;
    auto operator=(const mat &) -> mat & = delete;

    mat(mat &&) noexcept = default;
    auto operator=(mat &&) noexcept -> mat & = default;

    explicit mat(const mat_view &other);
    auto operator=(const mat_view &other) -> mat &;

    /*!
     * Make a copy of the matrix. In order to avoid performance issues, the class is made
     * non-copyable. In order to copy the matrix, a call to clone() must be done explicitly.
     * \return A copy of this image.
     */
    [[nodiscard]] auto clone() const -> mat;

    /*!
     * Delete the matrix data and set the size and stride information to 0.
     */
    void clear() noexcept;

protected:
    void copy_from_pointer(const underlying_type *data);

    std::vector<underlying_type> data_;
};

/*!
 * Swizzle elements of all components in a mat_view. This can for example be used for grayscale->rgb conversion
 * if the mat_view is an image. The amount of components supplied determines the components of the output matrix.
 * \param[in] view - A mat view to be swizzled
 */
template <swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const mat_view &view) noexcept -> mat;

} // namespace aeon::math

#include <aeon/math/impl/mat_impl.h>

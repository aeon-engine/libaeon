// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Contains the image_view class.
 * An image view provides a way to access and modify image data.
 */

#pragma once

#include <aeon/imaging/format.h>
#include <aeon/math/mat_view.h>
#include <aeon/math/rectangle.h>

namespace aeon::imaging
{

/*!
 * An image view provides a way to access and modify image data.
 * An image_view does not own the data that it provides a view on.
 */
class image_view : public math::mat_view
{
public:
    using underlying_type = mat_view::underlying_type;
    using dimensions_type = mat_view::dimensions_type;
    using size_type = mat_view::size_type;
    using stride_type = mat_view::stride_type;

    /*!
     * Create an empty image_view.
     */
    image_view() noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] data - Raw matrix data
     */
    explicit image_view(const common::element_type type, const imaging::format format,
                        const math::size2d<dimensions_type> dimensions, underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] data - Raw matrix data
     */
    explicit image_view(const common::element_type type, const imaging::format format, const dimensions_type width,
                        const dimensions_type height, underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     */
    explicit image_view(const common::element_type type, const imaging::format format,
                        const math::size2d<dimensions_type> dimensions, const stride_type stride,
                        underlying_type *data) noexcept;

    /*!
     * Create a view based on the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the matrix.
     * \param[in] height - The height of the matrix.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Raw matrix data
     */
    explicit image_view(const common::element_type type, const imaging::format format, const dimensions_type width,
                        const dimensions_type height, const stride_type stride, underlying_type *data) noexcept;

    ~image_view() = default;

    image_view(const image_view &) = default;
    auto operator=(const image_view &) -> image_view & = default;

    image_view(image_view &&) noexcept = default;
    auto operator=(image_view &&) noexcept -> image_view & = default;

    /*!
     * Set the pixel format of the image.
     */
    void format(const imaging::format format) noexcept;

    /*!
     * Get the pixel format of the image.
     * \return The pixel format of the image.
     */
    [[nodiscard]] auto format() const noexcept -> imaging::format;

protected:
    imaging::format format_;
};

/*!
 * Get the pixel format of the given image.
 * \param[in] image - An image
 * \return The format of the image.
 */
[[nodiscard]] inline auto pixel_format(const image_view &image) noexcept -> imaging::format
{
    return image.format();
}

/*!
 * Create a new view on an existing view based on a given rectangle. This will essentially
 * crop the view on the image data without modifying or copying the data itself.
 * The given rectangle must fit within the dimensions of the view.
 * \param[in] view - An image view
 * \param[in] rect - A rectangle to 'crop' the view.
 * \return Returns A new view
 */
[[nodiscard]] inline auto make_view(image_view &view, const math::rectangle<int> &rect) noexcept -> image_view;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_view_impl.h>

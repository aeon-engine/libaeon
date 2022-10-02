// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

/*!
 * \file
 * \brief Class for image. This is mainly used to have a common base for images
 * of different templated pixel types.
 */

#pragma once

#include <aeon/imaging/image_view.h>
#include <vector>

/*!
 * Imaging library with support for reading, writing and filtering images of
 * different pixel formats.
 */
namespace aeon::imaging
{

/*!
 * An image. This class is owns the underlying pixel data and provides are view on
 * this data through image_view.
 */
class image : public image_view
{
public:
    using underlying_type = image::underlying_type;
    using dimensions_type = image::dimensions_type;
    using size_type = image::size_type;
    using stride_type = image::stride_type;

    /*!
     * Create an empty image.
     */
    image() noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the image.
     */
    explicit image(const common::element_type type, const imaging::format format,
                   const math::size2d<dimensions_type> dimensions) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     */
    explicit image(const common::element_type type, const imaging::format format, const dimensions_type width,
                   const dimensions_type height) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit image(const common::element_type type, const imaging::format format,
                   const math::size2d<dimensions_type> dimensions, const stride_type stride) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit image(const common::element_type type, const imaging::format format, const dimensions_type width,
                   const dimensions_type height, const stride_type stride) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the image.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions.
     */
    explicit image(const common::element_type type, const imaging::format format,
                   const math::size2d<dimensions_type> dimensions, std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions.
     */
    explicit image(const common::element_type type, const imaging::format format, const dimensions_type width,
                   const dimensions_type height, std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions and
     *                   stride.
     */
    explicit image(const common::element_type type, const imaging::format format,
                   const math::size2d<dimensions_type> dimensions, const stride_type stride,
                   std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions and
     *                   stride.
     */
    explicit image(const common::element_type type, const imaging::format format, const dimensions_type width,
                   const dimensions_type height, const stride_type stride, std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the image.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions.
     */
    explicit image(const common::element_type type, const imaging::format format,
                   const math::size2d<dimensions_type> dimensions, const underlying_type *data);

    /*!
     * Create an image with the given dimensions
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions.
     */
    explicit image(const common::element_type type, const imaging::format format, const dimensions_type width,
                   const dimensions_type height, const underlying_type *data);

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions and
     *                   stride.
     */
    explicit image(const common::element_type type, const imaging::format format,
                   const math::size2d<dimensions_type> dimensions, const stride_type stride,
                   const underlying_type *data);

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] type - The real format that the data represents (for example f32_4, 4 floats per element)
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb)
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions.
     *                   stride.
     */
    explicit image(const common::element_type type, const imaging::format format, const dimensions_type width,
                   const dimensions_type height, const stride_type stride, const underlying_type *data);

    /*!
     * Create an image with the given dimensions
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] dimensions - The width and height of the image.
     */
    explicit image(const imaging::format format, const math::size2d<dimensions_type> dimensions) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     */
    explicit image(const imaging::format format, const dimensions_type width, const dimensions_type height) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                   const stride_type stride) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     */
    explicit image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                   const stride_type stride) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions.
     */
    explicit image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                   std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions.
     */
    explicit image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                   std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions and
     *                   stride.
     */
    explicit image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                   const stride_type stride, std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be moved into the image. The size of the data must match the given dimensions and
     *                   stride.
     */
    explicit image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                   const stride_type stride, std::vector<underlying_type> data) noexcept;

    /*!
     * Create an image with the given dimensions
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions.
     */
    explicit image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                   const underlying_type *data);

    /*!
     * Create an image with the given dimensions
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions.
     */
    explicit image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                   const underlying_type *data);

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions and
     *                   stride.
     */
    explicit image(const imaging::format format, const math::size2d<dimensions_type> dimensions,
                   const stride_type stride, const underlying_type *data);

    /*!
     * Create an image with the given dimensions and data pointer.
     * \param[in] format - How the data should be logically interpreted (for example r32_float, r8g8b8a8_unorm or
     *                     b8g8r8a8_unorm_srgb). The element type is deducted from the given format.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     * \param[in] stride - The amount of bytes between the start of 2 lines/rows.
     * \param[in] data - Data to be copied into the image. The size of the data must match the given dimensions.
     *                   stride.
     */
    explicit image(const imaging::format format, const dimensions_type width, const dimensions_type height,
                   const stride_type stride, const underlying_type *data);

    /*!
     * Make a copy of the given image_view.
     */
    explicit image(const image_view &view);

    ~image() = default;

    image(const image &) = delete;
    auto operator=(const image &) -> image & = delete;

    image(image &&) noexcept = default;
    auto operator=(image &&) noexcept -> image & = default;

    /*!
     * Make a copy of the image. In order to avoid performance issues, the class is made
     * non-copyable. In order to copy the image, a call to clone() must be done
     * explicitly.
     * \return A copy of this image.
     */
    [[nodiscard]] auto clone() const -> image;

    /*!
     * Delete the image data and set the size and stride information to 0.
     */
    void clear() noexcept;

private:
    void copy_from_pointer(const underlying_type *data);

    std::vector<std::byte> data_;
};

/*!
 * Swizzle elements of all components in an image_view. This can for example be used for grayscale->rgb conversion.
 * The amount of components supplied determines the components of the output image. The encoding is kept.
 * \param[in] view - An image view to be swizzled

 */
template <math::swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const image_view &view) noexcept -> image;

/*!
 * Swizzle elements of all components in an image_view. This can for example be used for grayscale->rgb conversion.
 * The amount of components supplied determines the components of the output image.
 * \param[in] view - An image view to be swizzled
 * \param[in] format - The new pixel format of the output image
 */
template <math::swizzle_component... components>
[[nodiscard]] inline auto swizzle_copy(const image_view &view, const format format) noexcept -> image;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_impl.h>

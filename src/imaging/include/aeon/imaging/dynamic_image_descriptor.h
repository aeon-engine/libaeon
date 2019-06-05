// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

/*!
 * \file
 * \brief Class and functions for dynamic image descriptor. The image descriptor has
 * information about the encoding, size, stride and pixel format of a dynamic image.
 */

#pragma once

#include <aeon/imaging/dimension.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/image_descriptor.h>
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>

namespace aeon::imaging
{

/*!
 * The image descriptor has information about encoding, size, stride and pixel format of
 * a dynamic image.
 */
class dynamic_image_descriptor
{
public:
    /*!
     * Create an image descriptor based on given dimensions. The X and Y stride are
     * automatically calculated based on the given dimensions and encoding.
     * In this case it is assumed that the pixels are tightly packed.
     * \param[in] encoding - The pixel encoding
     * \param[in] dimensions - The width and height of the image.
     */
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const math::size2d<dimension> dimensions) noexcept;

    /*!
     * Create an image descriptor based on given width and height. The X and Y stride are
     * automatically calculated based on the given dimensions and encoding.
     * In this case it is assumed that the pixels are tightly packed.
     * \param[in] encoding - The pixel encoding.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     */
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const dimension width,
                                      const dimension height) noexcept;

    /*!
     * Create an image descriptor based on given dimensions and a vertical stride in bytes.
     * The X stride is automatically calculated based on the given encoding.
     * \param[in] encoding - The pixel encoding.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride_y - The amount of bytes between the start of 2 lines/rows.
     */
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const math::size2d<dimension> dimensions,
                                      const std::ptrdiff_t stride_y) noexcept;

    /*!
     * Create an image descriptor based on given dimensions and strides in bytes.
     * \param[in] encoding - The pixel encoding.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride_x - The amount of bytes between 2 pixels.
     * \param[in] stride_y - The amount of bytes between the start of 2 lines/rows.
     */
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const math::size2d<dimension> dimensions,
                                      const std::ptrdiff_t stride_x, const std::ptrdiff_t stride_y) noexcept;

    /*!
     * Create a dynamic image descriptor based a given regular descriptor.
     * This essentially converts a regular image_descriptor<T> into a dynamic_image_descriptor.
     * \param[in] descriptor - A regular image descriptor
     */
    template <typename T>
    explicit dynamic_image_descriptor(const image_descriptor<T> &descriptor) noexcept;

    ~dynamic_image_descriptor();

    dynamic_image_descriptor(const dynamic_image_descriptor &) noexcept = default;
    auto operator=(const dynamic_image_descriptor &) noexcept -> dynamic_image_descriptor & = default;
    dynamic_image_descriptor(dynamic_image_descriptor &&) noexcept = default;
    auto operator=(dynamic_image_descriptor &&) noexcept -> dynamic_image_descriptor & = default;

    /*!
     * Get the encoding of the image.
     * \return The encoding of the image.
     */
    [[nodiscard]] auto encoding() const noexcept -> pixel_encoding;

    /*!
     * Get the width of the image.
     * \return The width of the image.
     */
    [[nodiscard]] auto width() const noexcept -> dimension;

    /*!
     * Get the height of the image.
     * \return The height of the image.
     */
    [[nodiscard]] auto height() const noexcept -> dimension;

    /*!
     * Get the size of the image (width, height).
     * \return The size of the image.
     */
    [[nodiscard]] auto dimensions() const noexcept -> math::size2d<dimension>;

    /*!
     * Get the X stride of the image. The X stride is the amount of bytes between 2 pixels.
     * \return The X stride of the image.
     */
    [[nodiscard]] auto stride_x() const noexcept -> std::ptrdiff_t;

    /*!
     * Get the Y stride of the image. The Y stride is the amount of bytes between 2 lines/rows.
     * \return The Y stride of the image.
     */
    [[nodiscard]] auto stride_y() const noexcept -> std::ptrdiff_t;

private:
    pixel_encoding encoding_;
    math::size2d<dimension> dimensions_;
    std::ptrdiff_t stride_x_;
    std::ptrdiff_t stride_y_;
};

/*!
 * Returns true if the descriptor is null. A descriptor is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] descriptor - An image descriptor.
 * \return Returns true if the descriptor is null.
 */
[[nodiscard]] inline auto null(const dynamic_image_descriptor &descriptor) noexcept -> bool;

/*!
 * Returns true if the descriptor is valid. A descriptor is valid when it is not null.
 * \see null(const image_descriptor<T> &descriptor)
 * \param[in] descriptor - An image descriptor.
 * \return Returns true if the descriptor is valid.
 */
[[nodiscard]] inline auto valid(const dynamic_image_descriptor &descriptor) noexcept -> bool;

/*!
 * Get the encoding of the image as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The encoding of the image.
 */
[[nodiscard]] inline auto encoding(const dynamic_image_descriptor &descriptor) noexcept -> pixel_encoding;

/*!
 * Get the width of the image as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The width of the image.
 */
[[nodiscard]] inline auto width(const dynamic_image_descriptor &descriptor) noexcept -> dimension;

/*!
 * Get the height of the image as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The height of the image.
 */
[[nodiscard]] inline auto height(const dynamic_image_descriptor &descriptor) noexcept -> dimension;

/*!
 * Get the dimensions of the image (width, height) as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The dimensions of the image.
 */
[[nodiscard]] inline auto dimensions(const dynamic_image_descriptor &descriptor) noexcept -> math::size2d<dimension>;

/*!
 * Get the rectangle of the image (based on the dimensions) as described in an image descriptor.
 * The rectangle is constructed with top and left as 0, and right and bottom as width and height
 * respectively.
 * \param[in] descriptor - An image descriptor.
 * \return The rectangle surrounding the image.
 */
[[nodiscard]] inline auto rectangle(const dynamic_image_descriptor &descriptor) noexcept -> math::rectangle<dimension>;

/*!
 * Get the X stride of the image as described in an image descriptor.
 * The X stride is the amount of bytes between 2 pixels.
 * \param[in] descriptor - An image descriptor.
 * \return The X stride of the image.
 */
[[nodiscard]] inline auto stride_x(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

/*!
 * Get the Y stride of the image as described in an image descriptor.
 * The Y stride is the amount of bytes between 2 lines/rows.
 * \param[in] descriptor - An image descriptor.
 * \return The Y stride of the image.
 */
[[nodiscard]] inline auto stride_y(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

/*!
 * Returns true if the given image descriptor describes an image where all the data is layed out
 * in memory in a continuous fashion
 * (ie. stride_x=bytes_per_pixel(encoding) and stride_y=bytes_per_pixel(encoding)*width)
 * \param[in] descriptor - An image descriptor.
 * \return True if the image is continuous.
 */
[[nodiscard]] inline auto continuous(const dynamic_image_descriptor &descriptor) noexcept -> bool;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimenions of the image.
 */
[[nodiscard]] inline auto contains(const dynamic_image_descriptor &descriptor,
                                   const math::vector2<dimension> coord) noexcept -> bool;

/*!
 * Get the offset in bytes from the start of the buffer for a given coordinate. This value must be
 * added to the pointer containing the data to access the pixel at the given coordinate.
 * \param[in] coord - A coordinate (X, Y)
 * \param[in] descriptor - An image descriptor.
 * \return An offset for the given pixel coordinate.
 */
[[nodiscard]] inline auto at_offset(const math::vector2<dimension> coord,
                                    const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

/*!
 * Get the full size in bytes of the image in memory an image would take up as described with the
 * given image descriptor (stride_y * height)
 * \param[in] descriptor - An image descriptor.
 * \return The size in bytes.
 */
[[nodiscard]] inline auto size(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

/*!
 * Convert the given dynamic_image_descriptor to a regular image_descriptor<T>.
 * The given template argument T must match the encoding set in the dynamic image descriptor.
 * \param[in] descriptor - A dynamic image descriptor.
 * \return A regular typed image descriptor.
 */
template <typename T>
[[nodiscard]] inline auto descriptor(const dynamic_image_descriptor &descriptor) noexcept -> image_descriptor<T>;

[[nodiscard]] inline auto operator==(const dynamic_image_descriptor &lhs, const dynamic_image_descriptor &rhs) noexcept
    -> bool;

[[nodiscard]] inline auto operator!=(const dynamic_image_descriptor &lhs, const dynamic_image_descriptor &rhs) noexcept
    -> bool;

} // namespace aeon::imaging

#include <aeon/imaging/impl/dynamic_image_descriptor_impl.h>

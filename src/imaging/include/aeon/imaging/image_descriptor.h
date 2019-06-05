// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

/*!
 * \file
 * \brief Class and functions for image descriptor. The image descriptor has
 * information about the size, stride and pixel format of an image or image view.
 */

#pragma once

#include <aeon/imaging/dimension.h>
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <aeon/common/signed_sizeof.h>

namespace aeon::imaging
{

/*!
 * The image descriptor has information about the size, stride and pixel format of an
 * image or image view.
 *
 * The template type can be a pod type (uint8_t, uint16_t, float etc) or one of the
 * structs from the pixel_encoding header (rgb24, bgr24, rgba32, bgra32).
 */
template <typename T>
class image_descriptor
{

    template <typename U>
    friend class image_view_base;

public:
    /*!
     * Create an image descriptor based on given dimensions. The X and Y stride are
     * automatically calculated based on the given dimensions and pixel type.
     * In this case it is assumed that the pixels are tightly packed.
     * \param[in] dimensions - The width and height of the image.
     */
    explicit image_descriptor(const math::size2d<dimension> dimensions) noexcept;

    /*!
     * Create an image descriptor based on given width and height. The X and Y stride are
     * automatically calculated based on the given dimensions and pixel type.
     * In this case it is assumed that the pixels are tightly packed.
     * \param[in] width - The width of the image.
     * \param[in] height - The height of the image.
     */
    explicit image_descriptor(const dimension width, const dimension height) noexcept;

    /*!
     * Create an image descriptor based on given dimensions and a vertical stride in bytes.
     * The X stride is automatically calculated based on the given pixel type.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride_y - The amount of bytes between the start of 2 lines/rows.
     */
    explicit image_descriptor(const math::size2d<dimension> dimensions, const std::ptrdiff_t stride_y) noexcept;

    /*!
     * Create an image descriptor based on given dimensions and strides in bytes.
     * \param[in] dimensions - The width and height of the image.
     * \param[in] stride_x - The amount of bytes between 2 pixels.
     * \param[in] stride_y - The amount of bytes between the start of 2 lines/rows.
     */
    explicit image_descriptor(const math::size2d<dimension> dimensions, const std::ptrdiff_t stride_x,
                              const std::ptrdiff_t stride_y) noexcept;

    ~image_descriptor();

    image_descriptor(const image_descriptor &) noexcept = default;
    auto operator=(const image_descriptor &) noexcept -> image_descriptor & = default;
    image_descriptor(image_descriptor &&) noexcept = default;
    auto operator=(image_descriptor &&) noexcept -> image_descriptor & = default;

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
    /*!
     * Internal constructor to create a "null" descriptor.
     */
    image_descriptor() noexcept;

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
template <typename T>
[[nodiscard]] inline auto null(const image_descriptor<T> &descriptor) noexcept -> bool;

/*!
 * Returns true if the descriptor is valid. A descriptor is valid when it is not null.
 * \see null(const image_descriptor<T> &descriptor)
 * \param[in] descriptor - An image descriptor.
 * \return Returns true if the descriptor is valid.
 */
template <typename T>
[[nodiscard]] inline auto valid(const image_descriptor<T> &descriptor) noexcept -> bool;

/*!
 * Get the width of the image as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The width of the image.
 */
template <typename T>
[[nodiscard]] inline auto width(const image_descriptor<T> &descriptor) noexcept;

/*!
 * Get the height of the image as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The height of the image.
 */
template <typename T>
[[nodiscard]] inline auto height(const image_descriptor<T> &descriptor) noexcept;

/*!
 * Get the dimensions of the image (width, height) as described in an image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \return The dimensions of the image.
 */
template <typename T>
[[nodiscard]] inline auto dimensions(const image_descriptor<T> &descriptor) noexcept;

/*!
 * Get the rectangle of the image (based on the dimensions) as described in an image descriptor.
 * The rectangle is constructed with top and left as 0, and right and bottom as width and height
 * respectively.
 * \param[in] descriptor - An image descriptor.
 * \return The rectangle surrounding the image.
 */
template <typename T>
[[nodiscard]] inline auto rectangle(const image_descriptor<T> &descriptor) noexcept -> math::rectangle<dimension>;

/*!
 * Get the X stride of the image as described in an image descriptor.
 * The X stride is the amount of bytes between 2 pixels.
 * \param[in] descriptor - An image descriptor.
 * \return The X stride of the image.
 */
template <typename T>
[[nodiscard]] inline auto stride_x(const image_descriptor<T> &descriptor) noexcept;

/*!
 * Get the Y stride of the image as described in an image descriptor.
 * The Y stride is the amount of bytes between 2 lines/rows.
 * \param[in] descriptor - An image descriptor.
 * \return The Y stride of the image.
 */
template <typename T>
[[nodiscard]] inline auto stride_y(const image_descriptor<T> &descriptor) noexcept;

/*!
 * Returns true if the given image descriptor describes an image where all the data is layed out
 * in memory in a continuous fashion (ie. stride_x=sizeof(T) and stride_y=sizeof(T)*width)
 * \param[in] descriptor - An image descriptor.
 * \return True if the image is continuous.
 */
template <typename T>
[[nodiscard]] inline auto continuous(const image_descriptor<T> &descriptor) noexcept;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given image descriptor.
 * \param[in] descriptor - An image descriptor.
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimenions of the image.
 */
template <typename T>
[[nodiscard]] inline auto contains(const image_descriptor<T> &descriptor,
                                   const math::vector2<dimension> coord) noexcept;

/*!
 * Get the offset in bytes from the start of the buffer for a given coordinate. This value must be
 * added to the pointer containing the data to access the pixel at the given coordinate.
 * \param[in] coord - A coordinate (X, Y)
 * \param[in] descriptor - An image descriptor.
 * \return An offset for the given pixel coordinate.
 */
template <typename T>
[[nodiscard]] inline auto at_offset(const math::vector2<dimension> coord,
                                    const image_descriptor<T> &descriptor) noexcept -> std::ptrdiff_t;

/*!
 * Get the full size in bytes of the image in memory an image would take up as described with the
 * given image descriptor (stride_y * height)
 * \param[in] descriptor - An image descriptor.
 * \return The size in bytes.
 */
template <typename T>
[[nodiscard]] inline auto size(const image_descriptor<T> &descriptor) noexcept -> std::ptrdiff_t;

template <typename T>
inline auto operator==(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept;

template <typename T>
inline auto operator!=(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_descriptor_impl.h>

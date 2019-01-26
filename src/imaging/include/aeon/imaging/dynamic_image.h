// Copyright (c) 2012-2019 Robin Degen

/*!
 * \file
 * \brief Class for dynamic image. This image wraps the typed image<T> class for runtime use
 * so that differently typed images can be used in runtime (for example when loading image files)
 */

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/dynamic_image_descriptor.h>
#include <aeon/imaging/exceptions.h>
#include <aeon/common/assert.h>
#include <memory>

namespace aeon::imaging
{

/*!
 * A dynamic image. This image wraps the typed image<T> class for runtime use
 * so that differently typed images can be used in runtime (for example when loading image files)
 *
 * This class owns the underlying pixel data of the image.
 */
class dynamic_image
{
public:
    /*!
     * Create a new dynamic image. This will allocate memory based on the values set
     * in the image descriptor.
     * \param[in] dynamic_descriptor - A dynamic image descriptor.
     */
    explicit dynamic_image(const dynamic_image_descriptor &dynamic_descriptor);

    /*!
     * Move an existing image<T> to a dynamic image. This will take over ownership of
     * the internal image data by move semantics.
     * \param[in] image - An existing image.
     */
    template <typename T>
    explicit dynamic_image(image<T> &&image);

    /*!
     * Move an existing unique_ptr of image<T> to a dynamic image.
     * \param[in] image - An existing image unique_ptr.
     */
    template <typename T>
    explicit dynamic_image(std::unique_ptr<image<T>> image);

    ~dynamic_image();

    dynamic_image(const dynamic_image &) = delete;
    auto operator=(const dynamic_image &) -> dynamic_image & = delete;

    dynamic_image(dynamic_image &&) noexcept = default;
    auto operator=(dynamic_image &&) noexcept -> dynamic_image & = default;

    /*!
     * Get the descriptor of the image.
     * \return The descriptor of the image.
     */
    auto descriptor() const noexcept -> dynamic_image_descriptor;

    /*!
     * Get the internal typed image<T> from this dynamic image.
     * The given template argument T must match the encoding.
     * \return An image<T>.
     */
    template <typename T>
    auto get_image() noexcept -> image<T> &;

    /*!
     * Get the internal typed image<T> from this dynamic image.
     * The given template argument T must match the encoding.
     * \return An image<T>.
     */
    template <typename T>
    auto get_image() const noexcept -> const image<T> &;

    /*!
     * Access the raw internal data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A pointer to the raw data.
     */
    auto raw_data() noexcept -> std::byte *;

    /*!
     * Access the raw internal data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A const pointer to the raw data.
     */
    auto raw_data() const noexcept -> const std::byte *;

private:
    dynamic_image_descriptor dynamic_descriptor_;
    std::unique_ptr<image_base> image_;
};

/*!
 * Get the descriptor of the given image.
 * \param[in] image - A dynamic image
 * \return The descriptor of the image.
 */
inline auto descriptor(const dynamic_image &image) noexcept -> dynamic_image_descriptor;

/*!
 * Returns true if the dynamic image is null. An image is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] image - A dynamic image
 * \return Returns true if the image is null.
 */
inline auto null(const dynamic_image &image) noexcept -> bool;

/*!
 * Returns true if the dynamic image is valid. An image is valid when it is not null.
 * \see null(const image_descriptor<T> &descriptor)
 * \param[in] image - A dynamic image
 * \return Returns true if the image is valid.
 */
inline auto valid(const dynamic_image &image) noexcept -> bool;

/*!
 * Get the encoding of the given image.
 * \param[in] image - A dynamic image
 * \return The encoding of the image.
 */
inline auto encoding(const dynamic_image &image) noexcept -> pixel_encoding;

/*!
 * Get the width of the given image.
 * \param[in] image - A dynamic image
 * \return The width of the image.
 */
inline auto width(const dynamic_image &image) noexcept -> dimension;

/*!
 * Get the height of the given image.
 * \param[in] image - A dynamic image
 * \return The height of the image.
 */
inline auto height(const dynamic_image &image) noexcept -> dimension;

/*!
 * Get the dimensions of the given image (width, height).
 * \param[in] image - A dynamic image
 * \return The dimensions of the image.
 */
inline auto dimensions(const dynamic_image &image) noexcept -> math::size2d<dimension>;

/*!
 * Get the rectangle of the image (based on the dimensions).
 * The rectangle is constructed with top and left as 0, and right and bottom as width and height
 * respectively.
 * \param[in] image - A dynamic image
 * \return The rectangle surrounding the image.
 */
inline auto rectangle(const dynamic_image &image) noexcept -> math::rectangle<dimension>;

/*!
 * Get the X stride of the given image.
 * The X stride is the amount of bytes between 2 pixels.
 * \param[in] image - A dynamic image
 * \return The X stride of the image.
 */
inline auto stride_x(const dynamic_image &image) noexcept -> std::ptrdiff_t;

/*!
 * Get the Y stride of the given image.
 * The Y stride is the amount of bytes between 2 lines/rows.
 * \param[in] image - A dynamic image
 * \return The Y stride of the image.
 */
inline auto stride_y(const dynamic_image &image) noexcept -> std::ptrdiff_t;

/*!
 * Returns true if the data of the given image is layed out in memory in a continuous fashion
 * (ie. stride_x=bytes_per_pixel(encoding) and stride_y=bytes_per_pixel(encoding)*width)
 * \param[in] image - A dynamic image
 * \return True if the image is continuous.
 */
inline auto continuous(const dynamic_image &image) noexcept -> bool;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given image.
 * \param[in] image - A dynamic image
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimenions of the image.
 */
inline auto contains(const dynamic_image &image, const math::vector2<dimension> coord) noexcept -> bool;

/*!
 * Get the full size in bytes of the image in memory (stride_y * height).
 * \param[in] image - A dynamic image
 * \return The size in bytes.
 */
inline auto size(const dynamic_image &image) noexcept -> std::ptrdiff_t;

/*!
 * Get the typed image view for a given image to access the internal data.
 * The template argument T must match the encoding type.
 * \param[in] image - A dynamic image
 * \return The size in bytes.
 */
template <typename T>
inline auto view(dynamic_image &image) noexcept -> image_view<T> &;

/*!
 * Get the typed image view for a given image to access the internal data.
 * The template argument T must match the encoding type.
 * \param[in] image - A dynamic image
 * \return The size in bytes.
 */
template <typename T>
inline auto view(const dynamic_image &image) noexcept -> const image_view<T> &;

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A pointer to the raw data.
 */
inline auto raw_data(dynamic_image &image) noexcept -> std::byte *;

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A const pointer to the raw data.
 */
inline auto raw_data(const dynamic_image &image) noexcept -> const std::byte *;

#define process_image(img, func, ...)                                                                                  \
    [&]() {                                                                                                            \
        switch (encoding(img))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                func(view<std::uint8_t>(img), ##__VA_ARGS__);                                                          \
                return;                                                                                                \
            case pixel_encoding::unsigned16:                                                                           \
                func(view<std::uint16_t>(img), ##__VA_ARGS__);                                                         \
                return;                                                                                                \
            case pixel_encoding::unsigned32:                                                                           \
                func(view<std::uint32_t>(img), ##__VA_ARGS__);                                                         \
                return;                                                                                                \
            case pixel_encoding::float32:                                                                              \
                func(view<float>(img), ##__VA_ARGS__);                                                                 \
                return;                                                                                                \
            case pixel_encoding::rgb24:                                                                                \
                func(view<rgb24>(img), ##__VA_ARGS__);                                                                 \
                return;                                                                                                \
            case pixel_encoding::rgba32:                                                                               \
                func(view<rgba32>(img), ##__VA_ARGS__);                                                                \
                return;                                                                                                \
            case pixel_encoding::bgr24:                                                                                \
                func(view<bgr24>(img), ##__VA_ARGS__);                                                                 \
                return;                                                                                                \
            case pixel_encoding::bgra32:                                                                               \
                func(view<bgra32>(img), ##__VA_ARGS__);                                                                \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

#define process_image_to_copy(img, func, ...)                                                                          \
    [&]() -> dynamic_image {                                                                                           \
        switch (encoding(img))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                return dynamic_image{func(view<std::uint8_t>(img), ##__VA_ARGS__)};                                    \
            case pixel_encoding::unsigned16:                                                                           \
                return dynamic_image{func(view<std::uint16_t>(img), ##__VA_ARGS__)};                                   \
            case pixel_encoding::unsigned32:                                                                           \
                return dynamic_image{func(view<std::uint32_t>(img), ##__VA_ARGS__)};                                   \
            case pixel_encoding::float32:                                                                              \
                return dynamic_image{func(view<float>(img), ##__VA_ARGS__)};                                           \
            case pixel_encoding::rgb24:                                                                                \
                return dynamic_image{func(view<rgb24>(img), ##__VA_ARGS__)};                                           \
            case pixel_encoding::rgba32:                                                                               \
                return dynamic_image{func(view<rgba32>(img), ##__VA_ARGS__)};                                          \
            case pixel_encoding::bgr24:                                                                                \
                return dynamic_image{func(view<bgr24>(img), ##__VA_ARGS__)};                                           \
            case pixel_encoding::bgra32:                                                                               \
                return dynamic_image{func(view<bgra32>(img), ##__VA_ARGS__)};                                          \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

#define process_image_with_dst(src, dst, func, ...)                                                                    \
    [&]() {                                                                                                            \
        aeon_assert(encoding(src) == encoding(dst), "Encoding mismatch between source and destination.");              \
        switch (encoding(src))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                func(view<std::uint8_t>(src), view<std::uint8_t>(dst), ##__VA_ARGS__);                                 \
                return;                                                                                                \
            case pixel_encoding::unsigned16:                                                                           \
                func(view<std::uint16_t>(src), view<std::uint16_t>(dst), ##__VA_ARGS__);                               \
                return;                                                                                                \
            case pixel_encoding::unsigned32:                                                                           \
                func(view<std::uint32_t>(src), view<std::uint32_t>(dst), ##__VA_ARGS__);                               \
                return;                                                                                                \
            case pixel_encoding::float32:                                                                              \
                func(view<float>(src), view<float>(dst), ##__VA_ARGS__);                                               \
                return;                                                                                                \
            case pixel_encoding::rgb24:                                                                                \
                func(view<rgb24>(src), view<rgb24>(dst), ##__VA_ARGS__);                                               \
                return;                                                                                                \
            case pixel_encoding::rgba32:                                                                               \
                func(view<rgba32>(src), view<rgba32>(dst), ##__VA_ARGS__);                                             \
                return;                                                                                                \
            case pixel_encoding::bgr24:                                                                                \
                func(view<bgr24>(src), view<bgr24>(dst), ##__VA_ARGS__);                                               \
                return;                                                                                                \
            case pixel_encoding::bgra32:                                                                               \
                func(view<bgra32>(src), view<bgra32>(dst), ##__VA_ARGS__);                                             \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

} // namespace aeon::imaging

#include <aeon/imaging/impl/dynamic_image_impl.h>

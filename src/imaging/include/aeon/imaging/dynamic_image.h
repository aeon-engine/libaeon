// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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
     * Create a dynamic image from existing raw data.
     * \param[in] dynamic_descriptor - A dynamic image descriptor.
     * \param[in] data - Raw image data following the strides and dimensions from the descriptor
     */
    explicit dynamic_image(const dynamic_image_descriptor &dynamic_descriptor, std::vector<std::byte> &&data);

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
    [[nodiscard]] auto descriptor() const noexcept -> dynamic_image_descriptor;

    /*!
     * Get the internal typed image<T> from this dynamic image.
     * The given template argument T must match the encoding.
     * \return An image<T>.
     */
    template <typename T>
    [[nodiscard]] auto get_image() noexcept -> image<T> &;

    /*!
     * Get the internal typed image<T> from this dynamic image.
     * The given template argument T must match the encoding.
     * \return An image<T>.
     */
    template <typename T>
    [[nodiscard]] auto get_image() const noexcept -> const image<T> &;

    /*!
     * Access the raw internal data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A pointer to the raw data.
     */
    [[nodiscard]] auto raw_data() noexcept -> std::byte *;

    /*!
     * Access the raw internal data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A const pointer to the raw data.
     */
    [[nodiscard]] auto raw_data() const noexcept -> const std::byte *;

private:
    dynamic_image_descriptor dynamic_descriptor_;
    std::unique_ptr<image_base> image_;
};

/*!
 * Get the descriptor of the given image.
 * \param[in] image - A dynamic image
 * \return The descriptor of the image.
 */
[[nodiscard]] inline auto descriptor(const dynamic_image &image) noexcept -> dynamic_image_descriptor;

/*!
 * Returns true if the dynamic image is null. An image is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] image - A dynamic image
 * \return Returns true if the image is null.
 */
[[nodiscard]] inline auto null(const dynamic_image &image) noexcept -> bool;

/*!
 * Returns true if the dynamic image is valid. An image is valid when it is not null.
 * \see null(const image_descriptor<T> &descriptor)
 * \param[in] image - A dynamic image
 * \return Returns true if the image is valid.
 */
[[nodiscard]] inline auto valid(const dynamic_image &image) noexcept -> bool;

/*!
 * Get the encoding of the given image.
 * \param[in] image - A dynamic image
 * \return The encoding of the image.
 */
[[nodiscard]] inline auto encoding(const dynamic_image &image) noexcept -> pixel_encoding;

/*!
 * Get the width of the given image.
 * \param[in] image - A dynamic image
 * \return The width of the image.
 */
[[nodiscard]] inline auto width(const dynamic_image &image) noexcept -> dimension;

/*!
 * Get the height of the given image.
 * \param[in] image - A dynamic image
 * \return The height of the image.
 */
[[nodiscard]] inline auto height(const dynamic_image &image) noexcept -> dimension;

/*!
 * Get the dimensions of the given image (width, height).
 * \param[in] image - A dynamic image
 * \return The dimensions of the image.
 */
[[nodiscard]] inline auto dimensions(const dynamic_image &image) noexcept -> math::size2d<dimension>;

/*!
 * Get the rectangle of the image (based on the dimensions).
 * The rectangle is constructed with top and left as 0, and right and bottom as width and height
 * respectively.
 * \param[in] image - A dynamic image
 * \return The rectangle surrounding the image.
 */
[[nodiscard]] inline auto rectangle(const dynamic_image &image) noexcept -> math::rectangle<dimension>;

/*!
 * Get the stride of the given image.
 * The stride is the amount of bytes between 2 lines/rows.
 * \param[in] image - A dynamic image
 * \return The stride of the image.
 */
[[nodiscard]] inline auto stride(const dynamic_image &image) noexcept -> std::ptrdiff_t;

/*!
 * Returns true if the data of the given image is laid out in memory in a continuous fashion
 * (ie. stride=bytes_per_pixel(encoding)*width)
 * \param[in] image - A dynamic image
 * \return True if the image is continuous.
 */
[[nodiscard]] inline auto continuous(const dynamic_image &image) noexcept -> bool;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given image.
 * \param[in] image - A dynamic image
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimensions of the image.
 */
[[nodiscard]] inline auto contains(const dynamic_image &image, const math::vector2<dimension> coord) noexcept -> bool;

/*!
 * Get the full size in bytes of the image in memory (stride * height).
 * \param[in] image - A dynamic image
 * \return The size in bytes.
 */
[[nodiscard]] inline auto size(const dynamic_image &image) noexcept -> std::ptrdiff_t;

/*!
 * Get the typed image view for a given image to access the internal data.
 * The template argument T must match the encoding type.
 * \param[in] image - A dynamic image
 * \return The size in bytes.
 */
template <typename T>
[[nodiscard]] inline auto view(dynamic_image &image) noexcept -> image_view<T> &;

/*!
 * Get the typed image view for a given image to access the internal data.
 * The template argument T must match the encoding type.
 * \param[in] image - A dynamic image
 * \return The size in bytes.
 */
template <typename T>
[[nodiscard]] inline auto view(const dynamic_image &image) noexcept -> const image_view<T> &;

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A pointer to the raw data.
 */
[[nodiscard]] inline auto raw_data(dynamic_image &image) noexcept -> std::byte *;

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A const pointer to the raw data.
 */
[[nodiscard]] inline auto raw_data(const dynamic_image &image) noexcept -> const std::byte *;

template <template <typename> class T, typename... args_t>
inline void process_image(const dynamic_image &src, dynamic_image &dst, args_t &&...args)
{
    aeon_assert(encoding(src) == encoding(dst), "Encoding mismatch between source and destination.");
    switch (encoding(src))
    {
        case pixel_encoding::unsigned8:
            T<std::uint8_t>::process(view<std::uint8_t>(src), view<std::uint8_t>(dst), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::unsigned16:
            T<std::uint16_t>::process(view<std::uint16_t>(src), view<std::uint16_t>(dst),
                                      std::forward<args_t>(args)...);
            return;
        case pixel_encoding::unsigned32:
            T<std::uint32_t>::process(view<std::uint32_t>(src), view<std::uint32_t>(dst),
                                      std::forward<args_t>(args)...);
            return;
        case pixel_encoding::float32:
            T<float>::process(view<float>(src), view<float>(dst), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::rgb24:
            T<rgb24>::process(view<rgb24>(src), view<rgb24>(dst), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::rgba32:
            T<rgba32>::process(view<rgba32>(src), view<rgba32>(dst), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::bgr24:
            T<bgr24>::process(view<bgr24>(src), view<bgr24>(dst), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::bgra32:
            T<bgra32>::process(view<bgra32>(src), view<bgra32>(dst), std::forward<args_t>(args)...);
            return;
        default:
            throw imaging_exception{};
    }
}

template <template <typename> class T, typename... args_t>
inline void process_image(const dynamic_image &img, args_t &&...args)
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            T<std::uint8_t>::process(view<std::uint8_t>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::unsigned16:
            T<std::uint16_t>::process(view<std::uint16_t>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::unsigned32:
            T<std::uint32_t>::process(view<std::uint32_t>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::float32:
            T<float>::process(view<float>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::rgb24:
            T<rgb24>::process(view<rgb24>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::rgba32:
            T<rgba32>::process(view<rgba32>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::bgr24:
            T<bgr24>::process(view<bgr24>(img), std::forward<args_t>(args)...);
            return;
        case pixel_encoding::bgra32:
            T<bgra32>::process(view<bgra32>(img), std::forward<args_t>(args)...);
            return;
        default:
            throw imaging_exception{};
    }
}

template <template <typename> class T, typename... args_t>
inline auto process_image_to_copy(const dynamic_image &img, args_t &&...args) -> dynamic_image
{
    switch (encoding(img))
    {
        case pixel_encoding::unsigned8:
            return dynamic_image{T<std::uint8_t>::process(view<std::uint8_t>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::unsigned16:
            return dynamic_image{T<std::uint16_t>::process(view<std::uint16_t>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::unsigned32:
            return dynamic_image{T<std::uint32_t>::process(view<std::uint32_t>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::float32:
            return dynamic_image{T<float>::process(view<float>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::rgb24:
            return dynamic_image{T<rgb24>::process(view<rgb24>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::rgba32:
            return dynamic_image{T<rgba32>::process(view<rgba32>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::bgr24:
            return dynamic_image{T<bgr24>::process(view<bgr24>(img), std::forward<args_t>(args)...)};
        case pixel_encoding::bgra32:
            return dynamic_image{T<bgra32>::process(view<bgra32>(img), std::forward<args_t>(args)...)};
        default:
            throw imaging_exception{};
    }
}

} // namespace aeon::imaging

#include <aeon/imaging/impl/dynamic_image_impl.h>

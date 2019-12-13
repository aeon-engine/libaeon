// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

/*!
 * \file
 * \brief Class for image. This is mainly used to have a common base for images
 * of different templated pixel types.
 */

#pragma once

#include <aeon/imaging/image_view.h>
#include <vector>
#include <memory>

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
template <typename T>
class image : public image_view<T>
{
    friend class dynamic_image;

public:
    /*!
     * Create an empty image. This will create an image (and view) that is marked
     * as "null" and "invalid".
     */
    image();

    /*!
     * Create a new image. This will allocate memory based on the values set
     * in the image descriptor.
     */
    explicit image(const image_descriptor<T> &descriptor);

    /*!
     * Create a new image by copying existing pixel data from a vector.
     * The size of the vector must match the values set in the given image descriptor.
     */
    explicit image(const image_descriptor<T> &descriptor, const std::vector<std::byte> &data);

    /*!
     * Create a new image by moving existing pixel data from a vector (take over ownership).
     * The size of the vector must match the values set in the given image descriptor.
     */
    explicit image(const image_descriptor<T> &descriptor, std::vector<std::byte> &&data);

    virtual ~image();

    image(const image<T> &) = delete;
    auto operator=(const image<T> &) -> image<T> & = delete;

    image(image<T> &&o) noexcept = default;
    auto operator=(image<T> &&other) noexcept -> image<T> & = default;

    /*!
     * Make a copy of the image. In order to avoid performance issues, the class is made
     * non-copyable. In order to copy the image, a call to clone() must be done
     * explicitly.
     * \return A copy of this image.
     */
    [[nodiscard]] auto clone() const -> image<T>;

private:
    /*!
     * Internal helper method to transfer the data to a std::unique_ptr<image_base>.
     * This is used by dynamic_image to take over ownership of this class.
     *
     * After calling this method, this class should be considered moved and can no
     * longer be used.
     */
    [[nodiscard]] auto move_to_dynamic_image() -> std::unique_ptr<internal::image_base>;

    std::vector<std::byte> data_;
};

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A pointer to the raw data.
 */
template <typename T>
[[nodiscard]] inline auto raw_data(image<T> &image) noexcept -> std::byte *;

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A const pointer to the raw data.
 */
template <typename T>
[[nodiscard]] inline auto raw_data(const image<T> &image) noexcept -> const std::byte *;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_impl.h>

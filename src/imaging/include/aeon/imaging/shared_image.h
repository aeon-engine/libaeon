// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/imaging/image_view.h>
#include <aeon/imaging/image_base.h>
#include <aeon/common/shared_vector.h>
#include <vector>
#include <memory>

namespace aeon::imaging
{

/*!
 * An shared image. This class is owns the underlying pixel data and provides are view on
 * this data through image_view.
 *
 * The underlying data is stored in a shared_ptr to allow for easier sharing of data over thread boundries.
 */
template <typename T>
class shared_image : public image_view<T>, public image_base
{
    friend class dynamic_image;

public:
    /*!
     * Create an empty image. This will create an image (and view) that is marked
     * as "null" and "invalid".
     */
    shared_image();

    /*!
     * Create a new image. This will allocate memory based on the values set
     * in the image descriptor.
     */
    explicit shared_image(const image_descriptor<T> &descriptor);

    /*!
     * Create a new image by copying existing pixel data from a vector.
     * The size of the vector must match the values set in the given image descriptor.
     */
    explicit shared_image(const image_descriptor<T> &descriptor, const std::vector<std::byte> &data);

    /*!
     * Create a new image by moving existing pixel data from a vector (take over ownership).
     * The size of the vector must match the values set in the given image descriptor.
     */
    explicit shared_image(const image_descriptor<T> &descriptor, std::vector<std::byte> &&data);

    /*!
     * Create a new image by copying existing pixel data from a shared_vector.
     * The size of the vector must match the values set in the given image descriptor.
     */
    explicit shared_image(const image_descriptor<T> &descriptor, const common::shared_vector<std::byte> &data);

    virtual ~shared_image();

    shared_image(const shared_image<T> &) = default;
    auto operator=(const shared_image<T> &) -> shared_image<T> & = default;

    shared_image(shared_image<T> &&o) noexcept = default;
    auto operator=(shared_image<T> &&other) noexcept -> shared_image<T> & = default;

    /*!
     * Access the raw internal data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A pointer to the raw data.
     */
    [[nodiscard]] auto raw_data() noexcept -> std::byte * override;

    /*!
     * Access the raw internal data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A const pointer to the raw data.
     */
    [[nodiscard]] auto raw_data() const noexcept -> const std::byte * override;

    /*!
     * Access the raw internal shared data of this image without any bounds checks.
     * Extreme care must be taken when using this method to use the correct size, pixel type and strides.
     * \return A shared vector to the raw data.
     */
    [[nodiscard]] auto shared_data() const noexcept -> common::shared_vector<std::byte>;

private:
    /*!
     * Internal helper method to transfer the data to a std::unique_ptr<image_base>.
     * This is used by dynamic_image to take over ownership of this class.
     *
     * After calling this method, this class should be considered moved and can no
     * longer be used.
     */
    [[nodiscard]] auto move_to_dynamic_image() -> std::unique_ptr<image_base>;

    common::shared_vector<std::byte> data_;
};

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A pointer to the raw data.
 */
template <typename T>
[[nodiscard]] inline auto raw_data(shared_image<T> &image) noexcept -> std::byte *;

/*!
 * Access the raw internal data of an image without any bounds checks.
 * Extreme care must be taken when using this function to use the correct size, pixel type and strides.
 * \return A const pointer to the raw data.
 */
template <typename T>
[[nodiscard]] inline auto raw_data(const shared_image<T> &image) noexcept -> const std::byte *;

} // namespace aeon::imaging

#include <aeon/imaging/impl/shared_image_impl.h>

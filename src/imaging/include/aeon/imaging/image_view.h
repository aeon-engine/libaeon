// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Contains the image_view class.
 * An image view provides a way to access and modify image data.
 */

#pragma once

#include <aeon/imaging/image_descriptor.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <cstdint>
#include <cstddef>

namespace aeon::imaging
{

/*!
 * An image view provides a way to access and modify image data.
 * An image_view does not own the data that it provides a view on.
 */
template <typename T>
class image_view
{
public:
    /*!
     * Create a null (empty) image view (all values will be set to 0)
     */
    image_view() noexcept;

    /*!
     * Create a view based on the given descriptor and data pointer.
     * The data must match the pixel type, stride and sizes in the given descriptor.
     * \param[in] descriptor - An image descriptor
     * \param[in] data - Raw image data
     */
    explicit image_view(const image_descriptor<T> &descriptor, std::byte *data) noexcept;

    /*!
     * Create a view based on the given descriptor and data pointer.
     * The data must match the pixel type, stride and sizes in the given descriptor.
     * \param[in] descriptor - An image descriptor
     * \param[in] data - Raw image data
     */
    explicit image_view(const image_descriptor<T> &descriptor, const std::byte *data) noexcept;

    virtual ~image_view() noexcept;

    image_view(const image_view<T> &) = default;
    auto operator=(const image_view<T> &) -> image_view<T> & = default;

    image_view(image_view<T> &&) noexcept = default;
    auto operator=(image_view<T> &&) noexcept -> image_view<T> & = default;

    /*!
     * Get the descriptor of the image view.
     * \return The descriptor of the image view.
     */
    [[nodiscard]] auto descriptor() const noexcept -> image_descriptor<T>;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    [[nodiscard]] auto data() noexcept -> T *;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    [[nodiscard]] auto data() const noexcept -> const T *;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    template <typename U>
    [[nodiscard]] auto data() noexcept -> U *;

    /*!
     * Get a pointer to the raw image data.
     * The descriptor should be used to get information about the layout in memory.
     * \return Pointer to raw image data.
     */
    template <typename U>
    [[nodiscard]] auto data() const noexcept -> const U *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    [[nodiscard]] auto data(const math::vector2<dimension> coord) noexcept -> T *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    [[nodiscard]] auto data(const math::vector2<dimension> coord) const noexcept -> const T *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    template <typename U>
    [[nodiscard]] auto data(const math::vector2<dimension> coord) noexcept -> U *;

    /*!
     * Get a pointer to the raw image data at the pixel offset of the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * The descriptor should be used to get information about the layout in memory.
     * \param[in] coord - A pixel coordinate
     * \return Pointer to raw image data.
     */
    template <typename U>
    [[nodiscard]] auto data(const math::vector2<dimension> coord) const noexcept -> const U *;

    /*!
     * Get a reference to a pixel at the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * \param[in] coord - A pixel coordinate
     * \return A reference to a pixel at the given coordinate.
     */
    [[nodiscard]] auto at(const math::vector2<dimension> coord) noexcept -> T &;

    /*!
     * Get a reference to a pixel at the given coordinate.
     * The coordinate must fit within the dimensions of the image.
     * \param[in] coord - A pixel coordinate
     * \return A reference to a pixel at the given coordinate.
     */
    [[nodiscard]] auto at(const math::vector2<dimension> coord) const noexcept -> const T &;

protected:
    /*!
     * Internal constructor used by image<T>. This constructor is used
     * when the data pointer is not known up front since the data needs to
     * be copied first. The image class will set the data pointer after copying
     * the image data.
     */
    explicit image_view(const image_descriptor<T> &descriptor) noexcept;

    image_descriptor<T> descriptor_;
    std::byte *data_ptr_;
};

/*!
 * Get the descriptor of the given image view
 * \param[in] view - An image view
 * \return The descriptor of the image view.
 */
template <typename T>
[[nodiscard]] inline auto descriptor(const image_view<T> &view) noexcept -> image_descriptor<T>;

/*!
 * Get the width of the given image view.
 * \param[in] view - An image view
 * \return The width of the image view.
 */
template <typename T>
[[nodiscard]] inline auto width(const image_view<T> &view) noexcept;

/*!
 * Get the height of the given image view.
 * \param[in] view - An image view
 * \return The height of the image view.
 */
template <typename T>
[[nodiscard]] inline auto height(const image_view<T> &view) noexcept;

/*!
 * Get the dimensions of the given image view (width, height).
 * \param[in] view - An image view
 * \return The dimensions of the image view.
 */
template <typename T>
[[nodiscard]] inline auto dimensions(const image_view<T> &view) noexcept;

/*!
 * Get the rectangle of the image view (based on the dimensions).
 * The rectangle is constructed with top and left as 0, and right and bottom as width and height
 * respectively.
 * \param[in] view - An image view
 * \return The rectangle surrounding the image view.
 */
template <typename T>
[[nodiscard]] inline auto rectangle(const image_view<T> &view) noexcept;

/*!
 * Get the stride of the given image view.
 * The stride is the amount of bytes between 2 lines/rows.
 * \param[in] view - An image view
 * \return The stride of the image view.
 */
template <typename T>
[[nodiscard]] inline auto stride(const image_view<T> &view) noexcept;

/*!
 * Returns true if the data described by the given image view is laid out in memory in a
 * continuous fashion
 * (ie. stride=bytes_per_pixel(encoding)*width)
 * \param[in] view - An image view
 * \return True if the image view's data is continuous.
 */
template <typename T>
[[nodiscard]] inline auto continuous(const image_view<T> &view) noexcept;

/*!
 * Returns true if the given coordinate falls within the dimensions of the given image view.
 * \param[in] view - An image view
 * \param[in] coord - A coordinate (X, Y)
 * \return True if the coordinate is within the dimensions of the image view.
 */
template <typename T>
[[nodiscard]] inline auto contains(const image_view<T> &view, const math::vector2<dimension> coord) noexcept;

/*!
 * Get the full size in bytes of the data described by the image view in
 * memory (stride * height).
 * \param[in] view - An image view
 * \return The size in bytes.
 */
template <typename T>
[[nodiscard]] inline auto size(const image_view<T> &view) noexcept -> std::ptrdiff_t;

/*!
 * Returns true if the image view is null. An image view is null when
 * all it's internal values (width, height, stride) are set to 0.
 * \param[in] view - An image view
 * \return Returns true if the image view is null.
 */
template <typename T>
[[nodiscard]] inline auto null(const image_view<T> &view) noexcept -> bool;

/*!
 * Returns true if the image view is valid. An image view is valid when it is not null.
 * \see null(const image_descriptor<T> &descriptor)
 * \param[in] view - An image view
 * \return Returns true if the image view is valid.
 */
template <typename T>
[[nodiscard]] inline auto valid(const image_view<T> &view) noexcept -> bool;

/*!
 * Create a new view on an existing view based on a given rectangle. This will essentially
 * crop the view on the image data without modifying or copying the data itself.
 * The given rectangle must fit within the dimensions of the view.
 * \param[in] view - An image view
 * \param[in] rect - A rectangle to 'crop' the view.
 * \return Returns A new view
 */
template <typename T>
[[nodiscard]] inline auto make_view(const image_view<T> &view, const math::rectangle<int> &rect) noexcept
    -> image_view<T>;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_view_impl.h>

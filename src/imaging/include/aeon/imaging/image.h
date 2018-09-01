/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
 * Base class for image. This is mainly used to have a common base for images
 * of different templated pixel types.
 */
class image_base
{
public:
    virtual ~image_base() = default;

    image_base(const image_base &) = delete;
    auto operator=(const image_base &) -> image_base & = delete;

    image_base(image_base &&) noexcept = default;
    auto operator=(image_base &&) noexcept -> image_base & = default;

protected:
    image_base() = default;
};

/*!
 * An image. This class is owns the underlaying pixel data and provides are view on
 * this data through image_view.
 */
template <typename T>
class image : public image_view<T>, public image_base
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
    auto clone() const -> image<T>;

private:
    /*!
     * Internal helper method to transfer the data to a std::unique_ptr<image_base>.
     * This is used by dynamic_image to take over ownership of this class.
     *
     * After calling this method, this class should be considered moved and can no
     * longer be used.
     */
    auto move_to_dynamic_image() -> std::unique_ptr<image_base>;

    std::vector<std::byte> data_;
};

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_impl.h>

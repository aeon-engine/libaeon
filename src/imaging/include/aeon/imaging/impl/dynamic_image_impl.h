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

#pragma once

#include <aeon/imaging/pixel_encoding_traits.h>
#include <aeon/common/assert.h>
#include <cstdint>

namespace aeon::imaging
{

template <typename T>
inline dynamic_image::dynamic_image(image<T> &&image)
    : image_{image.move_to_dynamic_image()}
    , encoding_{pixel_encoding_trait<T>::encoding()}
{
}

template <typename T>
inline dynamic_image::dynamic_image(std::unique_ptr<image<T>> image)
    : image_{std::move(image)}
    , encoding_{pixel_encoding_trait<T>::encoding()}
{
}

inline dynamic_image::~dynamic_image() = default;

inline auto dynamic_image::encoding() const noexcept -> pixel_encoding
{
    return encoding_;
}

template <typename T>
inline auto dynamic_image::get_image() noexcept -> imaging::image<T> &
{
    aeon_assert(pixel_encoding_trait<T>::encoding() == encoding_, "Encoding mismatch.");
    return *static_cast<image<T> *>(image_.get());
}

template <typename T>
inline auto dynamic_image::get_image() const noexcept -> const imaging::image<T> &
{
    aeon_assert(pixel_encoding_trait<T>::encoding() == encoding_, "Encoding mismatch.");
    return *static_cast<const image<T> *>(image_.get());
}

inline auto encoding(const dynamic_image &image) noexcept -> pixel_encoding
{
    return image.encoding();
}

template <typename T>
inline auto view(dynamic_image &image) noexcept -> image_view<T> &
{
    return image.get_image<T>();
}

template <typename T>
inline auto view(const dynamic_image &image) noexcept -> const image_view<T> &
{
    return image.get_image<T>();
}

} // namespace aeon::imaging

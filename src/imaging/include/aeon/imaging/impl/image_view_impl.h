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

#include <aeon/common/assert.h>

namespace aeon::imaging
{

template <typename T>
inline image_view<T>::image_view() noexcept
    : image_view_base<T>{}
    , data_ptr_{}
{
}

template <typename T>
inline image_view<T>::image_view(const image_descriptor<T> descriptor, std::byte *data) noexcept
    : image_view_base<T>{descriptor}
    , data_ptr_{data}
{
    aeon_assert(data, "Data is nullptr.");
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view<T>::image_view(const image_descriptor<T> descriptor, const std::byte *data) noexcept
    : image_view_base<T>{descriptor}
    , data_ptr_{const_cast<std::byte *>(data)}
{
    aeon_assert(data, "Data is nullptr.");
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view<T>::image_view(const image_descriptor<T> descriptor) noexcept
    : image_view_base<T>{descriptor}
    , data_ptr_{}
{
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view<T>::~image_view() noexcept = default;

template <typename T>
inline auto image_view<T>::data() noexcept -> T *
{
    return reinterpret_cast<T *>(data_ptr_);
}

template <typename T>
inline auto image_view<T>::data() const noexcept -> const T *
{
    return reinterpret_cast<const T *>(data_ptr_);
}

template <typename T>
template <typename U>
inline auto image_view<T>::data() noexcept -> U *
{
    return reinterpret_cast<U *>(data_ptr_);
}

template <typename T>
template <typename U>
inline auto image_view<T>::data() const noexcept -> const U *
{
    return reinterpret_cast<const U *>(data_ptr_);
}

template <typename T>
inline auto image_view<T>::data(const math::vector2<dimension> coord) noexcept -> T *
{
    aeon_assert(contains(image_view_base<T>::descriptor_, coord), "Given coordinate was out of bounds.");
    return reinterpret_cast<T *>(data_ptr_ + at_offset(coord, image_view_base<T>::descriptor_));
}

template <typename T>
inline auto image_view<T>::data(const math::vector2<dimension> coord) const noexcept -> const T *
{
    aeon_assert(contains(image_view_base<T>::descriptor_, coord), "Given coordinate was out of bounds.");
    return reinterpret_cast<const T *>(data_ptr_ + at_offset(coord, image_view_base<T>::descriptor_));
}

template <typename T>
template <typename U>
inline auto image_view<T>::data(const math::vector2<dimension> coord) noexcept -> U *
{
    return reinterpret_cast<U *>(data(coord));
}

template <typename T>
template <typename U>
inline auto image_view<T>::data(const math::vector2<dimension> coord) const noexcept -> const U *
{
    return reinterpret_cast<const U *>(data(coord));
}

template <typename T>
inline auto image_view<T>::at(const math::vector2<dimension> coord) noexcept -> T &
{
    return *data(coord);
}

template <typename T>
inline auto image_view<T>::at(const math::vector2<dimension> coord) const noexcept -> const T &
{
    return *data(coord);
}

template <typename T>
inline auto null(const image_view<T> &view) noexcept -> bool
{
    return null(descriptor(view)) || view.data() == nullptr;
}

template <typename T>
inline auto valid(const image_view<T> &view) noexcept -> bool
{
    return !null(view);
}

template <typename T>
inline auto make_view(const image_view<T> &view, const math::rectangle<int> &rect) noexcept -> image_view<T>
{
    aeon_assert(math::contains(rect, rectangle(view)), "View rectangle does not fit within image.");

    const image_descriptor<T> descriptor{math::size(rect), stride_x(view), stride_y(view)};
    const auto data_offset =
        view.template data<std::byte>() + math::top(rect) * stride_y(view) + math::left(rect) * stride_x(view);
    return image_view{descriptor, data_offset};
}

} // namespace aeon::imaging

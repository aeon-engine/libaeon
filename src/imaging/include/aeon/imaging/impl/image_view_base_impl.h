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
inline image_view_base<T>::image_view_base() noexcept
    : descriptor_{}
{
}

template <typename T>
inline image_view_base<T>::image_view_base(const image_descriptor<T> &descriptor) noexcept
    : descriptor_{descriptor}
{
    aeon_assert(valid(descriptor), "Descriptor must be valid.");
}

template <typename T>
inline image_view_base<T>::~image_view_base() noexcept = default;

template <typename T>
inline auto image_view_base<T>::descriptor() const noexcept -> image_descriptor<T>
{
    return descriptor_;
}

template <typename T>
inline auto descriptor(const image_view_base<T> &view) noexcept -> image_descriptor<T>
{
    return view.descriptor();
}

template <typename T>
inline auto width(const image_view_base<T> &view) noexcept
{
    return width(descriptor(view));
}

template <typename T>
inline auto height(const image_view_base<T> &view) noexcept
{
    return height(descriptor(view));
}

template <typename T>
inline auto dimensions(const image_view_base<T> &view) noexcept
{
    return dimensions(descriptor(view));
}

template <typename T>
inline auto rectangle(const image_view_base<T> &view) noexcept
{
    return rectangle(descriptor(view));
}

template <typename T>
inline auto stride_x(const image_view_base<T> &view) noexcept
{
    return stride_x(descriptor(view));
}

template <typename T>
inline auto stride_y(const image_view_base<T> &view) noexcept
{
    return stride_y(descriptor(view));
}

template <typename T>
inline auto continuous(const image_view_base<T> &view) noexcept
{
    return continuous(descriptor(view));
}

template <typename T>
inline auto contains(const image_view_base<T> &view, const math::vector2<dimension> coord) noexcept
{
    return contains(descriptor(view), coord);
}

template <typename T>
inline auto size(const image_view_base<T> &view) noexcept -> std::ptrdiff_t
{
    return size(descriptor(view));
}

} // namespace aeon::imaging

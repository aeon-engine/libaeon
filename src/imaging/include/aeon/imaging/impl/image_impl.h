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

namespace aeon::imaging
{

template <typename T>
inline image<T>::image(const image_descriptor<T> descriptor)
    : data_(size(descriptor))
    , view_{descriptor, data_.data()}
{
}

template <typename T>
inline image<T>::image(const image_descriptor<T> descriptor, const std::vector<std::byte> &data)
    : data_{data}
    , view_{descriptor, data_.data()}
{
}

template <typename T>
inline image<T>::image(const image_descriptor<T> descriptor, std::vector<std::byte> &&data)
    : data_{std::move(data)}
    , view_{descriptor, data_.data()}
{
}

template <typename T>
inline image<T>::~image() = default;

template <typename T>
inline image<T>::operator image_view<T> &() noexcept
{
    return view_;
}

template <typename T>
inline image<T>::operator const image_view<T> &() const noexcept
{
    return view_;
}

template <typename T>
inline auto image<T>::view() noexcept -> image_view<T> &
{
    return view_;
}

template <typename T>
inline auto image<T>::view() const noexcept -> const image_view<T> &
{
    return view_;
}

template <typename T>
inline auto image<T>::clone() const -> image<T>
{
    return image<T>{descriptor(view_), data_};
}

template <typename T>
inline auto image<T>::move_to_dynamic_image() -> std::unique_ptr<image_base>
{
    return std::make_unique<image<T>>(descriptor(view_), std::move(data_));
}

template <typename T>
inline auto view(image<T> &image) noexcept -> image_view<T> &
{
    return image.view();
}

template <typename T>
inline auto view(const image<T> &image) noexcept -> const image_view<T> &
{
    return image.view();
}

template <typename T>
inline auto descriptor(const image<T> &image) noexcept -> image_descriptor<T>
{
    return descriptor(view(image));
}

template <typename T>
inline auto width(const image<T> &image) noexcept
{
    return width(view(image));
}

template <typename T>
inline auto height(const image<T> &image) noexcept
{
    return height(view(image));
}

template <typename T>
inline auto dimensions(const image<T> &image) noexcept
{
    return dimensions(view(image));
}

template <typename T>
inline auto stride_x(const image<T> &image) noexcept
{
    return stride_x(view(image));
}

template <typename T>
inline auto stride_y(const image<T> &image) noexcept
{
    return stride_y(view(image));
}

template <typename T>
inline auto continuous(const image<T> &image) noexcept
{
    return continuous(view(image));
}

template <typename T>
inline auto size(const image<T> &image) noexcept -> std::ptrdiff_t
{
    return size(view(image));
}

} // namespace aeon::imaging

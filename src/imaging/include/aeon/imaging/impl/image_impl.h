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
inline image<T>::image()
    : image_view<T>{}
    , data_{}
{
}

template <typename T>
inline image<T>::image(const image_descriptor<T> &descriptor)
    : image_view<T>{descriptor}
    , data_(size(descriptor))
{
    image_view<T>::data_ptr_ = data_.data();
}

template <typename T>
inline image<T>::image(const image_descriptor<T> &descriptor, const std::vector<std::byte> &data)
    : image_view<T>{descriptor}
    , data_{data}
{
    image_view<T>::data_ptr_ = data_.data();
}

template <typename T>
inline image<T>::image(const image_descriptor<T> &descriptor, std::vector<std::byte> &&data)
    : image_view<T>{descriptor}
    , data_{std::move(data)}
{
    image_view<T>::data_ptr_ = data_.data();
}

template <typename T>
inline image<T>::~image() = default;

template <typename T>
inline auto image<T>::clone() const -> image<T>
{
    return image{image_view<T>::descriptor_, data_};
}

template <typename T>
inline auto image<T>::move_to_dynamic_image() -> std::unique_ptr<image_base>
{
    return std::make_unique<image<T>>(image_view<T>::descriptor_, std::move(data_));
}

} // namespace aeon::imaging

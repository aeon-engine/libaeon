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

#include <aeon/imaging/pixel_iterator.h>
#include <aeon/imaging/scanline_iterator.h>
#include <aeon/imaging/iterator.h>
#include <aeon/imaging/descriptor.h>
#include <vector>
#include <cstdint>
#include <cassert>

namespace aeon::imaging
{

class image
{
public:
    explicit image(const descriptor descriptor);
    explicit image(const descriptor descriptor, std::vector<std::uint8_t> &&data);
    explicit image(const descriptor descriptor, const std::vector<std::uint8_t> &data);
    explicit image(const descriptor descriptor, void *data);

    ~image() = default;

    image(const image &) = delete;
    auto operator=(const image &) -> image & = delete;

    image(image &&o) noexcept = default;
    auto operator=(image &&other) noexcept -> image & = default;

    auto get_descriptor() const noexcept -> descriptor;

    auto data() noexcept -> void *;
    auto data() const noexcept -> const void *;

    template <typename T>
    auto data() noexcept -> T *;

    template <typename T>
    auto data() const noexcept -> const T *;

    auto size() const noexcept -> std::size_t;

    auto clone() const -> image;

    auto begin() noexcept -> iterator<std::uint8_t>;
    auto end() noexcept -> iterator<std::uint8_t>;

    template <typename pixel_type_t>
    auto pixel_iterator() noexcept -> pixel_type_iterator<pixel_type_t>;

    auto pixel(const dimension x, const dimension y) noexcept -> void *;
    auto pixel(const dimension x, const dimension y) const noexcept -> const void *;

    template <typename T>
    auto pixel(const dimension x, const dimension y) noexcept -> T *;

    template <typename T>
    auto pixel(const dimension x, const dimension y) const noexcept -> const T *;

private:
    descriptor descriptor_;
    std::vector<std::uint8_t> data_;
};

template <typename T>
auto image::data() noexcept -> T *
{
    return reinterpret_cast<T *>(data());
}

template <typename T>
auto image::data() const noexcept -> const T *
{
    return reinterpret_cast<const T *>(data());
}

template <typename pixel_type_t>
auto image::pixel_iterator() noexcept -> pixel_type_iterator<pixel_type_t>
{
    const auto bpp = bytes_per_pixel(descriptor_);
    return pixel_type_iterator<pixel_type_t>{data_.data(), data_.data() + data_.size(), bpp};
}

inline auto image::pixel(const dimension x, const dimension y) noexcept -> void *
{
    assert(x < width(descriptor_));
    assert(y < height(descriptor_));
    return data_.data() + pixel_offset(x, y, descriptor_);
}

inline auto image::pixel(const dimension x, const dimension y) const noexcept -> const void *
{
    assert(x < width(descriptor_));
    assert(y < height(descriptor_));
    return data_.data() + pixel_offset(x, y, descriptor_);
}

template <typename T>
inline auto image::pixel(const dimension x, const dimension y) noexcept -> T *
{
    assert(x < width(descriptor_));
    assert(y < height(descriptor_));
    return reinterpret_cast<T *>(data_.data() + pixel_offset(x, y, descriptor_));
}

template <typename T>
inline auto image::pixel(const dimension x, const dimension y) const noexcept -> const T *
{
    assert(x < width(descriptor_));
    assert(y < height(descriptor_));
    return reinterpret_cast<const T *>(data_.data() + pixel_offset(x, y, descriptor_));
}

inline auto data(image &image) noexcept
{
    return image.data();
}

template <typename pixel_type_t>
inline auto data(image &image) noexcept -> pixel_type_t *
{
    return image.data<pixel_type_t>();
}

inline auto data(const image &image) noexcept
{
    return image.data();
}

template <typename pixel_type_t>
inline auto data(const image &image) noexcept -> const pixel_type_t *
{
    return image.data<pixel_type_t>();
}

inline auto size(const image &image) noexcept
{
    return image.size();
}

inline auto width(const image &image) noexcept
{
    return width(image.get_descriptor());
}

inline auto height(const image &image) noexcept
{
    return height(image.get_descriptor());
}

inline auto stride(const image &image) noexcept
{
    return stride(image.get_descriptor());
}

inline auto encoding(const image &image) noexcept
{
    return encoding(image.get_descriptor());
}

inline auto bytes_per_pixel(const image &image) noexcept
{
    return bytes_per_pixel(image.get_descriptor());
}

inline auto dimensions(const image &image) noexcept
{
    return dimensions(image.get_descriptor());
}

inline auto clone(const image &image) noexcept
{
    return image.clone();
}

inline auto continuous(const image &image) noexcept
{
    return continuous(image.get_descriptor());
}

inline auto contains(const image &image, const dimension x, const dimension y) noexcept
{
    return contains(image.get_descriptor(), x, y);
}

inline auto pixel_iterator(image &image) noexcept
{
    return image.pixel_iterator<std::uint8_t>();
}

template <typename pixel_type_t>
inline auto pixel_iterator(image &image) noexcept
{
    return image.pixel_iterator<pixel_type_t>();
}

} // namespace aeon::imaging

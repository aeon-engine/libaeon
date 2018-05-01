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

#include <aeon/imaging/image.h>
#include <cstring>

namespace aeon::imaging
{

image::image(const descriptor descriptor)
    : descriptor_{descriptor}
    , data_(imaging::size(descriptor), 0)
{
    assert(stride(descriptor) >= width(descriptor));
}

image::image(const descriptor descriptor, std::vector<std::uint8_t> &&data)
    : descriptor_{descriptor}
    , data_{std::move(data)}
{
    assert(stride(descriptor) >= width(descriptor));
}

image::image(const descriptor descriptor, const std::vector<std::uint8_t> &data) // NOLINT
    : descriptor_{descriptor}
    , data_{data}
{
    assert(stride(descriptor) >= width(descriptor));
}

image::image(const descriptor descriptor, void *data)
    : descriptor_{descriptor}
    , data_(imaging::size(descriptor), 0)
{
    assert(stride(descriptor) >= width(descriptor));

    memcpy(data_.data(), data, data_.size());
}

auto image::get_descriptor() const noexcept -> descriptor
{
    return descriptor_;
}

auto image::data() noexcept -> void *
{
    return data_.data();
}

auto image::data() const noexcept -> const void *
{
    return data_.data();
}

auto image::size() const noexcept -> std::size_t
{
    return data_.size();
}

auto image::clone() const -> image
{
    return image{descriptor_, data_};
}

auto image::begin() noexcept -> iterator<std::uint8_t>
{
    const auto bpp = bytes_per_pixel(*this);
    return iterator<std::uint8_t>{data_.data(), bpp};
}

auto image::end() noexcept -> iterator<std::uint8_t>
{
    const auto bpp = bytes_per_pixel(*this);
    return iterator<std::uint8_t>{data_.data() + data_.size(), bpp};
}

} // namespace aeon::imaging

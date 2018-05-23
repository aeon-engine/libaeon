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

#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/dimension.h>

namespace aeon::imaging
{

class descriptor
{
public:
    explicit descriptor(const dimension width, const dimension height, const pixel_encoding encoding) noexcept;
    explicit descriptor(const dimension width, const dimension height, const dimension stride,
                        const pixel_encoding encoding) noexcept;

    ~descriptor() = default;

    descriptor(const descriptor &) noexcept = default;
    auto operator=(const descriptor &) noexcept -> descriptor & = default;
    descriptor(descriptor &&o) noexcept = default;
    auto operator=(descriptor &&other) noexcept -> descriptor & = default;

    auto width() const noexcept -> dimension;
    auto height() const noexcept -> dimension;
    auto stride() const noexcept -> dimension;
    auto encoding() const noexcept -> pixel_encoding;
    auto bytes_per_pixel() const noexcept -> dimension;

private:
    dimension width_;
    dimension height_;
    dimension stride_;
    pixel_encoding encoding_;
    dimension bytes_per_pixel_;
};

inline descriptor::descriptor(const dimension width, const dimension height, const pixel_encoding encoding) noexcept
    : descriptor{width, height, width * imaging::bytes_per_pixel(encoding), encoding}
{
}

inline descriptor::descriptor(const dimension width, const dimension height, const dimension stride,
                              const pixel_encoding encoding) noexcept
    : width_{width}
    , height_{height}
    , stride_{stride}
    , encoding_{encoding}
    , bytes_per_pixel_{imaging::bytes_per_pixel(encoding)}
{
}

inline auto descriptor::width() const noexcept -> dimension
{
    return width_;
}

inline auto descriptor::height() const noexcept -> dimension
{
    return height_;
}

inline auto descriptor::stride() const noexcept -> dimension
{
    return stride_;
}

inline auto descriptor::encoding() const noexcept -> pixel_encoding
{
    return encoding_;
}

inline auto descriptor::bytes_per_pixel() const noexcept -> dimension
{
    return bytes_per_pixel_;
}

inline auto width(const descriptor &descriptor) noexcept
{
    return descriptor.width();
}

inline auto height(const descriptor &descriptor) noexcept
{
    return descriptor.height();
}

inline auto stride(const descriptor &descriptor) noexcept
{
    return descriptor.stride();
}

inline auto encoding(const descriptor &descriptor) noexcept
{
    return descriptor.encoding();
}

inline auto bytes_per_pixel(const descriptor &descriptor) noexcept
{
    return descriptor.bytes_per_pixel();
}

inline auto dimensions(const descriptor &descriptor) noexcept
{
    return width(descriptor) * height(descriptor);
}

inline auto size(const descriptor &descriptor) noexcept
{
    return stride(descriptor) * height(descriptor);
}

inline auto continuous(const descriptor &descriptor) noexcept
{
    return width(descriptor) * bytes_per_pixel(descriptor) == stride(descriptor);
}

inline auto contains(const descriptor &descriptor, const dimension x, const dimension y) noexcept
{
    return x < width(descriptor) && y < height(descriptor);
}

inline auto pixel_offset(const dimension x, const dimension y, const descriptor descriptor) noexcept
{
    return y * stride(descriptor) + (x * bytes_per_pixel(descriptor));
}

inline auto operator==(const descriptor &lhs, const descriptor &rhs) noexcept
{
    return lhs.width() == rhs.width() && lhs.height() == rhs.height() && lhs.stride() == rhs.stride() &&
           lhs.encoding() == rhs.encoding();
}

inline auto operator!=(const descriptor &lhs, const descriptor &rhs) noexcept
{
    return !(lhs == rhs);
}

} // namespace aeon::imaging

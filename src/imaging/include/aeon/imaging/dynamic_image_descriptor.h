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

#include <aeon/imaging/dimension.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/image_descriptor.h>
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>

namespace aeon::imaging
{

class dynamic_image_descriptor
{
public:
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const math::size2d<dimension> dimensions) noexcept;
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const dimension width,
                                      const dimension height) noexcept;
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const math::size2d<dimension> dimensions,
                                      const std::ptrdiff_t stride_y) noexcept;
    explicit dynamic_image_descriptor(const pixel_encoding encoding, const math::size2d<dimension> dimensions,
                                      const std::ptrdiff_t stride_x, const std::ptrdiff_t stride_y) noexcept;

    template <typename T>
    explicit dynamic_image_descriptor(const image_descriptor<T> &descriptor) noexcept;

    ~dynamic_image_descriptor();

    dynamic_image_descriptor(const dynamic_image_descriptor &) noexcept = default;
    auto operator=(const dynamic_image_descriptor &) noexcept -> dynamic_image_descriptor & = default;
    dynamic_image_descriptor(dynamic_image_descriptor &&) noexcept = default;
    auto operator=(dynamic_image_descriptor &&) noexcept -> dynamic_image_descriptor & = default;

    auto encoding() const noexcept -> pixel_encoding;
    auto width() const noexcept -> dimension;
    auto height() const noexcept -> dimension;
    auto dimensions() const noexcept -> math::size2d<dimension>;

    auto stride_x() const noexcept -> std::ptrdiff_t;
    auto stride_y() const noexcept -> std::ptrdiff_t;

private:
    pixel_encoding encoding_;
    math::size2d<dimension> dimensions_;
    std::ptrdiff_t stride_x_;
    std::ptrdiff_t stride_y_;
};

inline auto null(const dynamic_image_descriptor &descriptor) noexcept -> bool;

inline auto valid(const dynamic_image_descriptor &descriptor) noexcept -> bool;

inline auto encoding(const dynamic_image_descriptor &descriptor) noexcept -> pixel_encoding;

inline auto width(const dynamic_image_descriptor &descriptor) noexcept -> dimension;

inline auto height(const dynamic_image_descriptor &descriptor) noexcept -> dimension;

inline auto dimensions(const dynamic_image_descriptor &descriptor) noexcept -> math::size2d<dimension>;

inline auto rectangle(const dynamic_image_descriptor &descriptor) noexcept -> math::rectangle<dimension>;

inline auto stride_x(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

inline auto stride_y(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

inline auto continuous(const dynamic_image_descriptor &descriptor) noexcept -> bool;

inline auto contains(const dynamic_image_descriptor &descriptor, const math::vector2<dimension> coord) noexcept -> bool;

inline auto at_offset(const math::vector2<dimension> coord, const dynamic_image_descriptor &descriptor) noexcept
    -> std::ptrdiff_t;

inline auto size(const dynamic_image_descriptor &descriptor) noexcept -> std::ptrdiff_t;

template <typename T>
inline auto descriptor(const dynamic_image_descriptor &descriptor) noexcept -> image_descriptor<T>;

inline auto operator==(const dynamic_image_descriptor &lhs, const dynamic_image_descriptor &rhs) noexcept -> bool;

inline auto operator!=(const dynamic_image_descriptor &lhs, const dynamic_image_descriptor &rhs) noexcept -> bool;

} // namespace aeon::imaging

#include <aeon/imaging/impl/dynamic_image_descriptor_impl.h>

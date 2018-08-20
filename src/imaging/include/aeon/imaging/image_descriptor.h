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
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <aeon/common/signed_sizeof.h>

namespace aeon::imaging
{

template <typename T>
class image_descriptor
{

    template <typename U>
    friend class image_view_base;

public:
    explicit image_descriptor(const math::size2d<dimension> dimensions) noexcept;
    explicit image_descriptor(const dimension width, const dimension height) noexcept;
    explicit image_descriptor(const math::size2d<dimension> dimensions, const std::ptrdiff_t stride_y) noexcept;
    explicit image_descriptor(const math::size2d<dimension> dimensions, const std::ptrdiff_t stride_x,
                              const std::ptrdiff_t stride_y) noexcept;

    ~image_descriptor();

    image_descriptor(const image_descriptor &) noexcept = default;
    auto operator=(const image_descriptor &) noexcept -> image_descriptor & = default;
    image_descriptor(image_descriptor &&o) noexcept = default;
    auto operator=(image_descriptor &&other) noexcept -> image_descriptor & = default;

    auto width() const noexcept -> dimension;
    auto height() const noexcept -> dimension;
    auto dimensions() const noexcept -> math::size2d<dimension>;

    auto stride_x() const noexcept -> std::ptrdiff_t;
    auto stride_y() const noexcept -> std::ptrdiff_t;

private:
    image_descriptor() noexcept;

    math::size2d<dimension> dimensions_;
    std::ptrdiff_t stride_x_;
    std::ptrdiff_t stride_y_;
};

template <typename T>
inline auto null(const image_descriptor<T> &descriptor) noexcept -> bool;

template <typename T>
inline auto valid(const image_descriptor<T> &descriptor) noexcept -> bool;

template <typename T>
inline auto width(const image_descriptor<T> &descriptor) noexcept;

template <typename T>
inline auto height(const image_descriptor<T> &descriptor) noexcept;

template <typename T>
inline auto dimensions(const image_descriptor<T> &descriptor) noexcept;

template <typename T>
inline auto rectangle(const image_descriptor<T> &descriptor) noexcept -> math::rectangle<dimension>;

template <typename T>
inline auto stride_x(const image_descriptor<T> &descriptor) noexcept;

template <typename T>
inline auto stride_y(const image_descriptor<T> &descriptor) noexcept;

template <typename T>
inline auto continuous(const image_descriptor<T> &descriptor) noexcept;

template <typename T>
inline auto contains(const image_descriptor<T> &descriptor, const math::vector2<dimension> coord) noexcept;

template <typename T>
inline auto at_offset(const math::vector2<dimension> coord, const image_descriptor<T> descriptor) noexcept
    -> std::ptrdiff_t;

template <typename T>
inline auto size(const image_descriptor<T> descriptor) noexcept -> std::ptrdiff_t;

template <typename T>
inline auto operator==(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept;

template <typename T>
inline auto operator!=(const image_descriptor<T> &lhs, const image_descriptor<T> &rhs) noexcept;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_descriptor_impl.h>

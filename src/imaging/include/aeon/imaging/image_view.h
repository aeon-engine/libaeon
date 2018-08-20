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

#include <aeon/imaging/image_descriptor.h>
#include <aeon/imaging/image_view_base.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/vector2.h>
#include <cstdint>
#include <cstddef>

namespace aeon::imaging
{

template <typename T>
class image_view : public image_view_base<T>
{
public:
    image_view() noexcept;
    explicit image_view(const image_descriptor<T> descriptor, std::byte *data) noexcept;
    explicit image_view(const image_descriptor<T> descriptor, const std::byte *data) noexcept;

    virtual ~image_view() noexcept;

    image_view(const image_view<T> &) = default;
    auto operator=(const image_view<T> &) -> image_view<T> & = default;

    image_view(image_view<T> &&) noexcept = default;
    auto operator=(image_view<T> &&) noexcept -> image_view<T> & = default;

    auto data() noexcept -> T *;
    auto data() const noexcept -> const T *;

    template <typename U>
    auto data() noexcept -> U *;

    template <typename U>
    auto data() const noexcept -> const U *;

    auto data(const math::vector2<dimension> coord) noexcept -> T *;
    auto data(const math::vector2<dimension> coord) const noexcept -> const T *;

    template <typename U>
    auto data(const math::vector2<dimension> coord) noexcept -> U *;

    template <typename U>
    auto data(const math::vector2<dimension> coord) const noexcept -> const U *;

    auto at(const math::vector2<dimension> coord) noexcept -> T &;
    auto at(const math::vector2<dimension> coord) const noexcept -> const T &;

protected:
    explicit image_view(const image_descriptor<T> descriptor) noexcept;

    std::byte *data_ptr_;
};

template <typename T>
inline auto null(const image_view<T> &view) noexcept -> bool;

template <typename T>
inline auto valid(const image_view<T> &view) noexcept -> bool;

template <typename T>
inline auto make_view(const image_view<T> &view, const math::rectangle<int> &rect) noexcept -> image_view<T>;

} // namespace aeon::imaging

#include <aeon/imaging/impl/image_view_impl.h>

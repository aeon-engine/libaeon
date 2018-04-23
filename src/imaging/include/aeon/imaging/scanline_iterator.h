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

#include <aeon/imaging/iterator.h>
#include <aeon/imaging/dimension.h>
#include <cstdint>

namespace aeon::imaging
{

template <typename pixel_type_t>
class scanline_iterator
{
public:
    explicit scanline_iterator(std::uint8_t *begin, std::uint8_t *end, const dimension stride);

    ~scanline_iterator() = default;

    scanline_iterator(const scanline_iterator &) = default;
    auto operator=(const scanline_iterator &) -> scanline_iterator & = default;

    scanline_iterator(scanline_iterator &&o) noexcept = default;
    auto operator=(scanline_iterator &&other) noexcept -> scanline_iterator & = default;

    auto begin() noexcept -> iterator<pixel_type_t>;
    auto end() noexcept -> iterator<pixel_type_t>;

private:
    std::uint8_t *begin_;
    std::uint8_t *end_;
    dimension stride_;
};

template <typename pixel_type_t>
scanline_iterator<pixel_type_t>::scanline_iterator(std::uint8_t *begin, std::uint8_t *end, const dimension stride)
    : begin_(begin)
    , end_(end)
    , stride_(stride)
{
}

template <typename pixel_type_t>
auto scanline_iterator<pixel_type_t>::begin() noexcept -> iterator<pixel_type_t>
{
    return iterator<pixel_type_t>{begin_, stride_};
}

template <typename pixel_type_t>
auto scanline_iterator<pixel_type_t>::end() noexcept -> iterator<pixel_type_t>
{
    return iterator<pixel_type_t>{end_, stride_};
}

} // namespace aeon::imaging

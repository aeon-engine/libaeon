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
class pixel_type_iterator
{
public:
    explicit pixel_type_iterator(std::uint8_t *begin, std::uint8_t *end, const std::ptrdiff_t bytes_per_pixel);

    ~pixel_type_iterator() = default;

    pixel_type_iterator(const pixel_type_iterator &) = default;
    auto operator=(const pixel_type_iterator &) -> pixel_type_iterator & = default;

    pixel_type_iterator(pixel_type_iterator &&o) noexcept = default;
    auto operator=(pixel_type_iterator &&other) noexcept -> pixel_type_iterator & = default;

    auto begin() noexcept -> iterator<pixel_type_t>;
    auto end() noexcept -> iterator<pixel_type_t>;

private:
    std::uint8_t *begin_;
    std::uint8_t *end_;
    std::ptrdiff_t bytes_per_pixel_;
};

template <typename pixel_type_t>
pixel_type_iterator<pixel_type_t>::pixel_type_iterator(std::uint8_t *begin, std::uint8_t *end,
                                                       const std::ptrdiff_t bytes_per_pixel)
    : begin_(begin)
    , end_(end)
    , bytes_per_pixel_(bytes_per_pixel)
{
}

template <typename pixel_type_t>
auto pixel_type_iterator<pixel_type_t>::begin() noexcept -> iterator<pixel_type_t>
{
    return iterator<pixel_type_t>{begin_, bytes_per_pixel_};
}

template <typename pixel_type_t>
auto pixel_type_iterator<pixel_type_t>::end() noexcept -> iterator<pixel_type_t>
{
    return iterator<pixel_type_t>{end_, bytes_per_pixel_};
}

} // namespace aeon::imaging

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <algorithm>
#include <vector>

namespace aeon::math
{

inline auto operator==(const imat &lhs, const imat &rhs) noexcept -> bool
{
    if (dimensions(lhs) != dimensions(rhs))
        return false;

    const auto type = element_type(lhs);
    if (type != element_type(rhs))
        return false;

    const auto *const lhs_data = std::data(lhs);
    const auto *const rhs_data = std::data(rhs);

    // If both are matrices continuous, and the elements do not contain an individual stride we can just compare the
    // entire memory block
    if (continuous(lhs) && continuous(rhs) && type.continuous())
        return std::equal(lhs_data, lhs_data + std::size(lhs), rhs_data);

    // Slower individual component check
    const auto y_stride = stride(lhs);
    const auto element_size = type.size;

    for (auto y = 0; y < height(lhs); ++y)
    {
        for (auto x = 0; x < width(lhs); ++x)
        {
            const auto offset = common::offset_of(type, y_stride, x, y);

            if (!std::equal(lhs_data + offset, lhs_data + offset + element_size, rhs_data + offset))
                return false;
        }
    }

    return true;
}

inline auto operator!=(const imat &lhs, const imat &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

inline auto element_type(const imat &m) noexcept -> common::element_type
{
    return m.element_type();
}

inline auto width(const imat &m) noexcept -> imat::dimensions_type
{
    return m.width();
}

inline auto height(const imat &m) noexcept -> imat::dimensions_type
{
    return m.height();
}

inline auto dimensions(const imat &m) noexcept -> size2d<imat::dimensions_type>
{
    return m.dimensions();
}

inline auto stride(const imat &m) noexcept -> imat::stride_type
{
    return m.stride();
}

inline auto continuous(const imat &m) noexcept -> bool
{
    return (height(m) == 1) || (stride(m) == width(m) * element_type(m).size);
}

inline auto contains(const imat &m, const vector2<imat::dimensions_type> coord) noexcept -> bool
{
    return contains(coord, dimensions(m));
}

inline auto size(const imat &m) noexcept -> imat::size_type
{
    return m.size();
}

inline auto null(const imat &m) noexcept -> bool
{
    return std::data(m) == nullptr || (stride(m) == 0 && null(dimensions(m)));
}

inline auto valid(const imat &m) noexcept -> bool
{
    return !null(m);
}

inline auto at(imat &m, const vector2<imat::dimensions_type> coord) noexcept -> imat::underlying_type *
{
    return at(m, coord.x, coord.y);
}

inline auto at(const imat &m, const vector2<imat::dimensions_type> coord) noexcept -> const imat::underlying_type *
{
    return at(m, coord.x, coord.y);
}

template <typename T>
inline auto at(imat &m, const vector2<imat::dimensions_type> coord) noexcept -> T *
{
    return reinterpret_cast<T *>(at(m, coord));
}

template <typename T>
inline auto at(const imat &m, const vector2<imat::dimensions_type> coord) noexcept -> const T *
{
    return reinterpret_cast<const T *>(at(m, coord));
}

inline auto at(imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept
    -> imat::underlying_type *
{
    aeon_assert(x < width(m), "X must be < than the width of the matrix");
    aeon_assert(y < height(m), "Y must be < than the height of the matrix");

    const auto offset = common::offset_of(element_type(m), stride(m), x, y);
    return std::data(m) + offset;
}

inline auto at(const imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept
    -> const imat::underlying_type *
{
    aeon_assert(x < width(m), "X must be < than the width of the matrix");
    aeon_assert(y < height(m), "Y must be < than the height of the matrix");

    const auto offset = common::offset_of(element_type(m), stride(m), x, y);
    return std::data(m) + offset;
}

template <typename T>
inline auto at(imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept -> T *
{
    return reinterpret_cast<T *>(at(m, x, y));
}

template <typename T>
inline auto at(const imat &m, const imat::dimensions_type x, const imat::dimensions_type y) noexcept -> const T *
{
    return reinterpret_cast<const T *>(at(m, x, y));
}

template <typename T>
inline void fill(imat &m, const T value) noexcept
{
    const auto element_type = math::element_type(m);

    aeon_assert(sizeof(T) == element_type.size, "Element type size does not match.");

    const auto w = width(m);
    const auto h = height(m);
    const auto s = stride(m);

    const auto data = std::data(m);

    for (auto y = 0; y < h; ++y)
    {
        for (auto x = 0; x < w; ++x)
        {
            auto typed_data = reinterpret_cast<T *>(data + common::offset_of(element_type, s, x, y));
            *typed_data = value;
        }
    }
}

template <typename T>
inline void fill(imat &m, const math::rectangle<imat::dimensions_type> rect, const T value) noexcept
{
    aeon_assert(math::contains(rect, rectangle<int>{0, 0, dimensions(m)}),
                "View rectangle does not fit within matrix.");

    const auto element_type = math::element_type(m);
    aeon_assert(sizeof(T) == element_type.size, "Element type size does not match.");

    const auto s = stride(m);
    const auto data = std::data(m);

    for (auto y = top(rect); y < bottom(rect); ++y)
    {
        for (auto x = left(rect); x < right(rect); ++x)
        {
            auto typed_data = reinterpret_cast<T *>(data + common::offset_of(element_type, s, x, y));
            *typed_data = value;
        }
    }
}

inline void blit(const imat &src, imat &dst, const vector2<imat::dimensions_type> pos) noexcept
{
    aeon_assert(contains(translated(rectangle<int>{0, 0, dimensions(src)}, pos), rectangle<int>{0, 0, dimensions(dst)}),
                "Destination does not fit within the source at the given position.");

    const auto element_type = math::element_type(src);
    aeon_assert(element_type == math::element_type(dst), "Element type mismatch.");

    const auto source_height = height(src);
    const auto source_row_length = width(src) * element_type.stride;
    const auto source_stride = stride(src);
    const auto dest_stride = stride(dst);

    const auto *const source_data = std::data(src);
    auto *dest_data = std::data(dst);

    for (auto y = 0; y < source_height; ++y)
    {
        const auto *const source_row_offset = source_data + common::offset_of(element_type, source_stride, 0, y);
        auto *const dest_row_offset = dest_data + common::offset_of(element_type, dest_stride, pos.x, pos.y + y);
        std::copy_n(source_row_offset, source_row_length, dest_row_offset);
    }
}

inline void invert_vertically(imat &m)
{
    const auto height = math::height(m);
    const auto stride = math::stride(m);
    const auto element_type = math::element_type(m);
    auto *const data = std::data(m);

    std::vector<imat::underlying_type> scanline_buffer(stride);

    for (auto y = 0ll; y < height / 2; ++y)
    {
        auto *const upper_scanline = data + common::offset_of(element_type, stride, 0, y);
        auto *const lower_scanline = data + common::offset_of(element_type, stride, 0, height - 1 - y);

        // Copy the upper scanline in a temporary buffer
        std::copy_n(upper_scanline, std::size(scanline_buffer), std::data(scanline_buffer));

        // Copy the lower scanline in the upper one
        std::copy_n(lower_scanline, std::size(scanline_buffer), upper_scanline);

        // Copy the upper scanline from the temp buffer to the lower one
        std::copy_n(std::data(scanline_buffer), std::size(scanline_buffer), lower_scanline);
    }
}

} // namespace aeon::math

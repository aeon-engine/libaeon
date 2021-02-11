// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <algorithm>

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

} // namespace aeon::math

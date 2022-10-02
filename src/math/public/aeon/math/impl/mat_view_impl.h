// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/mat3.h>
#include <aeon/common/assert.h>
#include <limits>

namespace aeon::math
{

inline mat_view::mat_view() noexcept
    : type_{}
    , data_ptr_{nullptr}
    , dimensions_{}
    , stride_{0}
    , size_{0}
{
}

inline mat_view::mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                          underlying_type *data) noexcept
    : mat_view{type, dimensions, math::width(dimensions) * type.size, data}
{
}

inline mat_view::mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                          underlying_type *data) noexcept
    : mat_view{type, size2d{width, height}, data}
{
}

inline mat_view::mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                          const stride_type stride, underlying_type *data) noexcept
    : mat_view{type, dimensions, stride, data, stride * math::height(dimensions)}
{
}

inline mat_view::mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                          const stride_type stride, underlying_type *data) noexcept
    : mat_view{type, size2d{width, height}, stride, data}
{
}

inline mat_view::mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                          underlying_type *data, const size_type size) noexcept
    : mat_view{type, dimensions, math::width(dimensions) * type.size, data, size}
{
}

inline mat_view::mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                          underlying_type *data, const size_type size) noexcept
    : mat_view{type, size2d{width, height}, data, size}
{
}

inline mat_view::mat_view(const common::element_type type, const size2d<dimensions_type> dimensions,
                          const stride_type stride, underlying_type *data, const size_type size) noexcept
    : type_{type}
    , data_ptr_{data}
    , dimensions_{dimensions}
    , stride_{stride}
    , size_{size}
{
}

inline mat_view::mat_view(const common::element_type type, const dimensions_type width, const dimensions_type height,
                          const stride_type stride, underlying_type *data, const size_type size) noexcept
    : mat_view{type, size2d{width, height}, stride, data, size}
{
}

[[nodiscard]] inline auto mat_view::element_type() const noexcept -> common::element_type
{
    return type_;
}

[[nodiscard]] inline auto mat_view::width() const noexcept -> dimensions_type
{
    return math::width(dimensions_);
}

[[nodiscard]] inline auto mat_view::height() const noexcept -> dimensions_type
{
    return math::height(dimensions_);
}

[[nodiscard]] inline auto mat_view::dimensions() const noexcept -> size2d<dimensions_type>
{
    return dimensions_;
}

[[nodiscard]] inline auto mat_view::stride() const noexcept -> stride_type
{
    return stride_;
}

[[nodiscard]] inline auto mat_view::size() const noexcept -> size_type
{
    return size_;
}

[[nodiscard]] inline auto mat_view::data() noexcept -> underlying_type *
{
    return data_ptr_;
}

[[nodiscard]] inline auto mat_view::data() const noexcept -> const underlying_type *
{
    return data_ptr_;
}

[[nodiscard]] inline auto operator==(const mat_view &lhs, const mat_view &rhs) noexcept -> bool
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

[[nodiscard]] inline auto operator!=(const mat_view &lhs, const mat_view &rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

inline auto element_type(const mat_view &m) noexcept -> common::element_type
{
    return m.element_type();
}

inline auto width(const mat_view &m) noexcept -> mat_view::dimensions_type
{
    return m.width();
}

inline auto height(const mat_view &m) noexcept -> mat_view::dimensions_type
{
    return m.height();
}

inline auto dimensions(const mat_view &m) noexcept -> size2d<mat_view::dimensions_type>
{
    return m.dimensions();
}

inline auto stride(const mat_view &m) noexcept -> mat_view::stride_type
{
    return m.stride();
}

inline auto continuous(const mat_view &m) noexcept -> bool
{
    return (height(m) == 1) || (stride(m) == width(m) * element_type(m).size);
}

inline auto contains(const mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept -> bool
{
    return contains(coord, dimensions(m));
}

inline auto size(const mat_view &m) noexcept -> mat_view::size_type
{
    return m.size();
}

inline auto null(const mat_view &m) noexcept -> bool
{
    return std::data(m) == nullptr || (stride(m) == 0 && null(dimensions(m)));
}

inline auto valid(const mat_view &m) noexcept -> bool
{
    return !null(m);
}

inline auto at(mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept -> mat_view::underlying_type *
{
    return at(m, coord.x, coord.y);
}

inline auto at(const mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept
    -> const mat_view::underlying_type *
{
    return at(m, coord.x, coord.y);
}

template <typename T>
inline auto at(mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept -> T *
{
    return reinterpret_cast<T *>(at(m, coord));
}

template <typename T>
inline auto at(const mat_view &m, const vector2<mat_view::dimensions_type> coord) noexcept -> const T *
{
    return reinterpret_cast<const T *>(at(m, coord));
}

inline auto at(mat_view &m, const mat_view::dimensions_type x, const mat_view::dimensions_type y) noexcept
    -> mat_view::underlying_type *
{
    aeon_assert(x < width(m), "X must be < than the width of the matrix");
    aeon_assert(y < height(m), "Y must be < than the height of the matrix");

    const auto offset = common::offset_of(element_type(m), stride(m), x, y);
    return std::data(m) + offset;
}

inline auto at(const mat_view &m, const mat_view::dimensions_type x, const mat_view::dimensions_type y) noexcept
    -> const mat_view::underlying_type *
{
    aeon_assert(x < width(m), "X must be < than the width of the matrix");
    aeon_assert(y < height(m), "Y must be < than the height of the matrix");

    const auto offset = common::offset_of(element_type(m), stride(m), x, y);
    return std::data(m) + offset;
}

template <typename T>
inline auto at(mat_view &m, const mat_view::dimensions_type x, const mat_view::dimensions_type y) noexcept -> T *
{
    return reinterpret_cast<T *>(at(m, x, y));
}

template <typename T>
inline auto at(const mat_view &m, const mat_view::dimensions_type x, const mat_view::dimensions_type y) noexcept
    -> const T *
{
    return reinterpret_cast<const T *>(at(m, x, y));
}

template <typename T>
inline void fill(mat_view &m, const T value) noexcept
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
inline void fill(mat_view &m, const math::rectangle<mat_view::dimensions_type> rect, const T value) noexcept
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

inline void blit(const mat_view &src, mat_view &dst, const vector2<mat_view::dimensions_type> pos) noexcept
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

inline void invert_vertically(mat_view &m)
{
    const auto height = math::height(m);
    const auto stride = math::stride(m);
    const auto element_type = math::element_type(m);
    auto *const data = std::data(m);

    std::vector<mat_view::underlying_type> scanline_buffer(stride);

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

[[nodiscard]] inline auto make_view(mat_view &view, const rectangle<int> &rect) noexcept -> mat_view
{
    aeon_assert(!view.element_type().is_undefined(), "View has an undefined data layout.");
    aeon_assert(math::contains(rect, rectangle<int>{0, 0, dimensions(view)}),
                "View rectangle does not fit within matrix.");
    return mat_view{element_type(view), width(rect), height(rect), stride(view), at(view, left(rect), top(rect))};
}

[[nodiscard]] inline auto make_view(mat3 &mat) noexcept -> mat_view
{
    return mat_view{common::element_type::f32_1, 3, 3, std::data(mat)};
}

[[nodiscard]] inline auto make_view(mat4 &mat) noexcept -> mat_view
{
    return mat_view{common::element_type::f32_1, 4, 4, std::data(mat)};
}

namespace internal
{

template <typename T, swizzle_component component>
inline void swizzle_apply(const T *src, T *dst, const std::size_t index) noexcept
{
    if constexpr (component == swizzle_component::x)
        dst[index] = src[0];
    else if constexpr (component == swizzle_component::y)
        dst[index] = src[1];
    else if constexpr (component == swizzle_component::z)
        dst[index] = src[2];
    else if constexpr (component == swizzle_component::w)
        dst[index] = src[3];
    else if constexpr (component == swizzle_component::one)
        dst[index] = T(1);
    else if constexpr (component == swizzle_component::minus_one)
        dst[index] = T(-1);
    else if constexpr (component == swizzle_component::zero)
        dst[index] = T(0);
    else if constexpr (component == swizzle_component::min)
        dst[index] = std::numeric_limits<T>::min();
    else if constexpr (component == swizzle_component::max)
        dst[index] = std::numeric_limits<T>::max();
}

template <typename T, swizzle_component... components>
inline void swizzle(mat_view &view) noexcept
{
    constexpr auto component_count = sizeof...(components);

    auto data = reinterpret_cast<T *>(view.data());

    const auto size = area(view.dimensions()) * component_count;
    for (auto i = 0u; i < size; i += component_count)
    {
        std::array<T, component_count> components_data;
        std::copy_n(&data[i], component_count, std::data(components_data));

        std::size_t index = 0;
        (swizzle_apply<T, components>(std::data(components_data), &data[i], index++), ...);
    }
}

} // namespace internal

template <swizzle_component... components>
inline void swizzle(mat_view &view) noexcept
{
    // Currently strides are not supported. They may be in the future.
    if (!view.element_type().continuous() || !math::continuous(view))
        std::abort();

    if (view.element_type().count != sizeof...(components) || view.element_type().is_undefined())
        std::abort();

    switch (view.element_type().name)
    {
        case common::element_type_name::u8:
            internal::swizzle<std::uint8_t, components...>(view);
            break;
        case common::element_type_name::s8:
            internal::swizzle<std::int8_t, components...>(view);
            break;
        case common::element_type_name::u16:
            internal::swizzle<std::uint16_t, components...>(view);
            break;
        case common::element_type_name::s16:
            internal::swizzle<std::int16_t, components...>(view);
            break;
        case common::element_type_name::u32:
            internal::swizzle<std::uint32_t, components...>(view);
            break;
        case common::element_type_name::s32:
            internal::swizzle<std::int32_t, components...>(view);
            break;
        case common::element_type_name::u64:
            internal::swizzle<std::uint64_t, components...>(view);
            break;
        case common::element_type_name::s64:
            internal::swizzle<std::int64_t, components...>(view);
            break;
        case common::element_type_name::f32:
            internal::swizzle<float, components...>(view);
            break;
        case common::element_type_name::f64:
            internal::swizzle<double, components...>(view);
            break;
        default:
            std::abort();
    }
}

} // namespace aeon::math

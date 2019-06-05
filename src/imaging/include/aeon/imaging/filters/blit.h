// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/filters/resize.h>
#include <aeon/imaging/pixel_math.h>
#include <aeon/math/vector2.h>
#include <aeon/common/assert.h>

namespace aeon::imaging::filters
{

namespace internal
{

template <typename T>
[[nodiscard]] inline auto blend_add(const T src_pixel, const T dst_pixel) noexcept -> T
{
    const auto new_value = src_pixel + dst_pixel;
    return pixel_math<T>::clamp(new_value);
}

template <typename T>
[[nodiscard]] inline auto blend_multiply(const T src_pixel, const T dst_pixel) noexcept -> T
{
    const auto new_value = src_pixel * dst_pixel;
    return pixel_math<T>::clamp(new_value);
}

template <typename T>
[[nodiscard]] inline auto blend_alpha(const T src_pixel, const T dst_pixel) noexcept -> T
{
    const auto alpha_ratio = pixel_math<T>::alpha_ratio(src_pixel);
    const auto src_intensity = src_pixel * alpha_ratio;
    const auto dst_intensity = dst_pixel * (1.0f - alpha_ratio);

    const auto new_value = src_intensity + dst_intensity;
    return pixel_math<T>::clamp(new_value);
}

} // namespace internal

template <typename T>
inline void blit(const image_view<T> &src, image_view<T> &dst, const math::vector2<dimension> pos)
{
    aeon_assert(math::contains(math::translated(rectangle(src), pos), rectangle(dst)),
                "Source does not fit within destination.");

    const auto w = width(src);
    const auto h = height(src);
    const auto src_stride = stride_y(src) / sizeof(T);
    const auto src_data = src.data();

    auto dst_data = dst.data();
    const auto dst_stride = stride_y(dst) / sizeof(T);

    for (auto y = 0; y < h; ++y)
    {
        const auto src_row = &src_data[y * src_stride];
        auto dst_row = &dst_data[(pos.y + y) * dst_stride];

        for (auto x = 0; x < w; ++x)
        {
            dst_row[x + pos.x] = src_row[x];
        }
    }
}

inline void blit(const dynamic_image &src, dynamic_image &dst, const math::vector2<dimension> pos)
{
    process_image_with_dst(src, dst, blit, pos);
}

enum class blend_blit_mode
{
    overwrite,
    add,
    multiply,
    alpha
};

template <typename T>
inline void blend_blit(const image_view<T> &src, image_view<T> &dst, const math::vector2<dimension> pos,
                       const blend_blit_mode mode)
{
    aeon_assert(math::contains(math::translated(rectangle(src), pos), rectangle(dst)),
                "Source does not fit within destination.");

    using blend_func = typename std::add_pointer<auto(const T, const T) noexcept->T>::type;
    blend_func func;

    switch (mode)
    {
        case blend_blit_mode::overwrite:
            return blit(src, dst, pos);
        case blend_blit_mode::add:
            func = internal::blend_add;
            break;
        case blend_blit_mode::multiply:
            func = internal::blend_multiply;
            break;
        case blend_blit_mode::alpha:
            func = internal::blend_alpha;
            break;
        default:
            throw imaging_exception{};
    }

    const auto w = width(src);
    const auto h = height(src);
    const auto src_stride = stride_y(src) / sizeof(T);
    const auto src_data = src.data();

    auto dst_data = dst.data();
    const auto dst_stride = stride_y(dst) / sizeof(T);

    for (auto y = 0; y < h; ++y)
    {
        const auto src_row = &src_data[y * src_stride];
        auto dst_row = &dst_data[(pos.y + y) * dst_stride];

        for (auto x = 0; x < w; ++x)
        {
            dst_row[x + pos.x] = func(src_row[x], dst_row[x + pos.x]);
        }
    }
}

inline void blend_blit(const dynamic_image &src, dynamic_image &dst, const math::vector2<dimension> pos,
                       const blend_blit_mode mode)
{
    process_image_with_dst(src, dst, blend_blit, pos, mode);
}

template <typename T>
inline void scale_blit(const image_view<T> &src, image_view<T> &dst, const math::rectangle<dimension> rect)
{
    aeon_assert(math::contains(rect, rectangle(dst)), "Source does not fit within destination.");

    const auto new_src = resize_bilinear(src, math::size(rect));
    blit<T>(new_src, dst, math::left_top(rect));
}

inline void scale_blit(const dynamic_image &src, dynamic_image &dst, const math::rectangle<dimension> rect)
{
    process_image_with_dst(src, dst, scale_blit, rect);
}

template <typename T>
inline void blend_scale_blit(const image_view<T> &src, image_view<T> &dst, const math::rectangle<dimension> rect,
                             const blend_blit_mode mode)
{
    aeon_assert(math::contains(rect, rectangle(dst)), "Source does not fit within destination.");

    const auto new_src = resize_bilinear(src, math::size(rect));
    blend_blit<T>(new_src, dst, math::left_top(rect), mode);
}

inline void blend_scale_blit(const dynamic_image &src, dynamic_image &dst, const math::rectangle<dimension> rect,
                             const blend_blit_mode mode)
{
    process_image_with_dst(src, dst, blend_scale_blit, rect, mode);
}

} // namespace aeon::imaging::filters

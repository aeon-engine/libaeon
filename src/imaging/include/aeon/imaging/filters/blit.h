// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/dynamic_image.h>
#include <aeon/imaging/filters/resize.h>
#include <aeon/imaging/pixel_math.h>
#include <aeon/math/vector2.h>
#include <aeon/common/assert.h>

namespace aeon::imaging::filters
{

enum class blend_blit_mode
{
    overwrite,
    add,
    multiply,
    alpha
};

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

template <typename T>
struct blit_impl
{
    static void process(const image_view<T> &src, image_view<T> &dst, const math::vector2<dimension> pos)
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
            auto dst_row = &dst_data[(static_cast<std::ptrdiff_t>(pos.y) + y) * dst_stride];

            for (auto x = 0; x < w; ++x)
            {
                dst_row[x + pos.x] = src_row[x];
            }
        }
    }
};

template <typename T>
struct blend_blit_impl
{
    static void process(const image_view<T> &src, image_view<T> &dst, const math::vector2<dimension> pos,
                        const blend_blit_mode mode)
    {
        aeon_assert(math::contains(math::translated(rectangle(src), pos), rectangle(dst)),
                    "Source does not fit within destination.");

        using blend_func = typename std::add_pointer<auto(const T, const T) noexcept->T>::type;
        blend_func func;

        switch (mode)
        {
            case blend_blit_mode::overwrite:
                blit_impl<T>::process(src, dst, pos);
                return;
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
            auto dst_row = &dst_data[(static_cast<std::ptrdiff_t>(pos.y) + y) * dst_stride];

            for (auto x = 0; x < w; ++x)
            {
                dst_row[x + pos.x] = func(src_row[x], dst_row[x + pos.x]);
            }
        }
    }
};

template <typename T>
struct scale_blit_impl
{
    static void process(const image_view<T> &src, image_view<T> &dst, const math::rectangle<dimension> rect)
    {
        aeon_assert(math::contains(rect, rectangle(dst)), "Source does not fit within destination.");

        const auto new_src = resize_bilinear(src, math::size(rect));
        blit<T>(new_src, dst, math::left_top(rect));
    }
};

template <typename T>
struct blend_scale_blit_impl
{
    static void process(const image_view<T> &src, image_view<T> &dst, const math::rectangle<dimension> rect,
                        const blend_blit_mode mode)
    {
        aeon_assert(math::contains(rect, rectangle(dst)), "Source does not fit within destination.");

        const auto new_src = resize_bilinear(src, math::size(rect));
        blend_blit<T>(new_src, dst, math::left_top(rect), mode);
    }
};

} // namespace internal

template <typename T>
inline void blit(const image_view<T> &src, image_view<T> &dst, const math::vector2<dimension> pos)
{
    internal::blit_impl<T>::process(src, dst, pos);
}

inline void blit(const dynamic_image &src, dynamic_image &dst, const math::vector2<dimension> pos)
{
    process_image<internal::blit_impl>(src, dst, pos);
}

template <typename T>
inline void blend_blit(const image_view<T> &src, image_view<T> &dst, const math::vector2<dimension> pos,
                       const blend_blit_mode mode)
{
    internal::blend_blit_impl<T>::process(src, dst, pos, mode);
}

inline void blend_blit(const dynamic_image &src, dynamic_image &dst, const math::vector2<dimension> pos,
                       const blend_blit_mode mode)
{
    process_image<internal::blend_blit_impl>(src, dst, pos, mode);
}

template <typename T>
inline void scale_blit(const image_view<T> &src, image_view<T> &dst, const math::rectangle<dimension> rect)
{
    internal::scale_blit_impl<T>::process(src, dst, rect);
}

inline void scale_blit(const dynamic_image &src, dynamic_image &dst, const math::rectangle<dimension> rect)
{
    process_image<internal::scale_blit_impl>(src, dst, rect);
}

template <typename T>
inline void blend_scale_blit(const image_view<T> &src, image_view<T> &dst, const math::rectangle<dimension> rect,
                             const blend_blit_mode mode)
{
    internal::blend_scale_blit_impl<T>::process(src, dst, rect, mode);
}

inline void blend_scale_blit(const dynamic_image &src, dynamic_image &dst, const math::rectangle<dimension> rect,
                             const blend_blit_mode mode)
{
    process_image<internal::blend_scale_blit_impl>(src, dst, rect, mode);
}

} // namespace aeon::imaging::filters

// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/math/vector2.h>

namespace aeon::fonts
{

enum class glyph_pixel_type
{
    gray,
    color
};

class glyph
{
public:
    explicit glyph(imaging::image_view<std::uint8_t> view, const math::vector2<int> &offset,
                   const math::vector2<int> &advance) noexcept
        : view_{std::move(view)}
        , color_view_{}
        , offset_{offset}
        , advance_{advance}
        , pixel_type_{glyph_pixel_type::gray}
        , dimensions_{0}
    {
    }

    explicit glyph(imaging::image_view<imaging::bgra32> view, const math::vector2<int> &offset,
                   const math::vector2<int> &advance, const int dimensions) noexcept
        : view_{}
        , color_view_{std::move(view)}
        , offset_{offset * (static_cast<float>(dimensions) / static_cast<float>(imaging::width(view)))}
        , advance_{advance * (static_cast<float>(dimensions) / static_cast<float>(imaging::width(view)))}
        , pixel_type_{glyph_pixel_type::color}
        , dimensions_{dimensions}
    {
    }

    ~glyph() = default;

    glyph(const glyph &) = delete;
    auto operator=(const glyph &) -> glyph & = delete;

    glyph(glyph &&other) noexcept = default;
    auto operator=(glyph &&other) noexcept -> glyph & = default;

    auto &view() const noexcept
    {
        return view_;
    }

    auto &color_view() const noexcept
    {
        return color_view_;
    }

    auto offset() const noexcept
    {
        return offset_;
    }

    auto advance() const noexcept
    {
        return advance_;
    }

    auto pixel_type() const noexcept
    {
        return pixel_type_;
    }

    /*!
     * If the glyph is a color view (usually an emoji), it's likely to require scaling to be rendered correctly.
     * Dimensions returns the calculated size in pixels that should be used when rendering this glyph based on
     * the given dpi and point size.
     *
     * This value is 0 for normal vector based glyphs as they are already the correct size.
     */
    auto dimensions() const noexcept
    {
        return dimensions_;
    }

private:
    imaging::image_view<std::uint8_t> view_;
    imaging::image_view<imaging::bgra32> color_view_;
    math::vector2<int> offset_;
    math::vector2<int> advance_;
    glyph_pixel_type pixel_type_;
    int dimensions_;
};

} // namespace aeon::fonts

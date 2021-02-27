// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/math/vector2.h>
#include <aeon/math/size2d.h>

namespace aeon::fonts
{

enum class glyph_pixel_type
{
    gray,
    color
};

class [[nodiscard]] glyph final
{
public:
    explicit glyph(imaging::image_view view, const math::size2d<float> &dimensions, const math::vector2<float> &offset,
                   const math::vector2<float> &advance) noexcept
        : view_{std::move(view)}
        , dimensions_{dimensions}
        , offset_{offset}
        , advance_{advance}
        , pixel_type_{glyph_pixel_type::gray}
    {
    }

    explicit glyph(imaging::image_view view, const float dimensions, const math::vector2<float> &offset,
                   const math::vector2<float> &advance) noexcept
        : view_{std::move(view)}
        , dimensions_{dimensions, dimensions}
        , offset_{offset * (dimensions / static_cast<float>(math::width(view)))}
        , advance_{advance * (dimensions / static_cast<float>(math::width(view)))}
        , pixel_type_{glyph_pixel_type::color}
    {
    }

    ~glyph() = default;

    glyph(const glyph &) = delete;
    auto operator=(const glyph &) -> glyph & = delete;

    glyph(glyph &&other) noexcept = default;
    auto operator=(glyph &&other) noexcept -> glyph & = default;

    [[nodiscard]] auto has_view() const noexcept
    {
        return math::valid(view_);
    }

    [[nodiscard]] auto &view() const noexcept
    {
        return view_;
    }

    /*!
     * When using the LCD render mode, the actual dimensions of the glyph don't match those in the image.
     *
     * If the glyph is a color view (usually an emoji), it's likely to require scaling to be rendered correctly.
     * Dimensions returns the calculated size in pixels that should be used when rendering this glyph based on
     * the given dpi and point size.
     *
     * This value is 0 for normal vector based glyphs as they are already the correct size.
     */
    [[nodiscard]] auto dimensions() const noexcept
    {
        return dimensions_;
    }

    [[nodiscard]] auto offset() const noexcept
    {
        return offset_;
    }

    [[nodiscard]] auto advance() const noexcept
    {
        return advance_;
    }

    [[nodiscard]] auto pixel_type() const noexcept
    {
        return pixel_type_;
    }

private:
    imaging::image_view view_;
    math::size2d<float> dimensions_;
    math::vector2<float> offset_;
    math::vector2<float> advance_;
    glyph_pixel_type pixel_type_;
};

} // namespace aeon::fonts

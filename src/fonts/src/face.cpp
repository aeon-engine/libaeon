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

#include <aeon/fonts/face.h>
#include <aeon/fonts/exceptions.h>
#include <aeon/streams/stream.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/tttables.h>

namespace aeon::fonts
{

namespace internal
{

// 1 point is 1/72th of an inch.
static constexpr auto points_per_inch = 72.0f;

auto create_freetype_face(FT_LibraryRec_ *library, const std::vector<std::uint8_t> &data, const int index)
    -> FT_FaceRec_ *
{
    FT_Face face = nullptr;

    if (FT_New_Memory_Face(library, data.data(), static_cast<FT_Long>(data.size()), 0, &face) != 0)
        throw font_exception{};

    return face;
}

void free_freetype_face(FT_FaceRec_ *face)
{
    FT_Done_Face(face);
}

static auto has_color_emoji(FT_FaceRec_ *face) noexcept -> bool
{
    static const auto tag = FT_MAKE_TAG('C', 'B', 'D', 'T');
    unsigned long length = 0;
    FT_Load_Sfnt_Table(face, tag, 0, nullptr, &length);
    return length != 0;
}

static auto points_to_pixels(const float points, const int dpi) noexcept -> int
{
    return static_cast<int>((points / (points_per_inch / static_cast<float>(dpi))));
}

static void freetype_select_emoji_pixel_size(FT_FaceRec_ *face, const float points, const int dpi)
{
    const auto pixel_size = points_to_pixels(points, dpi);

    if (face->num_fixed_sizes == 0)
        throw font_exception{};

    auto best_match = 0;
    auto diff = std::abs(pixel_size - face->available_sizes[0].width);

    for (int i = 1; i < face->num_fixed_sizes; ++i)
    {
        const auto ndiff = std::abs(pixel_size - face->available_sizes[i].width);
        if (ndiff < diff)
        {
            best_match = i;
            diff = ndiff;
        }
    }

    if (FT_Select_Size(face, best_match) != 0)
        throw font_exception{};
}

static auto create_image_view_uint8(const FT_Bitmap &bitmap) noexcept -> imaging::image_view<std::uint8_t>
{
    if (!bitmap.buffer)
        return {};

    aeon_assert(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY, "Expected gray uint8 pixel format.");

    const imaging::image_descriptor<std::uint8_t> descriptor{
        math::size2d<imaging::dimension>{bitmap.width, bitmap.rows}, bitmap.pitch};
    return imaging::image_view{descriptor, reinterpret_cast<const std::byte *>(bitmap.buffer)};
}

static auto create_image_view_bgra32(const FT_Bitmap &bitmap) noexcept -> imaging::image_view<imaging::bgra32>
{
    if (!bitmap.buffer)
        return {};

    aeon_assert(bitmap.pixel_mode == FT_PIXEL_MODE_BGRA, "Expected BGRA32 pixel format.");

    const imaging::image_descriptor<imaging::bgra32> descriptor{
        math::size2d<imaging::dimension>{bitmap.width, bitmap.rows}, bitmap.pitch};
    return imaging::image_view{descriptor, reinterpret_cast<const std::byte *>(bitmap.buffer)};
}

} // namespace internal

face::face(FT_LibraryRec_ *library, streams::stream &stream, const float points, const int dpi)
    : face_data_{stream.read_to_vector()}
    , face_{internal::create_freetype_face(library, face_data_, 0), internal::free_freetype_face}
    , has_color_emoji_{internal::has_color_emoji(face_.get())}
{
    if (!has_color_emoji_)
    {
        FT_Set_Char_Size(face_.get(), 0, static_cast<int>(points * 64.0f), dpi, dpi);
    }
    else
    {
        internal::freetype_select_emoji_pixel_size(face_.get(), points, dpi);
    }
}

face::~face() = default;

auto face::load_glyph(const long unicode_control_code) const -> glyph
{
    const auto glyph_index = FT_Get_Char_Index(face_.get(), unicode_control_code);

    FT_Int32 flags = FT_LOAD_DEFAULT;

    if (has_color_emoji_)
        flags |= FT_LOAD_COLOR;

    if (FT_Load_Glyph(face_.get(), glyph_index, flags) != 0)
        throw font_exception{};

    if (FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_NORMAL) != 0)
        throw font_exception{};

    const auto offset = math::vector2<int>{face_->glyph->bitmap_left, -face_->glyph->bitmap_top};
    const auto advance = math::vector2<int>{face_->glyph->advance.x, face_->glyph->advance.y} / 64;

    if (face_->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
    {
        return glyph{internal::create_image_view_uint8(face_->glyph->bitmap), offset, advance};
    }
    else if (face_->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_BGRA)
    {
        return glyph{internal::create_image_view_bgra32(face_->glyph->bitmap), offset, advance};
    }

    throw font_exception{};
}

} // namespace aeon::fonts

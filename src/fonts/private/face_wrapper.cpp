// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/fonts/face_wrapper.h>
#include <aeon/fonts/exceptions.h>
#include <aeon/streams/stream_reader.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/tttables.h>

namespace aeon::fonts
{

namespace internal
{

// 1 point is 1/72th of an inch.
static constexpr auto points_per_inch = 72.0f;

[[nodiscard]] static auto create_freetype_face(FT_LibraryRec_ *library, const std::vector<char> &data, const int index)
    -> FT_FaceRec_ *
{
    FT_Face face = nullptr;

    if (FT_New_Memory_Face(library, reinterpret_cast<const FT_Byte *>(std::data(data)),
                           static_cast<FT_Long>(std::size(data)), index, &face) != 0)
        throw font_exception{};

    return face;
}

void free_freetype_face(FT_FaceRec_ *face)
{
    FT_Done_Face(face);
}

[[nodiscard]] static auto has_color_emoji(FT_FaceRec_ *face) noexcept -> bool
{
    static const auto tag = FT_MAKE_TAG('C', 'B', 'D', 'T');
    unsigned long length = 0;
    FT_Load_Sfnt_Table(face, tag, 0, nullptr, &length);
    return length != 0;
}

[[nodiscard]] static auto points_to_pixels(const float points, const int dpi) noexcept -> int
{
    return static_cast<int>((points / (points_per_inch / static_cast<float>(dpi))));
}

static void freetype_select_emoji_pixel_size(FT_FaceRec_ *face, const int pixels)
{
    if (face->num_fixed_sizes == 0)
        throw font_exception{};

    auto best_match = 0;
    auto diff = std::abs(pixels - face->available_sizes[0].width);

    for (int i = 1; i < face->num_fixed_sizes; ++i)
    {
        const auto ndiff = std::abs(pixels - face->available_sizes[i].width);
        if (ndiff < diff)
        {
            best_match = i;
            diff = ndiff;
        }
    }

    if (FT_Select_Size(face, best_match) != 0)
        throw font_exception{};
}

[[nodiscard]] static auto create_image_view_uint8(const FT_Bitmap &bitmap) noexcept -> imaging::image_view
{
    if (!bitmap.buffer)
        return {};

    aeon_assert(bitmap.pixel_mode == FT_PIXEL_MODE_GRAY, "Expected gray uint8 pixel format.");

    return imaging::image_view{common::element_type::u8_1, imaging::pixel_encoding::monochrome,
                               math::size2d<imaging::image_view::dimensions_type>{bitmap.width, bitmap.rows},
                               static_cast<imaging::image_view::stride_type>(bitmap.pitch),
                               reinterpret_cast<std::byte *>(bitmap.buffer)};
}

[[nodiscard]] static auto create_image_view_bgra32(const FT_Bitmap &bitmap) noexcept -> imaging::image_view
{
    if (!bitmap.buffer)
        return {};

    aeon_assert(bitmap.pixel_mode == FT_PIXEL_MODE_BGRA, "Expected BGRA32 pixel format.");

    return imaging::image_view{common::element_type::u8_4, imaging::pixel_encoding::bgra,
                               math::size2d<imaging::image_view::dimensions_type>{bitmap.width, bitmap.rows},
                               static_cast<imaging::image_view::stride_type>(bitmap.pitch),
                               reinterpret_cast<std::byte *>(bitmap.buffer)};
}

[[nodiscard]] static auto load_glyph(const FT_Face face, const bool has_color_emoji, const int dimensions_px,
                                     const FT_UInt glyph_index) -> glyph
{
    FT_Int32 flags = FT_LOAD_DEFAULT;

    if (has_color_emoji)
        flags |= FT_LOAD_COLOR;

    if (FT_Load_Glyph(face, glyph_index, flags) != 0)
        throw font_exception{};

    if (FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL) != 0)
        throw font_exception{};

    const auto offset = math::vector2<int>{face->glyph->bitmap_left, -face->glyph->bitmap_top};
    const auto advance = math::vector2<int>{face->glyph->advance.x, face->glyph->advance.y} / 64;

    if (face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
    {
        return glyph{internal::create_image_view_uint8(face->glyph->bitmap), offset, advance};
    }
    else if (face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_BGRA)
    {
        return glyph{internal::create_image_view_bgra32(face->glyph->bitmap), offset, advance, dimensions_px};
    }

    throw font_exception{};
}

} // namespace internal

face_wrapper::face_wrapper(FT_LibraryRec_ *library, streams::idynamic_stream &stream, const float points, const int dpi)
    : face_data_{streams::stream_reader{stream}.read_to_vector<char>()}
    , face_{internal::create_freetype_face(library, face_data_, 0), internal::free_freetype_face}
    , has_color_emoji_{internal::has_color_emoji(face_.get())}
    , dimensions_px_{internal::points_to_pixels(points, dpi)}
    , line_height_{face_->height / dpi}
{
    if (!has_color_emoji_)
    {
        FT_Set_Char_Size(face_.get(), 0, static_cast<int>(points * 64.0f), dpi, dpi);
    }
    else
    {
        internal::freetype_select_emoji_pixel_size(face_.get(), dimensions_px_);
    }
}

face_wrapper::~face_wrapper() = default;

[[nodiscard]] auto face_wrapper::get_char_index(const char32_t control_code) const -> unsigned int
{
    return FT_Get_Char_Index(face_.get(), control_code);
}

auto face_wrapper::load_first_index() const -> std::tuple<char32_t, unsigned int>
{
    FT_UInt index;
    auto control_code = FT_Get_First_Char(face_.get(), &index);
    return {control_code, index};
}

auto face_wrapper::load_next_index(const char32_t control_code) const -> std::tuple<char32_t, unsigned int>
{
    FT_UInt index;
    auto next_control_code = FT_Get_Next_Char(face_.get(), control_code, &index);
    return {next_control_code, index};
}

[[nodiscard]] auto face_wrapper::load_glyph(const unsigned int glyph_index) const -> glyph
{
    return internal::load_glyph(face_.get(), has_color_emoji_, dimensions_px_, glyph_index);
}

auto face_wrapper::line_height() const -> int
{
    return line_height_;
}

} // namespace aeon::fonts

// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/fonts/glyph.h>
#include <aeon/streams/idynamic_stream.h>
#include <aeon/imaging/image.h>
#include <memory>
#include <vector>

// Forward declare for FreeType.
struct FT_LibraryRec_;
struct FT_FaceRec_;

namespace aeon::fonts
{

namespace internal
{

auto create_freetype_face(FT_LibraryRec_ *library, const std::vector<std::uint8_t> &data, const int index)
    -> FT_FaceRec_ *;
void free_freetype_face(FT_FaceRec_ *face);

} // namespace internal

class face_wrapper
{
public:
    face_wrapper(FT_LibraryRec_ *library, streams::idynamic_stream &stream, const float points, const int dpi);
    ~face_wrapper();

    face_wrapper(const face_wrapper &) = delete;
    auto operator=(const face_wrapper &) -> face_wrapper & = delete;

    face_wrapper(face_wrapper &&) noexcept = default;
    auto operator=(face_wrapper &&) noexcept -> face_wrapper & = default;

    auto get_char_index(const char32_t control_code) const -> unsigned int;

    /*!
     * Load a glyph. Loading the next glyph will re-use the same buffer,
     * so be sure to copy the image somewhere first before loading the next glyph.
     */
    auto load_glyph(const unsigned int glyph_index) const -> glyph;

private:
    std::vector<char> face_data_;
    std::unique_ptr<FT_FaceRec_, decltype(&internal::free_freetype_face)> face_;
    bool has_color_emoji_;
    int dimensions_px_;
};

} // namespace aeon::fonts

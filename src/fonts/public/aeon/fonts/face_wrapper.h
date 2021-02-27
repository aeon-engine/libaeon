// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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

[[nodiscard]] auto create_freetype_face(FT_LibraryRec_ *library, const std::vector<std::uint8_t> &data, const int index)
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

    [[nodiscard]] auto get_char_index(const char32_t control_code) const -> unsigned int;

    /*!
     * Get the first valid control code and its glyph index
     * \return Tuple of the control code and the glyph index
     */
    [[nodiscard]] auto load_first_index() const -> std::tuple<char32_t, unsigned int>;

    /*!
     * Get the next valid control code and its glyph index from the given control code
     * \return Tuple of the control code and the glyph index
     */
    [[nodiscard]] auto load_next_index(const char32_t control_code) const -> std::tuple<char32_t, unsigned int>;

    /*!
     * Load a glyph. Loading the next glyph will re-use the same buffer,
     * so be sure to copy the image somewhere first before loading the next glyph.
     */
    [[nodiscard]] auto load_glyph(const unsigned int glyph_index) const -> glyph;

    /*!
     * Get the default line height in pixels
     */
    [[nodiscard]] auto line_height() const -> int;

private:
    std::vector<char> face_data_;
    std::unique_ptr<FT_FaceRec_, decltype(&internal::free_freetype_face)> face_;
    bool has_color_emoji_;
    int dimensions_px_;
    int line_height_;
};

} // namespace aeon::fonts

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

#pragma once

#include <aeon/fonts/glyph.h>
#include <aeon/streams/stream_fwd.h>
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
    face_wrapper(FT_LibraryRec_ *library, streams::stream &stream, const float points, const int dpi);
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
    std::vector<std::uint8_t> face_data_;
    std::unique_ptr<FT_FaceRec_, decltype(&internal::free_freetype_face)> face_;
    bool has_color_emoji_;
    int dimensions_px_;
};

} // namespace aeon::fonts

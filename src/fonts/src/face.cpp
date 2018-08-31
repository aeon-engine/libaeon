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
#include <aeon/fonts/face_wrapper.h>
#include <aeon/streams/stream.h>

namespace aeon::fonts
{

face::face(FT_LibraryRec_ *library, streams::stream &stream, const float points, const int dpi)
{
    faces_.emplace_back(std::make_unique<face_wrapper>(library, stream, points, dpi));
}

face::face(FT_LibraryRec_ *library, const std::vector<std::reference_wrapper<streams::stream>> &streams,
           const float points, const int dpi)
{
    for (const auto &stream : streams)
    {
        faces_.emplace_back(std::make_unique<face_wrapper>(library, stream, points, dpi));
    }
}

face::~face() = default;

auto face::load_glyph(const char32_t control_code) const -> glyph
{
    for (const auto &face : faces_)
    {
        const auto char_index = face->get_char_index(control_code);

        if (char_index == 0)
            continue;

        return face->load_glyph(char_index);
    }

    // If none of the fonts have the glyph, grab the special glyph from the first face.
    return faces_.at(0)->load_glyph(0);
}

} // namespace aeon::fonts

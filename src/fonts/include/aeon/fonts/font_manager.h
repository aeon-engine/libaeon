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

#include <aeon/fonts/face.h>
#include <aeon/fonts/config.h>
#include <memory>

// Forward declare for FreeType.
struct FT_LibraryRec_;

namespace aeon::fonts
{

namespace internal
{

auto create_freetype_library() -> FT_LibraryRec_ *;
void free_freetype_library(FT_LibraryRec_ *library);

} // namespace internal

class font_manager
{
public:
    font_manager();
    ~font_manager();

    font_manager(const font_manager &) = delete;
    auto operator=(const font_manager &) -> font_manager & = delete;

    font_manager(font_manager &&) noexcept = delete;
    auto operator=(font_manager &&) noexcept -> font_manager & = delete;

    auto load_face(streams::stream &stream, const float points = AEON_FONT_DEFAULT_POINTS,
                   const int dpi = AEON_FONT_DEFAULT_DPI) const -> face;

private:
    std::unique_ptr<FT_LibraryRec_, decltype(&internal::free_freetype_library)> freetype_;
};

} // namespace aeon::fonts

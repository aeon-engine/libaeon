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

#include <aeon/imaging/file/png_structs.h>

namespace aeon::imaging::file::png::detail
{

class png_read_structs : public png_structs
{
public:
    png_read_structs();
    ~png_read_structs();

    png_read_structs(const png_read_structs &) = delete;
    auto operator=(const png_read_structs &) -> png_read_structs & = delete;

    png_read_structs(png_read_structs &&o) = default;
    auto operator=(png_read_structs &&other) -> png_read_structs & = default;
};

inline png_read_structs::png_read_structs()
{
    png_ptr_ = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    info_ptr_ = create_info_struct();
    end_info_ = create_info_struct();
}

inline png_read_structs::~png_read_structs()
{
    png_destroy_read_struct(&png_ptr_, &info_ptr_, &end_info_);
}

} // namespace aeon::imaging::file::png::detail

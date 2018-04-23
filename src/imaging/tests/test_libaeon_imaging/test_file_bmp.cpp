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

#include <gtest/gtest.h>

#include <aeon/imaging/file/bmp_file.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/converters/stride.h>
#include <aeon/imaging/converters/convert_encoding.h>

#include "imaging_unittest_data.h"

using namespace aeon;

TEST(test_imaging, test_load_bmp)
{
    const auto image = imaging::file::bmp::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.bmp");

    auto new_image = imaging::convert::remove_stride(image);
    new_image = imaging::convert::to_rgb24(new_image);

    imaging::file::png::save(new_image, "test_load_bmp.png");
}

// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/filters/fill.h>
#include "imaging_unittest_data.h"
#include <gtest/gtest.h>

using namespace aeon;

TEST(test_imaging, test_fill)
{
    const imaging::image_descriptor<imaging::rgb24> d{256, 256};
    const imaging::image<imaging::rgb24> image{d};

    auto view1 = imaging::make_view(image, {0, 0, 64, 64});
    imaging::filters::fill(view1, {255, 0, 0});

    auto view2 = imaging::make_view(image, {200, 200, 220, 255});
    imaging::filters::fill(view2, {0, 255, 0});

    auto view3 = imaging::make_view(image, {140, 100, 210, 160});
    imaging::filters::fill(view3, {0, 0, 255});

    imaging::file::png::save(image, "test_fill_rgb24.png");
}

TEST(test_imaging, test_fill_rect)
{
    const imaging::image_descriptor<imaging::rgb24> d{256, 256};
    imaging::image<imaging::rgb24> image{d};

    imaging::filters::fill(image, {0, 0, 64, 64}, {255, 0, 0});
    imaging::filters::fill(image, {200, 200, 220, 255}, {0, 255, 0});
    imaging::filters::fill(image, {140, 100, 210, 160}, {0, 0, 255});

    imaging::file::png::save(image, "test_fill_rect_rgb24.png");
}

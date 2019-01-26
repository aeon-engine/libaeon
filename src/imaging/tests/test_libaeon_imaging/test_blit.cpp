// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>

#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/filters/blit.h>

#include "imaging_unittest_data.h"

using namespace aeon;

TEST(test_imaging, test_blit)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);

    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto d = imaging::image_descriptor<imaging::rgba32>{256, 256};
    auto dst = imaging::image{d};

    auto view1 = imaging::make_view(image, {0, 0, 64, 64});
    imaging::filters::blit(view1, dst, {10, 10});

    auto view2 = imaging::make_view(image, {128, 128, 150, 160});
    imaging::filters::blit(view2, dst, {40, 40});

    auto view3 = imaging::make_view(image, {140, 100, 210, 160});
    imaging::filters::blit(view3, dst, {100, 100});

    imaging::file::png::save(dst, "test_blit.png");
}

TEST(test_imaging, test_blit_add_blend)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);

    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto d = imaging::image_descriptor<imaging::rgba32>{256, 256};
    auto dst = imaging::image{d};

    auto view1 = imaging::make_view(image, {0, 0, 64, 64});
    imaging::filters::blend_blit(view1, dst, {10, 10}, imaging::filters::blend_blit_mode::add);

    auto view2 = imaging::make_view(image, {128, 128, 150, 160});
    imaging::filters::blend_blit(view2, dst, {40, 40}, imaging::filters::blend_blit_mode::add);

    auto view3 = imaging::make_view(image, {140, 100, 210, 160});
    imaging::filters::blend_blit(view3, dst, {100, 100}, imaging::filters::blend_blit_mode::add);

    imaging::file::png::save(dst, "test_blit_add.png");
}

TEST(test_imaging, test_scale_blit)
{
    const auto dynamic_image = imaging::file::png::load(AEON_IMAGING_UNITTEST_DATA_PATH "felix.png");
    ASSERT_EQ(imaging::encoding(dynamic_image), imaging::pixel_encoding::rgba32);

    auto &image = dynamic_image.get_image<imaging::rgba32>();

    const auto d = imaging::image_descriptor<imaging::rgba32>{256, 256};
    auto dst = imaging::image{d};

    auto view1 = imaging::make_view(image, {0, 0, 64, 64});
    imaging::filters::scale_blit(view1, dst, {10, 10, 246, 246});

    auto view2 = imaging::make_view(image, {140, 100, 210, 160});
    imaging::filters::scale_blit(view2, dst, {16, 16, 32, 32});

    imaging::file::png::save(dst, "test_scale_blit.png");
}

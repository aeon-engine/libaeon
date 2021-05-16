// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/fonts/font_manager.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/filters/resize.h>
#include <aeon/imaging/utils/atlas.h>
#include <aeon/common/preprocessor.h>
#include <aeon/unicode/utf_string_view.h>
#include "fonts_unittest_data.h"

#include <gtest/gtest.h>

using namespace aeon;
using namespace std::literals;

TEST(test_fonts, test_font_manager_init)
{
    ASSERT_NO_THROW(fonts::font_manager mgr;);
}

TEST(test_fonts, test_load_glyph)
{
    fonts::font_manager mgr;
    auto font_file = streams::make_dynamic_stream(
        streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "SourceSansPro-Black.ttf"});
    const auto face = mgr.load_face(font_file, 16.0f);
    const auto glyph = face.load_glyph('A');

    ASSERT_FALSE(math::null(glyph.view()));
    ASSERT_EQ(glyph.pixel_type(), fonts::glyph_pixel_type::gray);

    const auto rgb_image = imaging::swizzle_copy<math::swizzle_r, math::swizzle_r, math::swizzle_r>(
        glyph.view(), imaging::pixel_encoding::rgb);
    imaging::file::png::save(rgb_image, "test_fonts_a.png");
}

TEST(test_fonts, test_load_rgb_glyph)
{
    fonts::font_manager mgr;
    auto font_file =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "NotoColorEmoji.ttf"});
    const auto face = mgr.load_face(font_file, 16.0f);
    const auto glyph = face.load_glyph(0x1F600); // "Grinning Face"

    ASSERT_FALSE(math::null(glyph.view()));
    ASSERT_EQ(glyph.pixel_type(), fonts::glyph_pixel_type::color);

    const auto rgb_image = imaging::swizzle_copy<math::swizzle_b, math::swizzle_g, math::swizzle_r>(
        glyph.view(), imaging::pixel_encoding::rgb);
    imaging::file::png::save(rgb_image, "test_fonts_emoji.png");
}

static auto generate_text_image(const fonts::face &face, const std::u8string &str) -> imaging::image
{
    imaging::image image{common::element_type::u8_3, imaging::pixel_encoding::rgb, 1024, 256};

    math::vector2<int> position{30, 60};

    unicode::utf_string_view view{str};

    for (const auto c : view)
    {
        if (c == '\r')
            continue;

        if (c == '\n')
        {
            position.x = 30;
            position.y += 50;
            continue;
        }

        const auto glyph = face.load_glyph(c);

        if (glyph.has_view())
        {
            if (glyph.pixel_type() == fonts::glyph_pixel_type::gray)
                math::blit(imaging::swizzle_copy<math::swizzle_r, math::swizzle_r, math::swizzle_r>(
                               glyph.view(), imaging::pixel_encoding::rgb),
                           image, position + math::vector2<int>{glyph.offset()});
            else if (glyph.pixel_type() == fonts::glyph_pixel_type::color)
            {
                const auto scaled_glyph = imaging::filters::resize_bilinear(
                    glyph.view(), math::size2d<imaging::image::dimensions_type>{glyph.dimensions()});
                math::blit(imaging::swizzle_copy<math::swizzle_b, math::swizzle_g, math::swizzle_r>(
                               scaled_glyph, imaging::pixel_encoding::rgb),
                           image, position + math::vector2<int>{glyph.offset()});
            }
        }

        position.x += static_cast<int>(glyph.advance().x);
    }

    return image;
}

TEST(test_fonts, test_load_text_string)
{
    fonts::font_manager mgr;
    auto font_file1 = streams::make_dynamic_stream(
        streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "mikiyu-newpenji-p.ttf"});
    auto font_file2 =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "NotoColorEmoji.ttf"});

    const auto face = mgr.load_multi_face({font_file1, font_file2}, 40.0f);

    auto text_file =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "lucky_star.txt"});

    streams::stream_reader reader{text_file};
    const auto image = generate_text_image(face, reader.read_to_u8string());

    imaging::file::png::save(image, "test_fonts_text.png");
}

TEST(test_fonts, test_load_text_string_blit_emoji)
{
    fonts::font_manager mgr;
    auto font_file =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "Precious.ttf"});

    // Generate text image
    const auto face = mgr.load_face(font_file, 40.0f);
    const auto str = aeon_text("Lorem ipsum dolor sit amet...\nconsectetur adipiscing elit.\nsed do eiusmod tempor "
                               "incididunt ut\nlabore et dolore magna aliqua.");
    auto text_image = imaging::swizzle_copy<math::swizzle_r, math::swizzle_r, math::swizzle_r, math::swizzle_max>(
        generate_text_image(face, str), imaging::pixel_encoding::rgba);

    // Generate color emoji
    auto font_file2 =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "NotoColorEmoji.ttf"});
    const auto face2 = mgr.load_face(font_file2, 16.0f);
    const auto glyph = face2.load_glyph(0x1F600); // "Grinning Face"
    const auto emoji_image =
        imaging::swizzle_copy<math::swizzle_b, math::swizzle_g, math::swizzle_r, math::swizzle_max>(
            glyph.view(), imaging::pixel_encoding::rgba);

    // Blit them together
    math::blit(emoji_image, text_image, {100, 100});

    imaging::file::png::save(text_image, "test_fonts_text_emoji_blend.png");
}

TEST(test_fonts, test_load_glyphs_as_atlas)
{
    fonts::font_manager mgr;
    auto font_file =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "ProggyClean.ttf"});
    const auto face = mgr.load_face(font_file, 13.0f);

    std::vector<imaging::image> glyphs;

    auto result = face.load_first_glyph();

    while (true)
    {
        if (!std::empty(glyphs) && std::get<0>(result) == 0)
            break;

        if (std::get<1>(result).has_view())
            glyphs.emplace_back(std::get<1>(result).view());

        result = face.load_next_glyph(std::get<0>(result));
    }

    auto atlas = imaging::utils::create_atlas(glyphs);

    const auto rgb_image = imaging::swizzle_copy<math::swizzle_r, math::swizzle_r, math::swizzle_r>(
        atlas.img, imaging::pixel_encoding::rgb);
    imaging::file::png::save(rgb_image, "font_atlas.png");
}

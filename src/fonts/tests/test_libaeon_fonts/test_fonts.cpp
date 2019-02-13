// Copyright (c) 2012-2019 Robin Degen

#include <gtest/gtest.h>

#include <aeon/fonts/font_manager.h>
#include <aeon/streams/devices/file_device.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/imaging/file/png_file.h>
#include <aeon/imaging/filters/blit.h>
#include <aeon/imaging/converters/convert_encoding.h>
#include <aeon/common/preprocessor.h>
#include <aeon/unicode/utf_string_view.h>
#include "fonts_unittest_data.h"

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

    ASSERT_FALSE(imaging::null(glyph.view()));
    ASSERT_TRUE(imaging::null(glyph.color_view()));
    ASSERT_EQ(glyph.pixel_type(), fonts::glyph_pixel_type::gray);

    const auto rgb_image = imaging::convert::to_rgb24(glyph.view());
    imaging::file::png::save(rgb_image, "test_fonts_a.png");
}

TEST(test_fonts, test_load_rgb_glyph)
{
    fonts::font_manager mgr;
    auto font_file =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "NotoColorEmoji.ttf"});
    const auto face = mgr.load_face(font_file, 16.0f);
    const auto glyph = face.load_glyph(0x1F600); // "Grinning Face"

    ASSERT_TRUE(imaging::null(glyph.view()));
    ASSERT_FALSE(imaging::null(glyph.color_view()));
    ASSERT_EQ(glyph.pixel_type(), fonts::glyph_pixel_type::color);

    const auto rgb_image = imaging::convert::to_rgb24(glyph.color_view());
    imaging::file::png::save(rgb_image, "test_fonts_emoji.png");
}

static auto generate_text_image(const fonts::face &face, const std::string &str) -> imaging::image<imaging::rgb24>
{
    const imaging::image_descriptor<imaging::rgb24> descriptor{{1024, 256}};
    imaging::image image{descriptor};

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

        if (imaging::valid(glyph.view()))
            imaging::filters::blend_blit(imaging::convert::to_rgb24(glyph.view()), image, position + glyph.offset(),
                                         imaging::filters::blend_blit_mode::add);

        if (imaging::valid(glyph.color_view()))
            imaging::filters::blend_scale_blit(
                imaging::convert::to_rgb24(glyph.color_view()), image,
                {position + glyph.offset(), math::size2d<imaging::dimension>{glyph.dimensions(), glyph.dimensions()}},
                imaging::filters::blend_blit_mode::add);

        position.x += glyph.advance().x;
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
    const auto image = generate_text_image(face, reader.read_to_string());

    const auto rgb_image = imaging::convert::to_rgb24(image);
    imaging::file::png::save(rgb_image, "test_fonts_text.png");
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
    auto text_image = imaging::convert::to_rgba32(generate_text_image(face, str));

    // Generate color emoji
    auto font_file2 =
        streams::make_dynamic_stream(streams::file_source_device{AEON_FONTS_UNITTEST_DATA_PATH "NotoColorEmoji.ttf"});
    const auto face2 = mgr.load_face(font_file2, 16.0f);
    const auto glyph = face2.load_glyph(0x1F600); // "Grinning Face"
    const auto emoji_image = imaging::convert::to_rgba32(glyph.color_view());

    // Blend them together
    imaging::filters::blend_blit(emoji_image, text_image, {100, 100}, imaging::filters::blend_blit_mode::alpha);

    imaging::file::png::save(text_image, "test_fonts_text_emoji_blend.png");
}

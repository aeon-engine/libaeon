// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/gl_utils/check_error.h>
#include <aeon/gl_utils/texture.h>
#include <aeon/gl/exception.h>

namespace aeon::gl_utils
{

namespace internal
{

[[nodiscard]] auto convert_pixel_format(const imaging::image_view &image, const monochrome_type monochrome_type)
    -> GLenum
{
    switch (imaging::pixel_format(image))
    {

        case imaging::format::b8g8r8_uint:
            return GL_BGR;
        case imaging::format::b8g8r8a8_uint:
            return GL_BGRA;
        case imaging::format::r32_float:
        case imaging::format::r32_uint:
        case imaging::format::r8_uint:
            return static_cast<GLenum>(monochrome_type);
        case imaging::format::r32g32_float:
        case imaging::format::r32g32_uint:
        case imaging::format::r8g8_uint:
            return GL_RG;
        case imaging::format::r32g32b32_float:
        case imaging::format::r32g32b32_uint:
        case imaging::format::r8g8b8_uint:
            return GL_RGB;
        case imaging::format::r32g32b32a32_float:
        case imaging::format::r32g32b32a32_uint:
        case imaging::format::r8g8b8a8_uint:
            return GL_RGBA;
        case imaging::format::bc1_rgb_srgb_block:
        case imaging::format::bc1_rgba_srgb_block:
        case imaging::format::bc2_srgb_block:
        case imaging::format::bc3_srgb_block:
        case imaging::format::undefined:
        default:
            throw gl::gl_exception{u8"Invalid or unsupported pixel format."};
    }
}

[[nodiscard]] auto convert_type(const imaging::image_view &image) -> GLenum
{
    const auto element_type = math::element_type(image);

    switch (element_type.name)
    {
        case common::element_type_name::u8:
            return GL_UNSIGNED_BYTE;
        case common::element_type_name::u16:
            return GL_UNSIGNED_SHORT;
        case common::element_type_name::u32:
            return GL_UNSIGNED_INT;
        case common::element_type_name::f32:
            return GL_FLOAT;
        case common::element_type_name::s8:
        case common::element_type_name::s16:
        case common::element_type_name::s32:
        case common::element_type_name::u64:
        case common::element_type_name::s64:
        case common::element_type_name::f64:
        case common::element_type_name::undefined:
        default:
            throw gl::gl_exception{u8"Invalid or unsupported pixel type."};
    }
}

} // namespace internal

auto create_texture(const imaging::image_view &image, const texture_min_filter min_filter,
                    const texture_mag_filter max_filter, const monochrome_type monochrome_type) -> GLuint
{
    GLuint handle = 0;
    aeon_check_gl_error(glGenTextures(1, &handle));
    aeon_check_gl_error(glBindTexture(GL_TEXTURE_2D, handle));

    const auto width = math::width(image);
    const auto height = math::height(image);
    const auto pixel_format = internal::convert_pixel_format(image, monochrome_type);
    const auto type = internal::convert_type(image);

    aeon_check_gl_error(
        glTexImage2D(GL_TEXTURE_2D, 0, pixel_format, width, height, 0, pixel_format, type, std::data(image)));

    aeon_check_gl_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(min_filter)));
    aeon_check_gl_error(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(max_filter)));

    return handle;
}

} // namespace aeon::gl_utils

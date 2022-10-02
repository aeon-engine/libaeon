// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/imaging/image_view.h>
#include <aeon/gl/aeon_opengl.h>

namespace aeon::gl_utils
{

enum class texture_min_filter : GLenum
{
    nearest = GL_NEAREST,
    linear = GL_LINEAR,
    nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
    linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
    nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
    linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR
};

enum class texture_mag_filter : GLenum
{
    nearest = GL_NEAREST,
    linear = GL_LINEAR
};

enum class monochrome_type : GLenum
{
    red = GL_RED,
    green = GL_GREEN,
    blue = GL_BLUE,
    alpha = GL_ALPHA,
    luminance = GL_LUMINANCE,
    intensity = GL_INTENSITY,
    depth_component = GL_DEPTH_COMPONENT
};

[[nodiscard]] auto create_texture(const imaging::image_view &image,
                                  const texture_min_filter min_filter = texture_min_filter::linear,
                                  const texture_mag_filter max_filter = texture_mag_filter::linear,
                                  const monochrome_type monochrome_type = monochrome_type::red) -> GLuint;

} // namespace aeon::gl_utils

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/imaging/iimage.h>
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

enum class texture_max_filter : GLenum
{
    nearest = GL_NEAREST,
    linear = GL_LINEAR
};

[[nodiscard]] auto create_texture(const imaging::iimage &image,
                                  const texture_min_filter min_filter = texture_min_filter::linear,
                                  const texture_max_filter max_filter = texture_max_filter::linear) -> GLuint;

} // namespace aeon::gl_utils

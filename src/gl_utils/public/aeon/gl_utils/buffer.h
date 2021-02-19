// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/gl/aeon_opengl.h>
#include <span>

namespace aeon::gl_utils
{

enum class buffer_type : GLenum
{
    array = GL_ARRAY_BUFFER,
    atomic_counter = GL_ATOMIC_COUNTER_BUFFER,
    copy_read = GL_COPY_READ_BUFFER,
    copy_write = GL_COPY_WRITE_BUFFER,
    dispatch_indirect = GL_DISPATCH_INDIRECT_BUFFER,
    draw_indirect = GL_DRAW_INDIRECT_BUFFER,
    element_array = GL_ELEMENT_ARRAY_BUFFER,
    pixel_pack = GL_PIXEL_PACK_BUFFER,
    pixel_unpack = GL_PIXEL_UNPACK_BUFFER,
    query = GL_QUERY_BUFFER,
    shader_storage = GL_SHADER_STORAGE_BUFFER,
    texture = GL_TEXTURE_BUFFER,
    transform_feedback = GL_TRANSFORM_FEEDBACK_BUFFER,
    uniform = GL_UNIFORM_BUFFER
};

enum class buffer_usage : GLenum
{
    stream_draw = GL_STREAM_DRAW,
    stream_read = GL_STREAM_READ,
    stream_copy = GL_STREAM_COPY,
    static_draw = GL_STATIC_DRAW,
    static_read = GL_STATIC_READ,
    static_copy = GL_STATIC_COPY,
    dynamic_draw = GL_DYNAMIC_DRAW,
    dynamic_read = GL_DYNAMIC_READ,
    dynamic_copy = GL_DYNAMIC_COPY
};

[[nodiscard]] auto create_buffer() -> GLuint;

void set_buffer_data(const GLuint handle, const buffer_type type, const std::span<std::byte> &data,
                     const buffer_usage usage);

void bind_buffer(const buffer_type type, const GLuint handle);

[[nodiscard]] auto create_buffer(const buffer_type type, const std::span<std::byte> &data, const buffer_usage usage)
    -> GLuint;

} // namespace aeon::gl_utils

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/gl_utils/buffer.h>
#include <aeon/gl_utils/check_error.h>

namespace aeon::gl_utils
{

auto create_buffer() -> GLuint
{
    GLuint handle;
    aeon_check_gl_error(glGenBuffers(1, &handle));
    return handle;
}

void set_buffer_data(const GLuint handle, const buffer_type type, const std::span<const std::byte> &data,
                     const buffer_usage usage)
{
    aeon_check_gl_error(glBindBuffer(static_cast<GLenum>(type), handle));
    aeon_check_gl_error(
        glBufferData(static_cast<GLenum>(type), std::size(data), std::data(data), static_cast<GLenum>(usage)));
}

void bind_buffer(const buffer_type type, const GLuint handle)
{
    aeon_check_gl_error(glBindBuffer(static_cast<GLenum>(type), handle));
}

auto create_buffer(const buffer_type type, const std::span<const std::byte> &data, const buffer_usage usage) -> GLuint
{
    const auto handle = create_buffer();
    set_buffer_data(handle, type, data, usage);
    return handle;
}

} // namespace aeon::gl_utils

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/gl_utils/check_error.h>
#include <aeon/gl/aeon_opengl.h>
#include <iostream>

namespace aeon::gl_utils::internal
{

#if (defined(AEON_ENABLE_GL_ERROR_CHECKS))
void check_gl_error(const char *command, const char *file, const int line)
{
    auto count = 0;

    auto result = glGetError();
    while (result != GL_NO_ERROR)
    {
        if (++count >= 100)
        {
            std::cerr << "Too many OpenGL errors detected (> 100)" << std::endl;
            break;
        }

        const char *error_message;
        switch (result)
        {
            case GL_INVALID_ENUM:
                error_message = "Invalid enum.";
                break;
            case GL_INVALID_VALUE:
                error_message = "Invalid value.";
                break;
            case GL_INVALID_OPERATION:
                error_message = "Invalid operation.";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error_message = "Invalid framebuffer operation.";
                break;
            case GL_OUT_OF_MEMORY:
                error_message = "Out of memory";
                break;
            default:
                error_message = "Unknown error.";
        }

        std::cerr << "OpenGL error: " << '\n';
        std::cerr << "    " << command << "(" << file << ":" << line << ")\n";
        std::cerr << "    Description: " << error_message << ".\n";

        result = glGetError();
    }
}
#endif

} // namespace aeon::gl_utils::internal

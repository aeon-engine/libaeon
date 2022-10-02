// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/gl_utils/gl_utils_settings.h>
#include <aeon/common/preprocessor.h>

#if (defined(AEON_ENABLE_GL_ERROR_CHECKS))
namespace aeon::gl_utils::internal
{

void check_gl_error(const char *command, const char *file, const int line);

} // namespace aeon::gl_utils::internal

/*!
 * Check for OpenGL errors through glGetError and report them in the console.
 */
#define aeon_check_gl_error(func)                                                                                      \
    func;                                                                                                              \
    aeon::gl_utils::internal::check_gl_error(#func, __FILE__, __LINE__)
#else
#define aeon_check_gl_error(func) func
#endif

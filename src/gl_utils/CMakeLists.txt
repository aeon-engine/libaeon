# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

option(AEON_ENABLE_GL_ERROR_CHECKS "Enable OpenGL call error checking through glGetError" ON)
configure_file(gl_utils_settings.h.in public/aeon/gl_utils/gl_utils_settings.h @ONLY)

set(SOURCES
    private/buffer.cpp
    private/check_error.cpp
    private/shader.cpp
    private/texture.cpp
    public/aeon/gl_utils/buffer.h
    public/aeon/gl_utils/check_error.h
    public/aeon/gl_utils/shader.h
    public/aeon/gl_utils/texture.h
    public/aeon/gl_utils/utils.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_gl_utils STATIC
    ${SOURCES}
)

set_target_properties(aeon_gl_utils PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_gl_utils
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
)

target_link_libraries(aeon_gl_utils
    aeon_common
    aeon_gl
    aeon_imaging
    aeon_math
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

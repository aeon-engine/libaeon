# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

find_package(opengl-registry CONFIG)

include(GenerateExportHeader)

add_subdirectory(generator)

set(SOURCES
    public/aeon/gl/exception.h
    public/aeon/gl/opengl.h
    public/aeon/gl/opengl_context.h
    public/aeon/gl/opengl_context_create_info.h
)

if (WIN32)
    list(APPEND SOURCES
        private/wgl/scoped_context.h
        private/wgl/wgl.cpp
        private/wgl/wgl.h
        private/wgl/wgl_opengl_context.h
    )
endif ()

# Linux is not yet supported.
# if (UNIX AND NOT APPLE)
#     list(APPEND SOURCES
#         private/glx/glx.cpp
#     )
# endif ()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_gl
    ${SOURCES}
)

generate_export_header(aeon_gl
    EXPORT_FILE_NAME public/aeon/gl/gl_export.h
)

set_target_properties(aeon_gl PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_gl
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
        ${CMAKE_CURRENT_BINARY_DIR}/generator/public
)

target_link_libraries(aeon_gl
    aeon_common
    aeon_platform
    opengl-registry::opengl-registry
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

add_dependencies(aeon_gl aeon_gl_generator_runner)

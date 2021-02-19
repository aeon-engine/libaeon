# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(OPENGL_REGISTRY_DESTINATION_PATH ${CMAKE_CURRENT_BINARY_DIR}/public/aeon/gl)
file(MAKE_DIRECTORY "${OPENGL_REGISTRY_DESTINATION_PATH}")

configure_file(opengl_registry_info.h.in opengl_registry_info.h @ONLY)

set(LIB_AEON_GL_GENERATOR_PRIVATE_SOURCE
    private/generator.cpp
    private/generator.h
    private/main.cpp
    private/model.h
    private/parser.cpp
    private/parser.h
)

source_group(private FILES ${LIB_AEON_GL_GENERATOR_PRIVATE_SOURCE})

add_executable(aeon_gl_generator
    ${LIB_AEON_GL_GENERATOR_PRIVATE_SOURCE}
)

set_target_properties(aeon_gl_generator PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_gl_generator
    PRIVATE
        private
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(aeon_gl_generator
    aeon_common
    aeon_ptree
    aeon_streams
)

add_custom_target(aeon_gl_generator_runner
    aeon_gl_generator
)

set_target_properties(aeon_gl_generator_runner PROPERTIES
    FOLDER dep/libaeon
)

add_dependencies(aeon_gl_generator_runner aeon_gl_generator)

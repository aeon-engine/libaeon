# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

find_package(glfw3 CONFIG)

include(GenerateExportHeader)

set(SOURCES
    private/base_context.cpp
    private/base_context.h
    private/base_window.cpp
    private/base_window.h
    private/platforms/glfw/glfw_context.cpp
    private/platforms/glfw/glfw_context.h
    private/platforms/glfw/glfw_exception.h
    private/platforms/glfw/glfw_init.h
    private/platforms/glfw/glfw_scoped_window.h
    private/platforms/glfw/glfw_window.cpp
    private/platforms/glfw/glfw_window.h
    public/aeon/platform/context.h
    public/aeon/platform/exception.h
    public/aeon/platform/input_events.h
    public/aeon/platform/keyboard_key.h
    public/aeon/platform/keyboard_key_state.h
    public/aeon/platform/mouse_button.h
    public/aeon/platform/mouse_button_state.h
    public/aeon/platform/native_handles.h
    public/aeon/platform/window.h
    public/aeon/platform/window_create_info.h
    public/aeon/platform/window_events.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_platform
    ${SOURCES}
)

generate_export_header(aeon_platform
    EXPORT_FILE_NAME public/aeon/platform/platform_export.h
)

set_target_properties(aeon_platform PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_platform
    PUBLIC
        public
        ${CMAKE_CURRENT_BINARY_DIR}/public
    PRIVATE
        private
)

target_link_libraries(aeon_platform
    aeon_common
    aeon_math
    glfw::glfw
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

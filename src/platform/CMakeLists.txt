# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(GenerateExportHeader)

set(SOURCES
    private/base_context.cpp
    private/base_context.h
    public/aeon/platform/context.h
    public/aeon/platform/exception.h
    public/aeon/platform/input_events.h
    public/aeon/platform/modifier_keys_state.h
    public/aeon/platform/native_handles.h
    public/aeon/platform/window.h
    public/aeon/platform/window_create_info.h
    public/aeon/platform/window_events.h
)

if (WIN32)
    list(APPEND SOURCES
        private/platforms/windows/context.cpp
        private/platforms/windows/context.h
        private/platforms/windows/exception.h
        private/platforms/windows/scoped_window_class.cpp
        private/platforms/windows/scoped_window_class.h
        private/platforms/windows/scoped_window_handle.h
        private/platforms/windows/utility.h
        private/platforms/windows/window.cpp
        private/platforms/windows/window.h
    )
endif ()

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
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

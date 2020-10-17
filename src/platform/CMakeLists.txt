# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(GenerateExportHeader)

set(LIB_AEON_PLATFORM_PUBLIC_SOURCE
    include/aeon/platform/context.h
    include/aeon/platform/exception.h
    include/aeon/platform/input_events.h
    include/aeon/platform/modifier_keys_state.h
    include/aeon/platform/window.h
    include/aeon/platform/window_create_info.h
    include/aeon/platform/window_events.h
)

source_group(public FILES ${LIB_AEON_PLATFORM_PUBLIC_SOURCE})

set(LIB_AEON_PLATFORM_PRIVATE_SOURCE
    src/base_context.cpp
    src/base_context.h
)

source_group(private FILES ${LIB_AEON_PLATFORM_PRIVATE_SOURCE})

set(LIB_AEON_PLATFORM_PRIVATE_PLATFORM_SOURCE)

if (WIN32)
    list(APPEND LIB_AEON_PLATFORM_PRIVATE_PLATFORM_SOURCE
        src/platforms/windows/context.cpp
        src/platforms/windows/context.h
        src/platforms/windows/exception.h
        src/platforms/windows/scoped_window_class.cpp
        src/platforms/windows/scoped_window_class.h
        src/platforms/windows/scoped_window_handle.h
        src/platforms/windows/utility.h
        src/platforms/windows/window.cpp
        src/platforms/windows/window.h
    )

    source_group(private\\platforms\\windows FILES ${LIB_AEON_PLATFORM_PRIVATE_PLATFORM_SOURCE})
endif ()

add_library(aeon_platform
    ${LIB_AEON_PLATFORM_PUBLIC_SOURCE}
    ${LIB_AEON_PLATFORM_PRIVATE_SOURCE}
    ${LIB_AEON_PLATFORM_PRIVATE_PLATFORM_SOURCE}
)

generate_export_header(aeon_platform
    EXPORT_FILE_NAME include/aeon/platform/platform_export.h
)

set_target_properties(aeon_platform PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_platform
    PUBLIC
        include
        ${CMAKE_CURRENT_BINARY_DIR}/include
    PRIVATE
        src
)

target_link_libraries(aeon_platform
    aeon_common
    aeon_math
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

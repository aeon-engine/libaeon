# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(SOURCES
    private/plugin.cpp
    private/plugin_loader.cpp
    public/aeon/plugins/plugin.h
    public/aeon/plugins/plugin_loader.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_plugins STATIC
    ${SOURCES}
)

set_target_properties(aeon_plugins PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_plugins
    PUBLIC
        public
)

target_link_libraries(aeon_plugins
    aeon_common
)

# On linux, the plugin library and all plugins must be build with
# position independent code (-fPIC)
if (UNIX AND NOT APPLE)
    set_target_properties(aeon_plugins PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_plugins
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

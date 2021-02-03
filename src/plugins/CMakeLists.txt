# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(LIB_AEON_PLUGINS_PUBLIC_SOURCE
    include/aeon/plugins/plugin.h
    include/aeon/plugins/plugin_loader.h
)

source_group(public FILES ${LIB_AEON_PLUGINS_PUBLIC_SOURCE})

set(LIB_AEON_PLUGINS_PRIVATE_SOURCE
    src/plugin.cpp
    src/plugin_loader.cpp
)

source_group(private FILES ${LIB_AEON_PLUGINS_PRIVATE_SOURCE})

add_library(aeon_plugins STATIC
    ${LIB_AEON_PLUGINS_PUBLIC_SOURCE}
    ${LIB_AEON_PLUGINS_PRIVATE_SOURCE}
)

set_target_properties(aeon_plugins PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_plugins
    PUBLIC
        include
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
    DIRECTORY include/aeon
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

# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_PLUGINS_SOURCE
    include/aeon/plugins/plugin.h
    src/plugin.cpp
    include/aeon/plugins/plugin_loader.h
    src/plugin_loader.cpp
)

source_group(plugins FILES ${LIB_AEON_PLUGINS_SOURCE})

add_library(aeon_plugins STATIC ${LIB_AEON_PLUGINS_SOURCE})

set_target_properties(aeon_plugins PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_plugins PUBLIC include)
target_link_libraries(aeon_plugins aeon_common aeon_utility)

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

add_subdirectory(tests)

# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

add_library(testplugin1 SHARED
    src/testplugin1.cpp
    include/itestplugin1.h
)

target_link_libraries(testplugin1 aeon_plugins)

target_include_directories(testplugin1 PRIVATE include)

set_target_properties(testplugin1 PROPERTIES
    FOLDER dep/libaeon/tests/plugins
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    PREFIX ""
)

# On linux, the plugin library and all plugins must be build with
# position independent code (-fPIC)
if (UNIX AND NOT APPLE)
    set_target_properties(testplugin1 PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
endif ()

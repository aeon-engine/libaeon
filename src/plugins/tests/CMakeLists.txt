# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_plugins
    SOURCES
        main.cpp
        test_plugin_loader.cpp
    LIBRARIES aeon_plugins
    INCLUDES plugins/include
    FOLDER dep/libaeon/tests
)

add_subdirectory(plugins)

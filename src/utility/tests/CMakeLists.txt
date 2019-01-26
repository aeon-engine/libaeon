# Copyright (c) 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_utility
    SOURCES
        main.cpp
        test_configfile.cpp
        test_dispatcher.cpp
        test_linear_map.cpp
        test_signals.cpp
        test_tribool.cpp
        test_uuid.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_utility aeon_testing
    FOLDER dep/libaeon/tests
)

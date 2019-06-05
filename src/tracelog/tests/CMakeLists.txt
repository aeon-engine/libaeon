# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_tracelog
    SOURCES
        main.cpp
        test_tracelog.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_tracelog
    FOLDER dep/libaeon/tests
)

# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_gl
    SOURCES
        main.cpp
        test_gl.cpp
    LIBRARIES aeon_gl
    FOLDER dep/libaeon/tests
)

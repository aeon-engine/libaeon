# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_reflection
    SOURCES
        main.cpp
        test_reflection.cpp
    LIBRARIES aeon_reflection aeon_common
    FOLDER dep/libaeon/tests
)

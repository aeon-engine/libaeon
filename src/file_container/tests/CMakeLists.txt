# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_file_container
    SOURCES
        main.cpp
        test_file_container.cpp
    LIBRARIES aeon_file_container
    FOLDER dep/libaeon/tests
)

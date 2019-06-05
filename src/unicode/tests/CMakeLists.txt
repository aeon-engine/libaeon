# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_unicode
    SOURCES
        main.cpp
        test_encoding.cpp
        test_iterator.cpp
    LIBRARIES aeon_unicode
    FOLDER dep/libaeon/tests
)

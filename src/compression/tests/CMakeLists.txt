# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_compression
    SOURCES
        main.cpp
        test_zlib_filter.cpp
    LIBRARIES aeon_compression aeon_streams
    FOLDER dep/libaeon/tests
)

# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_web
    SOURCES
        main.cpp
        test_sockets.cpp
        test_url_encoding.cpp
    LIBRARIES aeon_web aeon_common
    FOLDER dep/libaeon/tests
)

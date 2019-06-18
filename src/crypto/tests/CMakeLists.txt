# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_crypto
    SOURCES
        main.cpp
        test_sha256.cpp
        test_sha265_stream_filter.cpp
    LIBRARIES aeon_crypto aeon_streams
    FOLDER dep/libaeon/tests
)

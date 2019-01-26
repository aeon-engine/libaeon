# Copyright (c) 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_streams
    SOURCES
        main.cpp
        test_circular_buffer_stream.cpp
        test_memory_stream.cpp
        test_stream_reader.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_streams
    FOLDER dep/libaeon/tests
)

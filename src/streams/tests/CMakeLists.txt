# Copyright (c) 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_streams
    SOURCES
        main.cpp
        test_circular_buffer_filter.cpp
        test_dynamic_stream.cpp
        test_memory_device.cpp
        test_size_filter.cpp
        test_streams.cpp
        test_stream_reader.cpp
        test_stream_writer.cpp
        test_zlib_filter.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_streams
    FOLDER dep/libaeon/tests
)

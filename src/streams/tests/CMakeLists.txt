# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_streams
    SOURCES
        main.cpp
        test_aggregate_device.cpp
        test_buffer_filter.cpp
        test_circular_buffer_filter.cpp
        test_dynamic_stream.cpp
        test_memory_device.cpp
        test_size_filter.cpp
        test_stream_reader.cpp
        test_stream_writer.cpp
        test_streams.cpp
        test_uuid_stream.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_streams
    FOLDER dep/libaeon/tests
)

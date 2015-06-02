include(Unittests)

add_unit_test_suite(
    TARGET test_circular_buffer_stream
    SOURCES test_circular_buffer_stream.cpp
    LIBRARIES aeon
)

add_unit_test_suite(
    TARGET test_memory_stream
    SOURCES test_memory_stream.cpp
    LIBRARIES aeon
)

add_unit_test_suite(
    TARGET test_optional
    SOURCES test_optional.cpp
    LIBRARIES aeon
)

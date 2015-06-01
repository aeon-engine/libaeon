include(Unittests)

add_unit_test_suite(
    TARGET test_optional
    SOURCES test_optional.cpp
    LIBRARIES aeon
)

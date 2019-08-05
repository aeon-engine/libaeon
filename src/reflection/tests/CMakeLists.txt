# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_reflection
    SOURCES
        main.cpp
        test_reflection.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_reflection
    FOLDER dep/libaeon/tests
)

set(AEON_REFLECTION_UNITTEST_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/)
configure_file(reflection_unittest_data.h.in reflection_unittest_data.h @ONLY)

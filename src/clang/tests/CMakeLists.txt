# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_clang
    SOURCES
        main.cpp
        test_clang.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_clang
    FOLDER dep/libaeon/tests
)

set(AEON_CLANG_UNITTEST_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/)
configure_file(clang_unittest_data.h.in clang_unittest_data.h @ONLY)

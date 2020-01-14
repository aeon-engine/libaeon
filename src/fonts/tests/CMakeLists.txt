# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_fonts
    SOURCES
        main.cpp
        test_fonts.cpp
    INCLUDES ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_fonts aeon_unicode
    FOLDER dep/libaeon/tests
)

set(AEON_FONTS_UNITTEST_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/)
configure_file(fonts_unittest_data.h.in fonts_unittest_data.h @ONLY)

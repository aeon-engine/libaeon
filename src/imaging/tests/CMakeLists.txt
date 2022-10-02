# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_imaging
    SOURCES
        main.cpp
        test_atlas.cpp
        test_blit.cpp
        test_file.cpp
        test_file_bmp.cpp
        test_file_jpg.cpp
        test_file_png.cpp
        test_fill.cpp
        test_generators.cpp
        test_imaging.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_imaging aeon_testing
    FOLDER dep/libaeon/tests
)

set(AEON_IMAGING_UNITTEST_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/)
configure_file(imaging_unittest_data.h.in imaging_unittest_data.h @ONLY)

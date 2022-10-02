# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_ptree
    SOURCES
        main.cpp
        test_blob.cpp
        test_config_file.cpp
        test_ini.cpp
        test_ptree.cpp
        test_reflection.cpp
        test_xml.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_ptree
    FOLDER dep/libaeon/tests
)

set(AEON_PTREE_UNITTEST_DATA_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/)
configure_file(ptree_unittest_data.h.in ptree_unittest_data.h @ONLY)

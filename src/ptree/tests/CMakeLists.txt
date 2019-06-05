# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_ptree
    SOURCES
        main.cpp
        test_ptree.cpp
    LIBRARIES aeon_ptree
    FOLDER dep/libaeon/tests
)

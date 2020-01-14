# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_ast
    SOURCES
        main.cpp
        test_ast.cpp
    LIBRARIES aeon_ast
    FOLDER dep/libaeon/tests
)

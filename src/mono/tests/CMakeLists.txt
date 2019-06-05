# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

include(Unittests)
include(Mono)

add_mono_assembly(
    TARGET MonoTests
    DESTINATION ${CMAKE_BINARY_DIR}/bin
    TYPE library
    SOURCES test_libaeon_mono/test_mono.cs
)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_mono
    SOURCES
        main.cpp
        mono_jit_fixture.cpp
        mono_jit_fixture.h
        test_mono.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_mono aeon_common aeon_testing
    FOLDER dep/libaeon/tests
)

add_dependencies(test_libaeon_mono MonoTests)

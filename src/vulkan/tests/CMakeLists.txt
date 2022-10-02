# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_vulkan
    SOURCES
        main.cpp
        test_instance.cpp
    LIBRARIES aeon_vulkan
    LABELS vulkan
    FOLDER dep/libaeon/tests
)

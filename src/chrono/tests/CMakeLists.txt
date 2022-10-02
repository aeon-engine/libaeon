# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_chrono
    SOURCES
        main.cpp
        test_calendar.cpp
        test_timezone.cpp
    LIBRARIES aeon_chrono
    FOLDER dep/libaeon/tests
)

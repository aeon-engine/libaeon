# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

include(Unittests)

add_unit_test_suite(
    NO_GTEST_MAIN
    TARGET test_libaeon_math
    SOURCES
        main.cpp
        test_circle.cpp
        test_mat3.cpp
        test_mat3_sse.cpp
        test_mat4.cpp
        test_mat4_sse.cpp
        test_math.cpp
        test_quaternion.cpp
        test_range.cpp
        test_rectangle.cpp
        test_size2d.cpp
        test_size3d.cpp
        test_units.cpp
        test_vector2.cpp
        test_vector3.cpp
        test_vector4.cpp
    INCLUDES
        ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARIES aeon_math
    FOLDER dep/libaeon/tests
)

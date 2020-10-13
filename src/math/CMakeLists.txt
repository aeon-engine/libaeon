# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

set(LIB_AEON_MATH_PUBLIC_SOURCE
    include/aeon/math/anchor_point.h
    include/aeon/math/circle.h
    include/aeon/math/circle_stream.h
    include/aeon/math/convert_type.h
    include/aeon/math/mat3.h
    include/aeon/math/mat3_stream.h
    include/aeon/math/mat4.h
    include/aeon/math/mat4_stream.h
    include/aeon/math/math.h
    include/aeon/math/math_fwd.h
    include/aeon/math/perlin_noise.h
    include/aeon/math/plane.h
    include/aeon/math/plane_stream.h
    include/aeon/math/quaternion.h
    include/aeon/math/quaternion_stream.h
    include/aeon/math/range.h
    include/aeon/math/range_stream.h
    include/aeon/math/ray3d.h
    include/aeon/math/ray3d_stream.h
    include/aeon/math/rectangle.h
    include/aeon/math/rectangle_stream.h
    include/aeon/math/simplex_noise.h
    include/aeon/math/size2d.h
    include/aeon/math/size2d_stream.h
    include/aeon/math/size3d.h
    include/aeon/math/size3d_stream.h
    include/aeon/math/units.h
    include/aeon/math/units_literals.h
    include/aeon/math/vector2.h
    include/aeon/math/vector2_stream.h
    include/aeon/math/vector3.h
    include/aeon/math/vector3_stream.h
    include/aeon/math/vector4.h
    include/aeon/math/vector4_stream.h
)

source_group(public FILES ${LIB_AEON_MATH_PUBLIC_SOURCE})

set(LIB_AEON_MATH_PUBLIC_IMPL_SOURCE
    include/aeon/math/impl/circle_impl.h
    include/aeon/math/impl/mat3_impl.h
    include/aeon/math/impl/mat3_operators_impl.h
    include/aeon/math/impl/mat4_impl.h
    include/aeon/math/impl/mat4_operators_impl.h
    include/aeon/math/impl/plane_impl.h
    include/aeon/math/impl/plane_operators_impl.h
    include/aeon/math/impl/quaternion_impl.h
    include/aeon/math/impl/quaternion_operators_impl.h
    include/aeon/math/impl/range_impl.h
    include/aeon/math/impl/ray3d_impl.h
    include/aeon/math/impl/ray3d_operators_impl.h
    include/aeon/math/impl/rectangle_impl.h
    include/aeon/math/impl/size2d_impl.h
    include/aeon/math/impl/size3d_impl.h
    include/aeon/math/impl/units_impl.h
    include/aeon/math/impl/units_magnitudes_impl.h
    include/aeon/math/impl/units_prefixes.h
    include/aeon/math/impl/units_tags_impl.h
    include/aeon/math/impl/units_traits_impl.h
    include/aeon/math/impl/vector2_impl.h
    include/aeon/math/impl/vector2_operators_impl.h
    include/aeon/math/impl/vector3_impl.h
    include/aeon/math/impl/vector3_operators_impl.h
    include/aeon/math/impl/vector4_impl.h
    include/aeon/math/impl/vector4_operators_impl.h
)

source_group(public\\impl FILES ${LIB_AEON_MATH_PUBLIC_IMPL_SOURCE})

set(LIB_AEON_MATH_PRIVATE_SOURCE
    src/perlin_noise.cpp
    src/simplex_noise.cpp
)

source_group(private FILES ${LIB_AEON_MATH_PRIVATE_SOURCE})

add_library(aeon_math STATIC
    ${LIB_AEON_MATH_PUBLIC_SOURCE}
    ${LIB_AEON_MATH_PUBLIC_IMPL_SOURCE}
    ${LIB_AEON_MATH_PRIVATE_SOURCE}
)

set_target_properties(aeon_math PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_math
    PUBLIC
        include
)

target_link_libraries(aeon_math
    aeon_common
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_math
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

if (AEON_ENABLE_BENCHMARK)
    add_subdirectory(benchmarks)
endif ()

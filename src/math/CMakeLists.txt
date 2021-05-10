# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/perlin_noise.cpp
    private/simplex_noise.cpp
    public/aeon/math/anchor_point.h
    public/aeon/math/circle.h
    public/aeon/math/circle_stream.h
    public/aeon/math/clipping_space.h
    public/aeon/math/hash.h
    public/aeon/math/imat.h
    public/aeon/math/impl/circle_impl.h
    public/aeon/math/impl/imat_impl.h
    public/aeon/math/impl/mat3_impl.h
    public/aeon/math/impl/mat3_operators_impl.h
    public/aeon/math/impl/mat4_impl.h
    public/aeon/math/impl/mat4_operators_impl.h
    public/aeon/math/impl/mat_impl.h
    public/aeon/math/impl/mat_view_impl.h
    public/aeon/math/impl/plane_impl.h
    public/aeon/math/impl/plane_operators_impl.h
    public/aeon/math/impl/quaternion_impl.h
    public/aeon/math/impl/quaternion_operators_impl.h
    public/aeon/math/impl/range_impl.h
    public/aeon/math/impl/ray3d_impl.h
    public/aeon/math/impl/ray3d_operators_impl.h
    public/aeon/math/impl/rectangle_impl.h
    public/aeon/math/impl/size2d_impl.h
    public/aeon/math/impl/size3d_impl.h
    public/aeon/math/impl/units_impl.h
    public/aeon/math/impl/units_magnitudes_impl.h
    public/aeon/math/impl/units_prefixes.h
    public/aeon/math/impl/units_tags_impl.h
    public/aeon/math/impl/units_traits_impl.h
    public/aeon/math/impl/vector2_impl.h
    public/aeon/math/impl/vector2_operators_impl.h
    public/aeon/math/impl/vector3_impl.h
    public/aeon/math/impl/vector3_operators_impl.h
    public/aeon/math/impl/vector4_impl.h
    public/aeon/math/impl/vector4_operators_impl.h
    public/aeon/math/line_segment.h
    public/aeon/math/mat.h
    public/aeon/math/mat3.h
    public/aeon/math/mat3_stream.h
    public/aeon/math/mat4.h
    public/aeon/math/mat4_stream.h
    public/aeon/math/mat_view.h
    public/aeon/math/math.h
    public/aeon/math/math_fwd.h
    public/aeon/math/perlin_noise.h
    public/aeon/math/plane.h
    public/aeon/math/plane_stream.h
    public/aeon/math/quaternion.h
    public/aeon/math/quaternion_stream.h
    public/aeon/math/range.h
    public/aeon/math/range_stream.h
    public/aeon/math/ray3d.h
    public/aeon/math/ray3d_stream.h
    public/aeon/math/rectangle.h
    public/aeon/math/rectangle_stream.h
    public/aeon/math/simplex_noise.h
    public/aeon/math/size2d.h
    public/aeon/math/size2d_stream.h
    public/aeon/math/size3d.h
    public/aeon/math/size3d_stream.h
    public/aeon/math/swizzle_component.h
    public/aeon/math/swizzle_vector.h
    public/aeon/math/units.h
    public/aeon/math/units_literals.h
    public/aeon/math/vector2.h
    public/aeon/math/vector2_stream.h
    public/aeon/math/vector3.h
    public/aeon/math/vector3_stream.h
    public/aeon/math/vector4.h
    public/aeon/math/vector4_stream.h
    public/aeon/math/vector_graphics_2d.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_math STATIC
    ${SOURCES}
)

set_target_properties(aeon_math PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_math
    PUBLIC
        public
)

target_link_libraries(aeon_math
    aeon_common
)

install(
    DIRECTORY public/aeon
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

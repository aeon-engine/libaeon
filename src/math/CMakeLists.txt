# Copyright (c) 2012-2018 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

set(LIB_AEON_MATH_SOURCE
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
    src/perlin_noise.cpp
    include/aeon/math/quaternion.h
    include/aeon/math/quaternion_stream.h
    include/aeon/math/range.h
    include/aeon/math/range_stream.h
    include/aeon/math/rectangle.h
    include/aeon/math/rectangle_stream.h
    include/aeon/math/simplex_noise.h
    src/simplex_noise.cpp
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

source_group(math FILES ${LIB_AEON_MATH_SOURCE})

set(LIB_AEON_MATH_IMPL_SOURCE
    include/aeon/math/impl/circle_impl.h
    include/aeon/math/impl/mat3_impl.h
    include/aeon/math/impl/mat3_operators_impl.h
    include/aeon/math/impl/mat4_impl.h
    include/aeon/math/impl/mat4_operators_impl.h
    include/aeon/math/impl/quaternion_impl.h
    include/aeon/math/impl/quaternion_operators_impl.h
    include/aeon/math/impl/range_impl.h
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

source_group(math\\impl FILES ${LIB_AEON_MATH_IMPL_SOURCE})

add_library(aeon_math STATIC ${LIB_AEON_MATH_SOURCE} ${LIB_AEON_MATH_IMPL_SOURCE})

set_target_properties(aeon_math PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_math PUBLIC include)

target_link_libraries(aeon_math aeon_common)

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

add_subdirectory(tests)
add_subdirectory(benchmarks)

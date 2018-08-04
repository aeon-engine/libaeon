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

set(LIB_AEON_TYPES_SOURCE
    include/aeon/types/anchor_point.h
    include/aeon/types/circle.h
    include/aeon/types/range.h
    include/aeon/types/rectangle.h
    include/aeon/types/size2d.h
    include/aeon/types/uuid.h
    include/aeon/types/uuid_stream.h
    src/uuid.cpp
)

source_group(types FILES ${LIB_AEON_TYPES_SOURCE})

set(LIB_AEON_TYPES_IMPL_SOURCE
    include/aeon/types/impl/circle_impl.h
    include/aeon/types/impl/range_impl.h
    include/aeon/types/impl/rectangle_impl.h
    include/aeon/types/impl/size2d_impl.h
)

source_group(types\\impl FILES ${LIB_AEON_TYPES_IMPL_SOURCE})

add_library(aeon_types STATIC ${LIB_AEON_TYPES_SOURCE} ${LIB_AEON_TYPES_IMPL_SOURCE})

set_target_properties(aeon_types PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_types PUBLIC include)

target_link_libraries(aeon_types aeon_common aeon_streams aeon_math)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)

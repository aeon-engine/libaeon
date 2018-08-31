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

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/freetype2 dep/freetype2)

set(LIB_AEON_FONTS_SOURCE
    include/aeon/fonts/config.h
    include/aeon/fonts/exceptions.h
    include/aeon/fonts/face.h
    src/face.cpp
    include/aeon/fonts/face_wrapper.h
    src/face_wrapper.cpp
    include/aeon/fonts/font_manager.h
    src/font_manager.cpp
    include/aeon/fonts/glyph.h
)

source_group(fonts FILES ${LIB_AEON_FONTS_SOURCE})

add_library(aeon_fonts STATIC
    ${LIB_AEON_FONTS_SOURCE}
)

set_target_properties(aeon_fonts PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_fonts PUBLIC include)
target_link_libraries(aeon_fonts
    aeon_imaging
    aeon_streams
    freetype
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_fonts
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)

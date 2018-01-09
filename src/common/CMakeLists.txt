# Copyright (c) 2012-2017 Robin Degen
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

set(LIB_AEON_COMMON_SOURCE
    include/aeon/common/bitflags.h
    include/aeon/common/compilers.h
    include/aeon/common/container.h
    include/aeon/common/endianness.h
    include/aeon/common/literals.h
    include/aeon/common/noncopyable.h
    include/aeon/common/optional.h
    include/aeon/common/platform.h
    include/aeon/common/singleton.h
    include/aeon/common/string.h
    src/string.cpp
    include/aeon/common/string_traits.h
    include/aeon/common/term_colors.h
    include/aeon/common/variant.h
    include/aeon/common/unused.h
    include/aeon/common/type_traits.h
    include/aeon/common/stdfilesystem.h
    include/aeon/common/stdoptional.h
    include/aeon/common/deprecated.h
    include/aeon/common/dllexport.h
)

source_group(common FILES ${LIB_AEON_COMMON_SOURCE})

add_library(aeon_common STATIC ${LIB_AEON_COMMON_SOURCE})

set_target_properties(aeon_common PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_common PUBLIC include)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)

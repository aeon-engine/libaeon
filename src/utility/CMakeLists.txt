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

set(LIB_AEON_UTILITY_SOURCE
    include/aeon/utility/cached_container.h
    include/aeon/utility/configfile.h
    src/configfile.cpp
    include/aeon/utility/dispatcher.h
    include/aeon/utility/dispatcher_fwd.h
    include/aeon/utility/hexdump.h
    src/hexdump.cpp
    include/aeon/utility/linear_map.h
    include/aeon/utility/listener_subject.h
    include/aeon/utility/parallelizer.h
    include/aeon/utility/parameters.h
    include/aeon/utility/signals.h
    include/aeon/utility/tribool.h
    include/aeon/utility/uuid.h
    src/uuid.cpp
    include/aeon/utility/uuid_stream.h
)

source_group(utility FILES ${LIB_AEON_UTILITY_SOURCE})

add_library(aeon_utility STATIC ${LIB_AEON_UTILITY_SOURCE})

set_target_properties(aeon_utility PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_utility PUBLIC include)

target_link_libraries(aeon_utility aeon_common aeon_streams)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_utility
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)

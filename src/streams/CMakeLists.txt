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

set(LIB_AEON_STREAMS_SOURCE
    include/aeon/streams/access_mode_mixin.h
    include/aeon/streams/circular_buffer_stream.h
    include/aeon/streams/config.h
    include/aeon/streams/file_stream.h
    src/file_stream.cpp
    include/aeon/streams/file_stream_fwd.h
    include/aeon/streams/io_stream.h
    src/io_stream.cpp
    include/aeon/streams/io_stream_fwd.h
    include/aeon/streams/io_stream_colors_mixin.h
    src/io_stream_colors_mixin.cpp
    include/aeon/streams/memory_stream.h
    src/memory_stream.cpp
    include/aeon/streams/memory_stream_fwd.h
    include/aeon/streams/stream.h
    include/aeon/streams/stream_fwd.h
    include/aeon/streams/stream_name_mixin.h
    include/aeon/streams/stream_reader.h
    include/aeon/streams/stream_writer.h
    include/aeon/streams/stream_string_operators.h
    include/aeon/streams/stream_vector_operators.h
)

source_group(streams FILES ${LIB_AEON_STREAMS_SOURCE})

add_library(aeon_streams STATIC ${LIB_AEON_STREAMS_SOURCE})

set_target_properties(aeon_streams PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_streams PUBLIC include)
target_link_libraries(aeon_streams aeon_common)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)

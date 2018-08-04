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

set(LIB_AEON_LOGGER_SOURCE
    include/aeon/logger/base_backend.h
    src/base_backend.cpp
    include/aeon/logger/io_stream_sink.h
    src/io_stream_sink.cpp
    include/aeon/logger/logger.h
    include/aeon/logger/log_level.h
    include/aeon/logger/log_sink.h
    include/aeon/logger/multithreaded_sink_backend.h
    src/multithreaded_sink_backend.cpp
    include/aeon/logger/simple_backend.h
    src/simple_backend.cpp
    include/aeon/logger/simple_sink_backend.h
    src/simple_sink_backend.cpp
    include/aeon/logger/stream_sink.h
    src/stream_sink.cpp
)

source_group(logger FILES ${LIB_AEON_LOGGER_SOURCE})

add_library(aeon_logger STATIC ${LIB_AEON_LOGGER_SOURCE})

set_target_properties(aeon_logger PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_logger PUBLIC include)
target_link_libraries(aeon_logger aeon_common aeon_streams)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

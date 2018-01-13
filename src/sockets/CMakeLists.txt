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

message(STATUS "Building libAeon with Socket support.")

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/asio dep/asio)

set(LIB_AEON_SOCKETS_SOURCE
    include/aeon/sockets/config.h
    include/aeon/sockets/line_protocol_handler.h
    include/aeon/sockets/tcp_server.h
    include/aeon/sockets/webserver/http_protocol_handler.h
    src/http_protocol_handler.cpp
    include/aeon/sockets/webserver/http_request.h
    src/http_request.cpp
)

source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

add_library(aeon_sockets STATIC ${LIB_AEON_SOCKETS_SOURCE})

set_target_properties(aeon_sockets PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_sockets PUBLIC include)
target_link_libraries(aeon_sockets aeon_common aeon_streams asio)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)

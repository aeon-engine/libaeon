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

message(STATUS "Building libAeon with Socket, HTTP and REST support.")

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/asio dep/asio)
add_subdirectory(${CMAKE_SOURCE_DIR}/dep/json11 dep/json11)

set(LIB_AEON_SOCKETS_SOURCE
    include/aeon/sockets/config.h
    include/aeon/sockets/tcp_socket.h
    include/aeon/sockets/line_protocol.h
    include/aeon/sockets/tcp_server.h
    include/aeon/sockets/tcp_client.h
    src/tcp_socket.cpp
    src/line_protocol.cpp
)

source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

set(LIB_AEON_SOCKETS_HTTP_SOURCE
    include/aeon/sockets/http/http_server_protocol.h
    include/aeon/sockets/http/http_client_protocol.h
    include/aeon/sockets/http/request.h
    include/aeon/sockets/http/status_code.h
    include/aeon/sockets/http/method.h
    include/aeon/sockets/http/validators.h
    include/aeon/sockets/http/constants.h
    include/aeon/sockets/http/reply.h
    src/http/request.cpp
    src/http/http_server_protocol.cpp
    src/http/http_client_protocol.cpp
    src/http/status_code.cpp
    src/http/method.cpp
    src/http/validators.cpp
    src/http/reply.cpp
)

source_group(sockets\\http FILES ${LIB_AEON_SOCKETS_HTTP_SOURCE})

set(LIB_AEON_SOCKETS_HTTP_REST_SOURCE
    include/aeon/sockets/http/rest/rest_server.h
    include/aeon/sockets/http/rest/rest_method.h
    src/http/rest/rest_server.cpp
    src/http/rest/rest_method.cpp
)

source_group(sockets\\http\\rest FILES ${LIB_AEON_SOCKETS_HTTP_REST_SOURCE})

add_library(aeon_sockets STATIC
    ${LIB_AEON_SOCKETS_SOURCE}
    ${LIB_AEON_SOCKETS_HTTP_SOURCE}
    ${LIB_AEON_SOCKETS_HTTP_REST_SOURCE}
)

set_target_properties(aeon_sockets PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_sockets PUBLIC include)

target_link_libraries(aeon_sockets
    aeon_common
    aeon_streams
    asio
    json11
)

install(
    DIRECTORY include
    DESTINATION include
)

add_subdirectory(tests)

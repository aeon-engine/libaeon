# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

set(SOURCES
    private/http/http_client_socket.cpp
    private/http/http_jsonrpc_route.cpp
    private/http/http_server_session.cpp
    private/http/http_server_socket.cpp
    private/http/method.cpp
    private/http/reply.cpp
    private/http/request.cpp
    private/http/routable_http_server_session.cpp
    private/http/routable_http_server_socket.cpp
    private/http/static_route.cpp
    private/http/status_code.cpp
    private/http/url_encoding.cpp
    private/http/validators.cpp
    private/jsonrpc/method.cpp
    private/jsonrpc/result.cpp
    private/jsonrpc/server.cpp
    public/aeon/web/http/constants.h
    public/aeon/web/http/http_client_socket.h
    public/aeon/web/http/http_jsonrpc_route.h
    public/aeon/web/http/http_server.h
    public/aeon/web/http/http_server_session.h
    public/aeon/web/http/http_server_socket.h
    public/aeon/web/http/method.h
    public/aeon/web/http/reply.h
    public/aeon/web/http/request.h
    public/aeon/web/http/routable_http_server.h
    public/aeon/web/http/routable_http_server_session.h
    public/aeon/web/http/routable_http_server_socket.h
    public/aeon/web/http/route.h
    public/aeon/web/http/static_route.h
    public/aeon/web/http/status_code.h
    public/aeon/web/http/url_encoding.h
    public/aeon/web/http/validators.h
    public/aeon/web/jsonrpc/method.h
    public/aeon/web/jsonrpc/result.h
    public/aeon/web/jsonrpc/server.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_web STATIC
    ${SOURCES}
)

set_target_properties(aeon_web PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_web
    PUBLIC
        public
)

target_link_libraries(aeon_web
    aeon_common
    aeon_streams
    aeon_sockets
    aeon_ptree
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_web
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

add_subdirectory(testapps)

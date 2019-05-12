# Copyright (c) 2012-2019 Robin Degen

message(STATUS "Building libAeon with Socket, HTTP and Json-RPC support.")

set(LIB_AEON_SOCKETS_PUBLIC_SOURCE
    include/aeon/sockets/config.h
    include/aeon/sockets/tcp_socket.h
    include/aeon/sockets/line_protocol_socket.h
    include/aeon/sockets/tcp_server.h
    include/aeon/sockets/tcp_client.h
)

source_group(public FILES ${LIB_AEON_SOCKETS_PUBLIC_SOURCE})

set(LIB_AEON_SOCKETS_PRIVATE_SOURCE
    src/tcp_socket.cpp
    src/line_protocol_socket.cpp
)

source_group(private FILES ${LIB_AEON_SOCKETS_PRIVATE_SOURCE})

set(LIB_AEON_SOCKETS_PUBLIC_HTTP_SOURCE
    include/aeon/sockets/http/http_server_socket.h
    include/aeon/sockets/http/http_client_socket.h
    include/aeon/sockets/http/http_server_session.h
    include/aeon/sockets/http/http_server.h
    include/aeon/sockets/http/http_jsonrpc_route.h
    include/aeon/sockets/http/routable_http_server_socket.h
    include/aeon/sockets/http/routable_http_server_session.h
    include/aeon/sockets/http/routable_http_server.h
    include/aeon/sockets/http/request.h
    include/aeon/sockets/http/status_code.h
    include/aeon/sockets/http/method.h
    include/aeon/sockets/http/validators.h
    include/aeon/sockets/http/constants.h
    include/aeon/sockets/http/reply.h
    include/aeon/sockets/http/route.h
    include/aeon/sockets/http/static_route.h
    include/aeon/sockets/http/url_encoding.h
)

source_group(public\\http FILES ${LIB_AEON_SOCKETS_PUBLIC_HTTP_SOURCE})

set(LIB_AEON_SOCKETS_PRIVATE_HTTP_SOURCE
    src/http/request.cpp
    src/http/http_server_socket.cpp
    src/http/http_client_socket.cpp
    src/http/http_server_session.cpp
    src/http/http_jsonrpc_route.cpp
    src/http/routable_http_server_socket.cpp
    src/http/routable_http_server_session.cpp
    src/http/status_code.cpp
    src/http/method.cpp
    src/http/validators.cpp
    src/http/reply.cpp
    src/http/static_route.cpp
    src/http/url_encoding.cpp
)

source_group(private\\http FILES ${LIB_AEON_SOCKETS_PRIVATE_HTTP_SOURCE})

set(LIB_AEON_SOCKETS_PUBLIC_JSONRPC_SOURCE
    include/aeon/sockets/jsonrpc/server.h
    include/aeon/sockets/jsonrpc/method.h
    include/aeon/sockets/jsonrpc/result.h
)

source_group(public\\jsonrpc FILES ${LIB_AEON_SOCKETS_PUBLIC_JSONRPC_SOURCE})

set(LIB_AEON_SOCKETS_PRIVATE_JSONRPC_SOURCE
    src/jsonrpc/server.cpp
    src/jsonrpc/method.cpp
    src/jsonrpc/result.cpp
)

source_group(private\\jsonrpc FILES ${LIB_AEON_SOCKETS_PRIVATE_JSONRPC_SOURCE})

add_library(aeon_sockets STATIC
    ${LIB_AEON_SOCKETS_PUBLIC_SOURCE}
    ${LIB_AEON_SOCKETS_PRIVATE_SOURCE}
    ${LIB_AEON_SOCKETS_PUBLIC_HTTP_SOURCE}
    ${LIB_AEON_SOCKETS_PRIVATE_HTTP_SOURCE}
    ${LIB_AEON_SOCKETS_PUBLIC_JSONRPC_SOURCE}
    ${LIB_AEON_SOCKETS_PRIVATE_JSONRPC_SOURCE}
)

set_target_properties(aeon_sockets PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_sockets
    PUBLIC
        include
)

target_link_libraries(aeon_sockets
    aeon_common
    aeon_streams
    Asio::Asio
    Json11::Json11
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_sockets
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

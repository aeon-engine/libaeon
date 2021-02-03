# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_WEB_PUBLIC_HTTP_SOURCE
    include/aeon/web/http/http_server_socket.h
    include/aeon/web/http/http_client_socket.h
    include/aeon/web/http/http_server_session.h
    include/aeon/web/http/http_server.h
    include/aeon/web/http/http_jsonrpc_route.h
    include/aeon/web/http/routable_http_server_socket.h
    include/aeon/web/http/routable_http_server_session.h
    include/aeon/web/http/routable_http_server.h
    include/aeon/web/http/request.h
    include/aeon/web/http/status_code.h
    include/aeon/web/http/method.h
    include/aeon/web/http/validators.h
    include/aeon/web/http/constants.h
    include/aeon/web/http/reply.h
    include/aeon/web/http/route.h
    include/aeon/web/http/static_route.h
    include/aeon/web/http/url_encoding.h
)

source_group(public\\http FILES ${LIB_AEON_WEB_PUBLIC_HTTP_SOURCE})

set(LIB_AEON_WEB_PRIVATE_HTTP_SOURCE
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

source_group(private\\http FILES ${LIB_AEON_WEB_PRIVATE_HTTP_SOURCE})

set(LIB_AEON_WEB_PUBLIC_JSONRPC_SOURCE
    include/aeon/web/jsonrpc/server.h
    include/aeon/web/jsonrpc/method.h
    include/aeon/web/jsonrpc/result.h
)

source_group(public\\jsonrpc FILES ${LIB_AEON_WEB_PUBLIC_JSONRPC_SOURCE})

set(LIB_AEON_WEB_PRIVATE_JSONRPC_SOURCE
    src/jsonrpc/server.cpp
    src/jsonrpc/method.cpp
    src/jsonrpc/result.cpp
)

source_group(private\\jsonrpc FILES ${LIB_AEON_WEB_PRIVATE_JSONRPC_SOURCE})

add_library(aeon_web STATIC
    ${LIB_AEON_WEB_PUBLIC_HTTP_SOURCE}
    ${LIB_AEON_WEB_PRIVATE_HTTP_SOURCE}
    ${LIB_AEON_WEB_PUBLIC_JSONRPC_SOURCE}
    ${LIB_AEON_WEB_PRIVATE_JSONRPC_SOURCE}
)

set_target_properties(aeon_web PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_web
    PUBLIC
        include
)

target_link_libraries(aeon_web
    aeon_common
    aeon_streams
    aeon_sockets
    aeon_ptree
)

install(
    DIRECTORY include/aeon
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

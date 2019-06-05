# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

handle_local_dependencies_file()

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

add_library(aeon_sockets STATIC
    ${LIB_AEON_SOCKETS_PUBLIC_SOURCE}
    ${LIB_AEON_SOCKETS_PRIVATE_SOURCE}
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

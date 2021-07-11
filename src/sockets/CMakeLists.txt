# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/line_protocol_socket.cpp
    private/tcp_socket.cpp
    public/aeon/sockets/config.h
    public/aeon/sockets/length_prefixed_binary_protocol_socket.h
    public/aeon/sockets/line_protocol_socket.h
    public/aeon/sockets/tcp_client.h
    public/aeon/sockets/tcp_server.h
    public/aeon/sockets/tcp_socket.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_sockets STATIC
    ${SOURCES}
)

set_target_properties(aeon_sockets PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_sockets
    PUBLIC
        public
)

target_link_libraries(aeon_sockets
    aeon_common
    aeon_streams
    CONAN_PKG::asio
)

target_compile_definitions(aeon_sockets
    PUBLIC
        ASIO_NO_DEPRECATED
        ASIO_STANDALONE
        ASIO_HEADER_ONLY
        # ASIO uses deprecated windows api calls which raise a warning when targetting Windows 10
        _WINSOCK_DEPRECATED_NO_WARNINGS
)

install(
    DIRECTORY public/aeon
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

add_subdirectory(testapps)

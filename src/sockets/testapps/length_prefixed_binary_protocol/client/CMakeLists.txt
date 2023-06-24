# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

set(LIB_AEON_LENGTH_PREFIXED_BINARY_PROTOCOL_SOURCE
    private/main.cpp
)

source_group(private FILES ${LIB_AEON_LENGTH_PREFIXED_BINARY_PROTOCOL_SOURCE})

add_executable(aeon_sockets_length_prefixed_binary_protocol_client
    ${LIB_AEON_LENGTH_PREFIXED_BINARY_PROTOCOL_SOURCE}
)

set_target_properties(aeon_sockets_length_prefixed_binary_protocol_client PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_sockets_length_prefixed_binary_protocol_client
    PRIVATE
        private
)

target_link_libraries(aeon_sockets_length_prefixed_binary_protocol_client
    aeon_sockets
)

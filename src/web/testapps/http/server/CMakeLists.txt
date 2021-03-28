# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(LIB_AEON_HTTP_SERVER_SOURCE
    private/main.cpp
)

source_group(private FILES ${LIB_AEON_HTTP_SERVER_SOURCE})

add_executable(aeon_web_http_server
    ${LIB_AEON_HTTP_SERVER_SOURCE}
)

set_target_properties(aeon_web_http_server PROPERTIES
    FOLDER dep/libaeon
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_include_directories(aeon_web_http_server
    PRIVATE
        private
        ${CMAKE_CURRENT_BINARY_DIR}/private
)

target_link_libraries(aeon_web_http_server
    aeon_web
)

set(AEON_HTTP_SERVER_WWWROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/wwwroot)
configure_file(http_server_settings.h.in private/http_server_settings.h @ONLY)

# ROBIN DEGEN; CONFIDENTIAL
#
# 2012 - 2017 Robin Degen
# All Rights Reserved.
#
# NOTICE:  All information contained herein is, and remains the property of
# Robin Degen and its suppliers, if any. The intellectual and technical
# concepts contained herein are proprietary to Robin Degen and its suppliers
# and may be covered by U.S. and Foreign Patents, patents in process, and are
# protected by trade secret or copyright law. Dissemination of this
# information or reproduction of this material is strictly forbidden unless
# prior written permission is obtained from Robin Degen.

# Mono
option(AEON_ENABLE_MONO "Enable the Aeon Mono library." OFF)
option(AEON_COPY_MONO_RUNTIMES "Enable if Mono should be embedded and ran purely from the binary folder." OFF)

# Sockets
option(AEON_ENABLE_SOCKETS "Enable the Aeon Socket library." OFF)

################################################################################

set(LIB_AEON_STREAMS_SOURCE
    src/aeon/streams.h
    src/aeon/streams/config.h
    src/aeon/streams/access_mode_mixin.h
    src/aeon/streams/stream_reader.h
    src/aeon/streams/stream_writer.h
    src/aeon/streams/stream.h
    src/aeon/streams/file_stream.h
    src/aeon/streams/file_stream.cpp
    src/aeon/streams/io_stream.h
    src/aeon/streams/io_stream.cpp
    src/aeon/streams/circular_buffer_stream.h
    src/aeon/streams/memory_stream.h
    src/aeon/streams/stream_name_mixin.h
    src/aeon/streams/io_stream_colors_mixin.h
    src/aeon/streams/io_stream_colors_mixin.cpp
)

source_group(streams FILES ${LIB_AEON_STREAMS_SOURCE})

################################################################################

set(LIB_AEON_MATH_SOURCE
    src/aeon/math.h
    src/aeon/math/perlin_noise.h
    src/aeon/math/perlin_noise.cpp
    src/aeon/math/simplex_noise.h
    src/aeon/math/simplex_noise.cpp
)

source_group(math FILES ${LIB_AEON_MATH_SOURCE})

################################################################################

if (AEON_ENABLE_SOCKETS)
    set(LIB_AEON_SOCKETS_SOURCE
        src/aeon/sockets.h
        src/aeon/sockets/config.h
        src/aeon/sockets/line_protocol_handler.h
        src/aeon/sockets/tcp_server.h
    )

    source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

    set(LIB_AEON_WEBSERVER_SOURCE
        src/aeon/webserver.h
        src/aeon/webserver/http_protocol_handler.h
        src/aeon/webserver/http_protocol_handler.cpp
        src/aeon/webserver/http_request.h
        src/aeon/webserver/http_request.cpp
    )

    source_group(webserver FILES ${LIB_AEON_WEBSERVER_SOURCE})
endif ()

################################################################################

set(LIB_AEON_UTILITY_SOURCE
    src/aeon/utility.h
    src/aeon/utility/bitflags.h
    src/aeon/utility/singleton.h
    src/aeon/utility/configfile.h
    src/aeon/utility/configfile.cpp
    src/aeon/utility/container.h
    src/aeon/utility/hexdump.h
    src/aeon/utility/hexdump.cpp
    src/aeon/utility/endianness.h
    src/aeon/utility/timer.cpp
    src/aeon/utility/timer.h
    src/aeon/utility/optional.h
    src/aeon/utility/linear_map.h
    src/aeon/utility/variant.h
    src/aeon/utility/noncopyable.h
    src/aeon/utility/string_traits.h
    src/aeon/utility/string.cpp
    src/aeon/utility/string.h
    src/aeon/utility/listener_subject.h
    src/aeon/utility/dispatcher.h
    src/aeon/utility/signals.h
    src/aeon/utility/parallelizer.h
    src/aeon/utility/literals.h
)

source_group(utility FILES ${LIB_AEON_UTILITY_SOURCE})

################################################################################

set(LIB_AEON_PLATFORM_SOURCE
    src/aeon/platform.h
    src/aeon/platform/platform.h
    src/aeon/platform/term_colors.h
    src/aeon/platform/compilers.h
)

source_group(platform FILES ${LIB_AEON_PLATFORM_SOURCE})

################################################################################

set(LIB_AEON_TESTING_SOURCE
    src/aeon/testing.h
    src/aeon/testing/temporary_file_fixture.h
    src/aeon/testing/temporary_file_fixture.cpp
)

source_group(testing FILES ${LIB_AEON_TESTING_SOURCE})

################################################################################

set(LIB_AEON_FILESYSTEM_SOURCE
    src/aeon/filesystem.h
    src/aeon/filesystem/filesystem.h
    src/aeon/filesystem/filesystem.cpp
)

source_group(filesystem FILES ${LIB_AEON_FILESYSTEM_SOURCE})

################################################################################

set(LIB_AEON_LOGGER_SOURCE
    src/aeon/logger.h
    src/aeon/logger/logger.h
    src/aeon/logger/log_sink.h
    src/aeon/logger/log_level.h
    src/aeon/logger/base_backend.h
    src/aeon/logger/simple_backend.h
    src/aeon/logger/simple_sink_backend.h
    src/aeon/logger/multithreaded_sink_backend.h
    src/aeon/logger/stream_sink.h
    src/aeon/logger/io_stream_sink.h
)

source_group(logger FILES ${LIB_AEON_LOGGER_SOURCE})

################################################################################

if (AEON_ENABLE_CURL)
    set(LIB_AEON_CURL_SOURCE
        src/aeon/curl.h
        src/aeon/curl/url_downloader.h
        src/aeon/curl/url_downloader.cpp
        src/aeon/curl/exceptions.h
        src/aeon/curl/global_wrapper.cpp
        src/aeon/curl/global_wrapper.h
        src/aeon/curl/easy_wrapper.cpp
        src/aeon/curl/easy_wrapper.h
    )

    source_group(curl FILES ${LIB_AEON_CURL_SOURCE})
endif ()

################################################################################

if (AEON_ENABLE_MONO)
    include(Mono)

    if (AEON_COPY_MONO_RUNTIMES)
        copy_mono_runtimes_to_runtime_path()
        set(_MONO_ASSEMBLY_DIR ".")
        set(_MONO_CONFIG_DIR ".")
    else ()
        set(_MONO_ASSEMBLY_DIR ${MONO_ASSEMBLY_PATH})
        set(_MONO_CONFIG_DIR ${MONO_CONFIG_PATH})
    endif ()

    set(AEON_MONO_ASSEMBLY_DIR "${_MONO_ASSEMBLY_DIR}"
        CACHE PATH "Path to the Mono assembly dir (mono/lib). May be a relative path.")
    set(AEON_MONO_CONFIG_DIR "${_MONO_CONFIG_DIR}"
        CACHE PATH "Path to the Mono config dir (mono/etc). May be a relative path.")

    configure_file(src/aeon/mono/mono_build_config.h.in mono_build_config.h @ONLY)

    set(LIB_AEON_MONO_SOURCE
        src/aeon/mono.h
        src/aeon/mono/mono_method.cpp
        src/aeon/mono/mono_method.h
        src/aeon/mono/mono_assembly.cpp
        src/aeon/mono/mono_assembly.h
        src/aeon/mono/mono_jit.cpp
        src/aeon/mono/mono_jit.h
        src/aeon/mono/mono_class.cpp
        src/aeon/mono/mono_class.h
        src/aeon/mono/mono_object.cpp
        src/aeon/mono/mono_object.h
        src/aeon/mono/mono_string.cpp
        src/aeon/mono/mono_string.h
        src/aeon/mono/mono_gchandle.cpp
        src/aeon/mono/mono_gchandle.h
        src/aeon/mono/mono_class_instance.cpp
        src/aeon/mono/mono_class_instance.h
        src/aeon/mono/mono_exception.h
        ${CMAKE_CURRENT_BINARY_DIR}/mono_build_config.h
    )

    source_group(mono FILES ${LIB_AEON_MONO_SOURCE})
endif ()

################################################################################

set(LIB_AEON_SOURCE
    ${LIB_AEON_STREAMS_SOURCE}
    ${LIB_AEON_MATH_SOURCE}
    ${LIB_AEON_UTILITY_SOURCE}
    ${LIB_AEON_PLATFORM_SOURCE}
    ${LIB_AEON_LOGGER_SOURCE}
    ${LIB_AEON_FILESYSTEM_SOURCE}
    ${LIB_AEON_TESTING_SOURCE}
)

if (AEON_ENABLE_CURL)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_CURL_SOURCE})
endif ()

if (AEON_ENABLE_SOCKETS)
    list(APPEND LIB_AEON_SOURCE
        ${LIB_AEON_SOCKETS_SOURCE}
        ${LIB_AEON_WEBSERVER_SOURCE}
    )
endif ()

if (AEON_ENABLE_MONO)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_MONO_SOURCE})
endif ()

add_library(aeon ${LIB_AEON_SOURCE})

set_target_properties(aeon PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon PUBLIC src)

if (AEON_ENABLE_CURL)
    message(STATUS "Building libAeon with CURL support.")
    target_link_libraries(aeon curl)
endif ()

if (AEON_ENABLE_SOCKETS)
    message(STATUS "Building libAeon with Sockets support (Asio).")
    target_link_libraries(aeon asio)
endif ()

if (AEON_ENABLE_MONO)
    message(STATUS "Building libAeon with MONO support.")
    target_link_libraries(aeon ${MONO_LIBRARIES})
    target_include_directories(aeon PUBLIC ${MONO_INCLUDE_PATH} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

install(
    TARGETS aeon
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY src/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)


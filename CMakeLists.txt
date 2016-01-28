set(LIB_AEON_STREAMS_SOURCE
    include/aeon/streams.h
    include/aeon/streams/config.h
    include/aeon/streams/access_mode_mixin.h
    include/aeon/streams/stream_reader.h
    include/aeon/streams/stream_writer.h
    include/aeon/streams/stream.h
    include/aeon/streams/file_stream.h
    src/streams/file_stream.cpp
    include/aeon/streams/io_stream.h
    src/streams/io_stream.cpp
    include/aeon/streams/circular_buffer_stream.h
    include/aeon/streams/memory_stream.h
    include/aeon/streams/stream_name_mixin.h
    include/aeon/streams/io_stream_colors_mixin.h
    src/streams/io_stream_colors_mixin.cpp
)

source_group(streams FILES ${LIB_AEON_STREAMS_SOURCE})

################################################################################

set(LIB_AEON_MATH_SOURCE
    include/aeon/math.h
    include/aeon/math/perlin_noise.h
    src/math/perlin_noise.cpp
    include/aeon/math/simplex_noise.h
    src/math/simplex_noise.cpp
)

source_group(math FILES ${LIB_AEON_MATH_SOURCE})

################################################################################

set(LIB_AEON_SOCKETS_SOURCE
    include/aeon/sockets.h
    include/aeon/sockets/config.h
    include/aeon/sockets/line_protocol_handler.h
    include/aeon/sockets/tcp_server.h
)

source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

################################################################################

set(LIB_AEON_UTILITY_SOURCE
    include/aeon/utility.h
    include/aeon/utility/singleton.h
    include/aeon/utility/configfile.h
    src/utility/configfile.cpp
    include/aeon/utility/hexdump.h
    src/utility/hexdump.cpp
    include/aeon/utility/endianness.h
    src/utility/timer.cpp
    include/aeon/utility/timer.h
    include/aeon/utility/optional.h
    include/aeon/utility/linear_map.h
    include/aeon/utility/variant.h
    include/aeon/utility/noncopyable.h
    include/aeon/utility/string_traits.h
)

source_group(utility FILES ${LIB_AEON_UTILITY_SOURCE})

################################################################################

set(LIB_AEON_PLATFORM_SOURCE
    include/aeon/platform.h
    include/aeon/platform/platform.h
    include/aeon/platform/term_colors.h
    include/aeon/platform/compilers.h
)

source_group(platform FILES ${LIB_AEON_PLATFORM_SOURCE})

################################################################################

set(LIB_AEON_FILESYSTEM_SOURCE
    include/aeon/filesystem.h
    include/aeon/filesystem/filesystem.h
    src/filesystem/filesystem.cpp
)

source_group(filesystem FILES ${LIB_AEON_FILESYSTEM_SOURCE})

################################################################################

set(LIB_AEON_LOGGER_SOURCE
    include/aeon/logger.h
    include/aeon/logger/logger.h
    include/aeon/logger/log_sink.h
    include/aeon/logger/log_level.h
    include/aeon/logger/base_backend.h
    include/aeon/logger/simple_backend.h
    include/aeon/logger/simple_sink_backend.h
    include/aeon/logger/multithreaded_sink_backend.h
    include/aeon/logger/stream_sink.h
    include/aeon/logger/io_stream_sink.h
)

source_group(logger FILES ${LIB_AEON_LOGGER_SOURCE})

################################################################################

if (CURL_FOUND)
    set(LIB_AEON_CURL_SOURCE
        include/aeon/curl.h
        include/aeon/curl/url_downloader.h
        src/curl/url_downloader.cpp
        include/aeon/curl/exceptions.h
        src/curl/global_wrapper.cpp
        include/aeon/curl/global_wrapper.h
        src/curl/easy_wrapper.cpp
        include/aeon/curl/easy_wrapper.h
    )

    source_group(curl FILES ${LIB_AEON_CURL_SOURCE})
endif ()

################################################################################

if (MONO_FOUND)
    set(LIB_AEON_MONO_SOURCE
        include/aeon/mono.h
        src/mono/mono_method.cpp
        include/aeon/mono/mono_method.h
        src/mono/mono_assembly.cpp
        include/aeon/mono/mono_assembly.h
        src/mono/mono_jit.cpp
        include/aeon/mono/mono_jit.h
        src/mono/mono_class.cpp
        include/aeon/mono/mono_class.h
        src/mono/mono_object.cpp
        include/aeon/mono/mono_object.h
        src/mono/mono_string.cpp
        include/aeon/mono/mono_string.h
        src/mono/mono_gchandle.cpp
        include/aeon/mono/mono_gchandle.h
        src/mono/mono_class_instance.cpp
        include/aeon/mono/mono_class_instance.h
        include/aeon/mono/mono_exception.h
    )

    source_group(mono FILES ${LIB_AEON_MONO_SOURCE})
endif ()

################################################################################

set(LIB_AEON_SOURCE
    ${LIB_AEON_STREAMS_SOURCE}
    ${LIB_AEON_MATH_SOURCE}
    ${LIB_AEON_SOCKETS_SOURCE}
    ${LIB_AEON_UTILITY_SOURCE}
    ${LIB_AEON_PLATFORM_SOURCE}
    ${LIB_AEON_LOGGER_SOURCE}
    ${LIB_AEON_FILESYSTEM_SOURCE}
)

if (CURL_FOUND)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_CURL_SOURCE})
endif ()

if (MONO_FOUND)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_MONO_SOURCE})
endif ()

add_library(aeon ${LIB_AEON_SOURCE})

set_target_properties(aeon PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon PRIVATE src)
target_include_directories(aeon PUBLIC include)

if (CURL_FOUND)
    message(STATUS "Building libAeon with CURL support.")
    target_link_libraries(aeon ${CURL_LIBRARIES})
    target_include_directories(aeon PUBLIC ${CURL_INCLUDE_DIRS})
endif ()

if (MONO_FOUND)
    message(STATUS "Building libAeon with MONO support.")
    target_link_libraries(aeon ${MONO_LIBRARIES})
    target_include_directories(aeon PUBLIC ${MONO_INCLUDE_PATH})
endif ()

install(
    TARGETS aeon
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY include/
    DESTINATION include
)


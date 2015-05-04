include_directories(${Boost_INCLUDE_DIRS} src include)

################################################################################

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
)

source_group(utility FILES ${LIB_AEON_UTILITY_SOURCE})

################################################################################

set(LIB_AEON_PLATFORM_SOURCE
    include/aeon/platform.h
    include/aeon/platform/platform.h
    include/aeon/platform/term_colors.h
)

source_group(platform FILES ${LIB_AEON_PLATFORM_SOURCE})

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

set(LIB_AEON_SOURCE
    ${LIB_AEON_STREAMS_SOURCE}
    ${LIB_AEON_MATH_SOURCE}
    ${LIB_AEON_SOCKETS_SOURCE}
    ${LIB_AEON_UTILITY_SOURCE}
    ${LIB_AEON_PLATFORM_SOURCE}
    ${LIB_AEON_LOGGER_SOURCE}
)

add_library(aeon STATIC ${LIB_AEON_SOURCE})

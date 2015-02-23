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
    include/aeon/streams/circular_buffer_stream.h
    include/aeon/streams/memory_stream.h
)

source_group(streams FILES ${LIB_AEON_STREAMS_SOURCE})

################################################################################

set(LIB_AEON_SOCKETS_SOURCE
    include/aeon/sockets.h
    include/aeon/sockets/config.h
    include/aeon/sockets/line_protocol_handler.h
    include/aeon/sockets/tcp_server.h
)

source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

################################################################################

set(LIB_AEON_SOURCE
    ${LIB_AEON_STREAMS_SOURCE}
    ${LIB_AEON_SOCKETS_SOURCE}
)

add_library(aeon STATIC ${LIB_AEON_SOURCE})

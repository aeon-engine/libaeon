# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_STREAMS_SOURCE
    include/aeon/streams/access_mode_mixin.h
    include/aeon/streams/circular_buffer_stream.h
    include/aeon/streams/circular_buffer_stream_fwd.h
    include/aeon/streams/config.h
    include/aeon/streams/file_stream.h
    src/file_stream.cpp
    include/aeon/streams/file_stream_fwd.h
    include/aeon/streams/io_stream.h
    src/io_stream.cpp
    include/aeon/streams/io_stream_fwd.h
    include/aeon/streams/io_stream_colors_mixin.h
    src/io_stream_colors_mixin.cpp
    include/aeon/streams/memory_stream.h
    src/memory_stream.cpp
    include/aeon/streams/memory_stream_fwd.h
    include/aeon/streams/stream.h
    include/aeon/streams/stream_fwd.h
    include/aeon/streams/stream_name_mixin.h
    include/aeon/streams/stream_reader.h
    include/aeon/streams/stream_writer.h
    include/aeon/streams/stream_string_operators.h
    include/aeon/streams/stream_vector_operators.h
)

source_group(streams FILES ${LIB_AEON_STREAMS_SOURCE})

add_library(aeon_streams STATIC ${LIB_AEON_STREAMS_SOURCE})

set_target_properties(aeon_streams PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_streams PUBLIC include)
target_link_libraries(aeon_streams aeon_common)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_streams
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)

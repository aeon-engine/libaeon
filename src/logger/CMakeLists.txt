# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(SOURCES
    private/base_backend.cpp
    private/io_stream_sink.cpp
    private/multithreaded_sink_backend.cpp
    private/simple_backend.cpp
    private/simple_sink_backend.cpp
    private/stream_sink.cpp
    public/aeon/logger/base_backend.h
    public/aeon/logger/io_stream_sink.h
    public/aeon/logger/log_level.h
    public/aeon/logger/log_sink.h
    public/aeon/logger/logger.h
    public/aeon/logger/multithreaded_sink_backend.h
    public/aeon/logger/simple_backend.h
    public/aeon/logger/simple_sink_backend.h
    public/aeon/logger/stream_sink.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_logger STATIC
    ${SOURCES}
)

set_target_properties(aeon_logger PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_logger
    PUBLIC
        public
)

target_link_libraries(aeon_logger
    aeon_common
    aeon_streams
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_logger
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

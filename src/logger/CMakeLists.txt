# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_LOGGER_SOURCE
    include/aeon/logger/base_backend.h
    src/base_backend.cpp
    include/aeon/logger/io_stream_sink.h
    src/io_stream_sink.cpp
    include/aeon/logger/logger.h
    include/aeon/logger/log_level.h
    include/aeon/logger/log_sink.h
    include/aeon/logger/multithreaded_sink_backend.h
    src/multithreaded_sink_backend.cpp
    include/aeon/logger/simple_backend.h
    src/simple_backend.cpp
    include/aeon/logger/simple_sink_backend.h
    src/simple_sink_backend.cpp
    include/aeon/logger/stream_sink.h
    src/stream_sink.cpp
)

source_group(logger FILES ${LIB_AEON_LOGGER_SOURCE})

add_library(aeon_logger STATIC ${LIB_AEON_LOGGER_SOURCE})

set_target_properties(aeon_logger PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_logger PUBLIC include)
target_link_libraries(aeon_logger aeon_common aeon_streams)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_logger
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

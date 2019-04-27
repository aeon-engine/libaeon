# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_LOGGER_PUBLIC_SOURCE
    include/aeon/logger/base_backend.h
    include/aeon/logger/io_stream_sink.h
    include/aeon/logger/logger.h
    include/aeon/logger/log_level.h
    include/aeon/logger/log_sink.h
    include/aeon/logger/multithreaded_sink_backend.h
    include/aeon/logger/simple_backend.h
    include/aeon/logger/simple_sink_backend.h
    include/aeon/logger/stream_sink.h
)

source_group(public FILES ${LIB_AEON_LOGGER_PUBLIC_SOURCE})

set(LIB_AEON_LOGGER_PRIVATE_SOURCE
    src/base_backend.cpp
    src/io_stream_sink.cpp
    src/multithreaded_sink_backend.cpp
    src/simple_backend.cpp
    src/simple_sink_backend.cpp
    src/stream_sink.cpp
)

source_group(private FILES ${LIB_AEON_LOGGER_PRIVATE_SOURCE})

add_library(aeon_logger STATIC
    ${LIB_AEON_LOGGER_PUBLIC_SOURCE}
    ${LIB_AEON_LOGGER_PRIVATE_SOURCE}
)

set_target_properties(aeon_logger PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_logger
    PUBLIC
        include
)

target_link_libraries(aeon_logger
    aeon_common
    aeon_streams
)

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

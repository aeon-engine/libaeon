# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(SOURCES
    private/zlib.cpp
    private/zlib_raii_wrappers.h
    public/aeon/compression/exception.h
    public/aeon/compression/stream_filters/zlib_filter.h
    public/aeon/compression/zlib.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_compression STATIC
    ${SOURCES}
)

set_target_properties(aeon_compression PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_compression
    PUBLIC
        public
)

target_link_libraries(aeon_compression
    aeon_common
    aeon_streams
    ZLIB::ZLIB
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

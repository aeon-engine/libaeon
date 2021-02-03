# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_COMPRESSION_PUBLIC_SOURCE
    include/aeon/compression/exception.h
    include/aeon/compression/zlib.h
)

source_group(public FILES ${LIB_AEON_COMPRESSION_PUBLIC_SOURCE})

set(LIB_AEON_COMPRESSION_PUBLIC_STREAM_FILTERS_SOURCE
    include/aeon/compression/stream_filters/zlib_filter.h
)

source_group(public\\stream_filters FILES ${LIB_AEON_COMPRESSION_PUBLIC_STREAM_FILTERS_SOURCE})

set(LIB_AEON_COMPRESSION_PRIVATE_SOURCE
    src/zlib.cpp
    src/zlib_raii_wrappers.h
)

source_group(private FILES ${LIB_AEON_COMPRESSION_PRIVATE_SOURCE})

add_library(aeon_compression STATIC
    ${LIB_AEON_COMPRESSION_PUBLIC_SOURCE}
    ${LIB_AEON_COMPRESSION_PUBLIC_STREAM_FILTERS_SOURCE}
    ${LIB_AEON_COMPRESSION_PRIVATE_SOURCE}
)

set_target_properties(aeon_compression PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon_compression
    PUBLIC
        include
)

target_link_libraries(aeon_compression
    aeon_common
    aeon_streams
    ZLIB::ZLIB
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

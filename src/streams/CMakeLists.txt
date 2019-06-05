# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_STREAMS_PUBLIC_SOURCE
    include/aeon/streams/aggregate_device.h
    include/aeon/streams/dynamic_stream.h
    include/aeon/streams/dynamic_stream_view.h
    include/aeon/streams/exception.h
    include/aeon/streams/idynamic_stream.h
    include/aeon/streams/length_prefix_string.h
    include/aeon/streams/seek_direction.h
    include/aeon/streams/stream.h
    include/aeon/streams/stream_reader.h
    include/aeon/streams/stream_traits.h
    include/aeon/streams/stream_writer.h
    include/aeon/streams/tags.h
    include/aeon/streams/varint.h
)

source_group(public FILES ${LIB_AEON_STREAMS_PUBLIC_SOURCE})

set(LIB_AEON_STREAMS_PUBLIC_DEVICES_SOURCE
    include/aeon/streams/devices/device.h
    include/aeon/streams/devices/device_view.h
    include/aeon/streams/devices/file_device.h
    include/aeon/streams/devices/iostream_device.h
    include/aeon/streams/devices/memory_device.h
    include/aeon/streams/devices/memory_view_device.h
    include/aeon/streams/devices/span_device.h
    include/aeon/streams/devices/stdio_device.h
)

source_group(public\\devices FILES ${LIB_AEON_STREAMS_PUBLIC_DEVICES_SOURCE})

set(LIB_AEON_STREAMS_PRIVATE_DEVICES_SOURCE
    src/devices/stdio_device.cpp
)

source_group(private\\devices FILES ${LIB_AEON_STREAMS_PRIVATE_DEVICES_SOURCE})

set(LIB_AEON_STREAMS_PUBLIC_DEVICES_DETAIL_SOURCE
    include/aeon/streams/devices/detail/file_device_base.h
    include/aeon/streams/devices/detail/iostream_device_base.h
)

source_group(public\\devices\\detail FILES ${LIB_AEON_STREAMS_PUBLIC_DEVICES_DETAIL_SOURCE})

set(LIB_AEON_STREAMS_PRIVATE_DEVICES_DETAIL_SOURCE
    src/devices/detail/file_device_base.cpp
)

source_group(private\\devices\\detail FILES ${LIB_AEON_STREAMS_PRIVATE_DEVICES_DETAIL_SOURCE})

set(LIB_AEON_STREAMS_PUBLIC_FILTERS_SOURCE
    include/aeon/streams/filters/buffer_filter.h
    include/aeon/streams/filters/circular_buffer_filter.h
    include/aeon/streams/filters/filter.h
    include/aeon/streams/filters/seek_offset_filter.h
    include/aeon/streams/filters/size_filter.h
    include/aeon/streams/filters/zlib_filter.h
)

source_group(public\\filters FILES ${LIB_AEON_STREAMS_PUBLIC_FILTERS_SOURCE})

add_library(aeon_streams STATIC 
    ${LIB_AEON_STREAMS_PUBLIC_SOURCE}
    ${LIB_AEON_STREAMS_PUBLIC_DEVICES_SOURCE}
    ${LIB_AEON_STREAMS_PRIVATE_DEVICES_SOURCE}
    ${LIB_AEON_STREAMS_PUBLIC_DEVICES_DETAIL_SOURCE}
    ${LIB_AEON_STREAMS_PRIVATE_DEVICES_DETAIL_SOURCE}
    ${LIB_AEON_STREAMS_PUBLIC_FILTERS_SOURCE}
)

set_target_properties(aeon_streams PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_streams
    PUBLIC
        include
)

target_link_libraries(aeon_streams
    aeon_common
    ZLIB::ZLIB
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

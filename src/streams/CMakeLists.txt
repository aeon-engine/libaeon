# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

set(SOURCES
    private/devices/detail/file_device_base.cpp
    private/devices/stdio_device.cpp
    public/aeon/streams/aggregate_device.h
    public/aeon/streams/devices/detail/file_device_base.h
    public/aeon/streams/devices/detail/iostream_device_base.h
    public/aeon/streams/devices/device.h
    public/aeon/streams/devices/device_view.h
    public/aeon/streams/devices/file_device.h
    public/aeon/streams/devices/iostream_device.h
    public/aeon/streams/devices/memory_device.h
    public/aeon/streams/devices/memory_view_device.h
    public/aeon/streams/devices/span_device.h
    public/aeon/streams/devices/stdio_device.h
    public/aeon/streams/dynamic_stream.h
    public/aeon/streams/dynamic_stream_view.h
    public/aeon/streams/exception.h
    public/aeon/streams/filters/buffer_filter.h
    public/aeon/streams/filters/circular_buffer_filter.h
    public/aeon/streams/filters/filter.h
    public/aeon/streams/filters/seek_offset_filter.h
    public/aeon/streams/filters/size_filter.h
    public/aeon/streams/idynamic_stream.h
    public/aeon/streams/idynamic_stream_fwd.h
    public/aeon/streams/length_prefix_string.h
    public/aeon/streams/seek_direction.h
    public/aeon/streams/stream.h
    public/aeon/streams/stream_reader.h
    public/aeon/streams/stream_traits.h
    public/aeon/streams/stream_writer.h
    public/aeon/streams/string_stream.h
    public/aeon/streams/tags.h
    public/aeon/streams/uuid_stream.h
    public/aeon/streams/varint.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_streams STATIC 
    ${SOURCES}
)

set_target_properties(aeon_streams PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_streams
    PUBLIC
        public
)

target_link_libraries(aeon_streams
    aeon_common
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

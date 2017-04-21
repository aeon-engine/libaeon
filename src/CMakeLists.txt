# Copyright (c) 2012-2017 Robin Degen
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

# Curl
option(AEON_ENABLE_CURL "Enable the Aeon Curl wrappers." ON)

# Mono
option(AEON_ENABLE_MONO "Enable the Aeon Mono library." OFF)
option(AEON_COPY_MONO_RUNTIMES "Enable if Mono should be embedded and ran purely from the binary folder." OFF)

# Sockets
option(AEON_ENABLE_SOCKETS "Enable the Aeon Socket library." OFF)

# Midi
option(AEON_ENABLE_MIDI "Enable the Aeon Midi IO library." OFF)

# HDF5
option(AEON_ENABLE_HDF5 "Enable the Aeon HDF5 wrapper library." OFF)

################################################################################

add_subdirectory(common)
add_subdirectory(streams)
add_subdirectory(utility)
add_subdirectory(filesystem)
add_subdirectory(testing)
add_subdirectory(math)

if (AEON_ENABLE_CURL)
    add_subdirectory(curl)
endif ()

################################################################################

if (AEON_ENABLE_SOCKETS)
    set(LIB_AEON_SOCKETS_SOURCE
        aeon/sockets.h
        aeon/sockets/config.h
        aeon/sockets/line_protocol_handler.h
        aeon/sockets/tcp_server.h
    )

    source_group(sockets FILES ${LIB_AEON_SOCKETS_SOURCE})

    set(LIB_AEON_WEBSERVER_SOURCE
        aeon/webserver.h
        aeon/webserver/http_protocol_handler.h
        aeon/webserver/http_protocol_handler.cpp
        aeon/webserver/http_request.h
        aeon/webserver/http_request.cpp
    )

    source_group(webserver FILES ${LIB_AEON_WEBSERVER_SOURCE})
endif ()

################################################################################

set(LIB_AEON_LOGGER_SOURCE
    aeon/logger.h
    aeon/logger/logger.h
    aeon/logger/log_sink.h
    aeon/logger/log_level.h
    aeon/logger/base_backend.h
    aeon/logger/simple_backend.h
    aeon/logger/simple_sink_backend.h
    aeon/logger/multithreaded_sink_backend.h
    aeon/logger/stream_sink.h
    aeon/logger/io_stream_sink.h
)

source_group(logger FILES ${LIB_AEON_LOGGER_SOURCE})

################################################################################

if (AEON_ENABLE_MONO)
    include(Mono)

    if (AEON_COPY_MONO_RUNTIMES)
        copy_mono_runtimes_to_runtime_path()
        set(_MONO_ASSEMBLY_DIR ".")
        set(_MONO_CONFIG_DIR ".")
    else ()
        set(_MONO_ASSEMBLY_DIR ${MONO_ASSEMBLY_PATH})
        set(_MONO_CONFIG_DIR ${MONO_CONFIG_PATH})
    endif ()

    set(AEON_MONO_ASSEMBLY_DIR "${_MONO_ASSEMBLY_DIR}"
        CACHE PATH "Path to the Mono assembly dir (mono/lib). May be a relative path.")
    set(AEON_MONO_CONFIG_DIR "${_MONO_CONFIG_DIR}"
        CACHE PATH "Path to the Mono config dir (mono/etc). May be a relative path.")

    configure_file(src/aeon/mono/mono_build_config.h.in mono_build_config.h @ONLY)

    set(LIB_AEON_MONO_SOURCE
        aeon/mono.h
        aeon/mono/mono_method.cpp
        aeon/mono/mono_method.h
        aeon/mono/mono_assembly.cpp
        aeon/mono/mono_assembly.h
        aeon/mono/mono_jit.cpp
        aeon/mono/mono_jit.h
        aeon/mono/mono_class.cpp
        aeon/mono/mono_class.h
        aeon/mono/mono_object.cpp
        aeon/mono/mono_object.h
        aeon/mono/mono_string.cpp
        aeon/mono/mono_string.h
        aeon/mono/mono_gchandle.cpp
        aeon/mono/mono_gchandle.h
        aeon/mono/mono_class_instance.cpp
        aeon/mono/mono_class_instance.h
        aeon/mono/mono_exception.h
        ${CMAKE_CURRENT_BINARY_DIR}/mono_build_config.h
    )

    source_group(mono FILES ${LIB_AEON_MONO_SOURCE})
endif ()

################################################################################

if (AEON_ENABLE_MIDI)
    set(LIB_AEON_MIDI_SOURCE
        aeon/midi.h
        aeon/midi/midi_device.cpp
        aeon/midi/midi_device.h
        aeon/midi/midi_file_reader.cpp
        aeon/midi/midi_file_reader.h
        aeon/midi/midi_input_device.cpp
        aeon/midi/midi_input_device.h
        aeon/midi/midi_input_manager.cpp
        aeon/midi/midi_input_manager.h
        aeon/midi/midi_output_device.cpp
        aeon/midi/midi_output_device.h
        aeon/midi/midi_messages.h
    )

    source_group(midi FILES ${LIB_AEON_MIDI_SOURCE})
endif ()

################################################################################

if (AEON_ENABLE_HDF5)
    set(LIB_AEON_HDF5_SOURCE
        aeon/hdf5.h
        aeon/hdf5/hdf5_file.h
        aeon/hdf5/hdf5_file_impl.h
        aeon/hdf5/hdf5_dataset.h
        aeon/hdf5/hdf5_dataset_impl.h
        aeon/hdf5/hdf5_dataset_wrapper.h
        aeon/hdf5/hdf5_dataset_wrapper_impl.h
        aeon/hdf5/hdf5_dataset_properties.h
        aeon/hdf5/hdf5_dataset_properties_impl.h
        aeon/hdf5/hdf5_dataspace.h
        aeon/hdf5/hdf5_dataspace_impl.h
        aeon/hdf5/hdf5_datatype.h
        aeon/hdf5/hdf5_datatype_impl.h
        aeon/hdf5/hdf5_scoped_create_group.h
        aeon/hdf5/hdf5_scoped_create_group_impl.h
        aeon/hdf5/hdf5_object.h
        aeon/hdf5/hdf5_object_impl.h
        aeon/hdf5/hdf5_object_iterator.h
        aeon/hdf5/hdf5_object_iterator_impl.h
    )

    source_group(hdf5 FILES ${LIB_AEON_HDF5_SOURCE})
endif ()

################################################################################

set(LIB_AEON_SOURCE
    ${LIB_AEON_LOGGER_SOURCE}
)

if (AEON_ENABLE_SOCKETS)
    list(APPEND LIB_AEON_SOURCE
        ${LIB_AEON_SOCKETS_SOURCE}
        ${LIB_AEON_WEBSERVER_SOURCE}
    )
endif ()

if (AEON_ENABLE_MONO)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_MONO_SOURCE})
endif ()

if (AEON_ENABLE_MIDI)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_MIDI_SOURCE})
endif ()

if (AEON_ENABLE_HDF5)
    list(APPEND LIB_AEON_SOURCE ${LIB_AEON_HDF5_SOURCE})
endif ()

add_library(aeon ${LIB_AEON_SOURCE})

target_link_libraries(aeon aeon_common aeon_utility aeon_filesystem)

set_target_properties(aeon PROPERTIES
    FOLDER dep/libaeon
)

target_include_directories(aeon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (AEON_ENABLE_SOCKETS)
    message(STATUS "Building libAeon with Sockets support (Asio).")
    target_link_libraries(aeon asio)
endif ()

if (AEON_ENABLE_MONO)
    message(STATUS "Building libAeon with MONO support.")
    target_link_libraries(aeon ${MONO_LIBRARIES})
    target_include_directories(aeon PUBLIC ${MONO_INCLUDE_PATH} ${CMAKE_CURRENT_BINARY_DIR})
endif ()

if (AEON_ENABLE_MIDI)
    message(STATUS "Building libAeon with MIDI support.")
    target_link_libraries(aeon rtmidi)
endif ()

if (AEON_ENABLE_HDF5)
    message(STATUS "Building libAeon with HDF5 wrapper support.")
    target_link_libraries(aeon hdf5-static hdf5_hl-static)
endif ()

install(
    TARGETS aeon
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_RTMIDI_PUBLIC_SOURCE
    include/aeon/midi/midi_device.h
    include/aeon/midi/midi_file_reader.h
    include/aeon/midi/midi_input_device.h
    include/aeon/midi/midi_input_manager.h
    include/aeon/midi/midi_messages.h
    include/aeon/midi/midi_output_device.h
)

source_group(public FILES ${LIB_AEON_RTMIDI_PUBLIC_SOURCE})

set(LIB_AEON_RTMIDI_PRIVATE_SOURCE
    src/midi_device.cpp
    src/midi_file_reader.cpp
    src/midi_input_device.cpp
    src/midi_input_manager.cpp
    src/midi_output_device.cpp
)

source_group(private FILES ${LIB_AEON_RTMIDI_PRIVATE_SOURCE})

add_library(aeon_midi STATIC
    ${LIB_AEON_RTMIDI_PUBLIC_SOURCE}
    ${LIB_AEON_RTMIDI_PRIVATE_SOURCE}
)

set_target_properties(aeon_midi PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_midi
    PUBLIC
        include
)

target_link_libraries(aeon_midi
    aeon_common
    aeon_streams
    RTMidi::RTMidi
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_midi
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

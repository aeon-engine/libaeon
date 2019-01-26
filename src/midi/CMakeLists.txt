# Copyright (c) 2012-2019 Robin Degen

message(STATUS "Building libAeon with RtMidi support.")

set(LIB_AEON_RTMIDI_SOURCE
    include/aeon/midi/midi_device.h
    src/midi_device.cpp
    include/aeon/midi/midi_file_reader.h
    src/midi_file_reader.cpp
    include/aeon/midi/midi_input_device.h
    src/midi_input_device.cpp
    include/aeon/midi/midi_input_manager.h
    src/midi_input_manager.cpp
    include/aeon/midi/midi_messages.h
    include/aeon/midi/midi_output_device.h
    src/midi_output_device.cpp
)

source_group(midi FILES ${LIB_AEON_RTMIDI_SOURCE})

add_library(aeon_midi STATIC ${LIB_AEON_RTMIDI_SOURCE})

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
    aeon_utility
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

add_subdirectory(tests)

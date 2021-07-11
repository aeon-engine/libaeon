# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/midi_device.cpp
    private/midi_file_reader.cpp
    private/midi_input_device.cpp
    private/midi_input_manager.cpp
    private/midi_output_device.cpp
    private/midi_utils.cpp
    public/aeon/midi/midi_device.h
    public/aeon/midi/midi_file_reader.h
    public/aeon/midi/midi_input_device.h
    public/aeon/midi/midi_input_manager.h
    public/aeon/midi/midi_messages.h
    public/aeon/midi/midi_output_device.h
    public/aeon/midi/midi_utils.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_midi STATIC
    ${SOURCES}
)

set_target_properties(aeon_midi PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_midi
    PUBLIC
        public
)

target_link_libraries(aeon_midi
    aeon_common
    aeon_streams
    CONAN_PKG::rtmidi
)

install(
    DIRECTORY public/aeon
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

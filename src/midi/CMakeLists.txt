# Copyright (c) 2012-2018 Robin Degen
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

message(STATUS "Building libAeon with RtMidi support.")

add_subdirectory(${CMAKE_SOURCE_DIR}/dep/rtmidi dep/rtmidi)

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

target_include_directories(aeon_midi PUBLIC include)
target_link_libraries(aeon_midi aeon_common aeon_utility aeon_streams rtmidi)

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

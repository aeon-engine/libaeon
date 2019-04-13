# Copyright (c) 2012-2019 Robin Degen

# Mono
option(AEON_ENABLE_MONO "Enable the Aeon Mono library." OFF)

# Sockets
option(AEON_ENABLE_SOCKETS "Enable the Aeon Socket library." OFF)

# Serial
option(AEON_ENABLE_SERIAL "Enable the Aeon Serial library." OFF)

# Midi
option(AEON_ENABLE_MIDI "Enable the Aeon Midi IO library." OFF)

# Imaging
option(AEON_ENABLE_IMAGING "Enable the Aeon imaging library." OFF)

# Fonts
option(AEON_ENABLE_FONTS "Enable the Aeon fonts library (requires AEON_ENABLE_IMAGING)." OFF)

################################################################################

add_subdirectory(common)
add_subdirectory(logger)
add_subdirectory(math)
add_subdirectory(plugins)
add_subdirectory(ptree)
add_subdirectory(rdp)
add_subdirectory(streams)
add_subdirectory(testing)
add_subdirectory(tracelog)
add_subdirectory(utility)
add_subdirectory(unicode)

if (AEON_ENABLE_MONO)
    add_subdirectory(mono)
endif ()

if (AEON_ENABLE_MIDI)
    add_subdirectory(midi)
endif ()

if (AEON_ENABLE_SOCKETS)
    add_subdirectory(sockets)
endif ()

if (AEON_ENABLE_SERIAL)
    add_subdirectory(serial)
endif ()

if (AEON_ENABLE_IMAGING)
    add_subdirectory(imaging)
endif ()

if (AEON_ENABLE_FONTS)
    if (NOT AEON_ENABLE_IMAGING)
        message(FATAL_ERROR "The Aeon Fonts library requires Imaging.")
    endif ()

    add_subdirectory(fonts)
endif ()

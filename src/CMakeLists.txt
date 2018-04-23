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

# Curl
option(AEON_ENABLE_CURL "Enable the Aeon Curl wrappers." OFF)

# Mono
option(AEON_ENABLE_MONO "Enable the Aeon Mono library." OFF)

# Sockets
option(AEON_ENABLE_SOCKETS "Enable the Aeon Socket library." OFF)

# Midi
option(AEON_ENABLE_MIDI "Enable the Aeon Midi IO library." OFF)

# HDF5
option(AEON_ENABLE_HDF5 "Enable the Aeon HDF5 wrapper library." OFF)

# Imaging
option(AEON_ENABLE_IMAGING "Enable the Aeon imaging library." OFF)

################################################################################

add_subdirectory(common)
add_subdirectory(streams)
add_subdirectory(utility)
add_subdirectory(filesystem)
add_subdirectory(testing)
add_subdirectory(math)
add_subdirectory(logger)
add_subdirectory(plugins)
add_subdirectory(types)

if (AEON_ENABLE_CURL)
    add_subdirectory(curl)
endif ()

if (AEON_ENABLE_MONO)
    add_subdirectory(mono)
endif ()

if (AEON_ENABLE_MIDI)
    add_subdirectory(midi)
endif ()

if (AEON_ENABLE_SOCKETS)
    add_subdirectory(sockets)
endif ()

if (AEON_ENABLE_HDF5)
    add_subdirectory(hdf5)
endif ()

if (AEON_ENABLE_IMAGING)
    add_subdirectory(imaging)
endif ()

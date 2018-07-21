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

cmake_minimum_required(VERSION 3.10)

if (DEFINED ENV{LIBAEON_PROJECT_NAME})
    project($ENV{LIBAEON_PROJECT_NAME})
else ()
    project(libAeon)
endif ()

# Create compile_commands.json when possible, which can be used for
# analysis tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dep/cmake")

include(CompilerFlags)

set(CMAKE_CXX_STANDARD 17)

################################################################################

option(AEON_ENABLE_COVERAGE "Enable code coverage. Requires linux with GCC 5.1.0 or higher." OFF)

if (AEON_ENABLE_COVERAGE)
    include(Coverage)
    enable_coverage()
endif ()

################################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################

# If mono is found on the system; attempt to build with it enabled.
find_package(Mono)
if (MONO_FOUND)
    set(AEON_ENABLE_MONO ON CACHE BOOL "")
endif ()

set(AEON_ENABLE_SOCKETS ON CACHE BOOL "")
set(AEON_ENABLE_SERIAL ON CACHE BOOL "")
set(AEON_ENABLE_MIDI ON CACHE BOOL "")
set(AEON_ENABLE_HDF5 ON CACHE BOOL "")
set(AEON_ENABLE_IMAGING ON CACHE BOOL "")

add_subdirectory(dep/googletest)

################################################################################

option(AEON_ENABLE_BENCHMARK "Enable google benchmarking tests." ON)

if (AEON_ENABLE_BENCHMARK)
    message(STATUS "Building libAeon with Google Benchmark support.")
    add_subdirectory(dep/google_benchmark)
endif ()

################################################################################

add_subdirectory(src)

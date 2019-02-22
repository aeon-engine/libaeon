# Copyright (c) 2012-2019 Robin Degen

cmake_minimum_required(VERSION 3.11)

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

include(Dependencies)
handle_dependencies_file("${CMAKE_SOURCE_DIR}/dependencies.txt")

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
set(AEON_ENABLE_IMAGING ON CACHE BOOL "")
set(AEON_ENABLE_FONTS ON CACHE BOOL "")

################################################################################

option(AEON_ENABLE_BENCHMARK "Enable google benchmarking tests." ON)

if (AEON_ENABLE_BENCHMARK)
    message(STATUS "Building libAeon with Google Benchmark support.")
endif ()

################################################################################

option(AEON_ENABLE_DOXYGEN "Enable doxygen documentation (if doxygen is installed)." ON)

if (AEON_ENABLE_DOXYGEN)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        message(STATUS "Generating doxygen documentation.")

        set(DOXYGEN_PROJECT_NAME "libAeon")
        set(DOXYGEN_PROJECT_BRIEF "A C++17 support library.")

        if (MSVC)
            set(DOXYGEN_WARN_FORMAT "$file($line) : $text")
        endif()

        doxygen_add_docs(aeon_documentation src)

        set_target_properties(aeon_documentation PROPERTIES
            FOLDER dep/libaeon/docs
            EXCLUDE_FROM_ALL 1
            EXCLUDE_FROM_DEFAULT_BUILD 1
        )
    else ()
        message(STATUS "Doxygen not installed. Skipping generating documentation.")
    endif()
endif ()

################################################################################

add_subdirectory(src)

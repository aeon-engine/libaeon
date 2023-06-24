# Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

cmake_minimum_required(VERSION 3.27)

if (DEFINED ENV{LIBAEON_PROJECT_NAME})
    project($ENV{LIBAEON_PROJECT_NAME})
else ()
    project(libAeon)
endif ()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_DEBUG_POSTFIX _d)

# Create compile_commands.json when possible, which can be used for
# analysis tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_CURRENT_SOURCE_DIR}/dep/cmake")
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

option(AEON_ENABLE_CONAN_INTEGRATION "Enable automatic installation of Conan packages as part of the CMake configure step." ON)

set(CMAKE_CXX_STANDARD 23)

if (AEON_ENABLE_CONAN_INTEGRATION)
    include(Conan)
    conan_install()
endif ()

include(CompilerFlags)

option(AEON_ENABLE_TESTING "Enable testing." ON)

if (AEON_ENABLE_TESTING)
    find_package(GTest CONFIG)

    set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
    include(CTest)
    enable_testing()
endif ()

################################################################################

option(AEON_ENABLE_COVERAGE "Enable code coverage. Requires linux with GCC 10 or higher." OFF)

if (AEON_ENABLE_COVERAGE)
    include(Coverage)
    enable_coverage()
endif ()

################################################################################

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################

option(BUILD_SHARED_LIBS "Build shared libraries if possible" ON)

include(ComponentUtils)
enable_component(common)
enable_component(compression)
enable_component(crypto)
enable_component(file_container)
enable_component(fonts)
enable_component(imaging)
enable_component(logger)
enable_component(math)
enable_component(platform)
enable_component(plugins)
enable_component(ptree)
enable_component(rdp)
enable_component(reflection)
enable_component(serial)
enable_component(sockets)
enable_component(streams)
enable_component(testing)
enable_component(tracelog)
enable_component(unicode)
enable_component(variant)
enable_component(web)

# If the LunarG Vulkan SDK is found on the system; attempt to build the vulkan subsystem
find_package(Vulkan)
if (Vulkan_FOUND)
    enable_component(vulkan)
endif ()

################################################################################

option(AEON_ENABLE_BENCHMARK "Enable google benchmarking tests." ON)

if (AEON_ENABLE_BENCHMARK)
    find_package(benchmark CONFIG)
    message(STATUS "Building libAeon with Google Benchmark support.")
endif ()

################################################################################

option(AEON_ENABLE_DOXYGEN "Enable doxygen documentation (if doxygen is installed)." ON)

if (AEON_ENABLE_DOXYGEN)
    find_package(Doxygen)

    if (DOXYGEN_FOUND)
        message(STATUS "Generating doxygen documentation.")

        set(DOXYGEN_PROJECT_NAME "libAeon")
        set(DOXYGEN_PROJECT_BRIEF "A C++20 support library.")

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
add_subdirectory(tools)

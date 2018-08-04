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

message(STATUS "Building libAeon with MONO support.")

if (NOT MONO_FOUND)
    find_package(Mono)
endif ()

include(Mono)

option(AEON_COPY_MONO_RUNTIMES "Enable if Mono should be embedded and ran purely from the binary folder." OFF)

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

configure_file(mono_build_config.h.in mono_build_config.h @ONLY)

set(LIB_AEON_MONO_SOURCE
    include/aeon/mono/mono_assembly.h
    src/mono_assembly.cpp
    include/aeon/mono/mono_class.h
    src/mono_class.cpp
    include/aeon/mono/mono_class_instance.h
    src/mono_class_instance.cpp
    include/aeon/mono/mono_exception.h
    src/mono_exception.cpp
    include/aeon/mono/mono_gc_handle.h
    src/mono_gc_handle.cpp
    include/aeon/mono/mono_jit.h
    src/mono_jit.cpp
    include/aeon/mono/mono_method.h
    src/mono_method.cpp
    include/aeon/mono/mono_object.h
    src/mono_object.cpp
    include/aeon/mono/mono_string.h
    src/mono_string.cpp
    include/aeon/mono/mono_class_field.h
    src/mono_class_field.cpp
    include/aeon/mono/mono_static_function.h
    src/mono_static_function.cpp
    include/aeon/mono/mono_thunk_base.h
    include/aeon/mono/mono_thunk.h
    include/aeon/mono/mono_method_thunk.h
    include/aeon/mono/mono_type_conversion.h
    include/aeon/mono/mono_thunk_signature.h
)

source_group(mono FILES ${LIB_AEON_MONO_SOURCE})

add_library(aeon_mono STATIC ${LIB_AEON_MONO_SOURCE})

set_target_properties(aeon_mono PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_mono
    PUBLIC
        include
        ${MONO_INCLUDE_PATH}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(aeon_mono aeon_common ${MONO_LIBRARIES})

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_mono
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)

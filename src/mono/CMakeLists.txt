# Copyright (c) 2012-2019 Robin Degen

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

set(LIB_AEON_MONO_PUBLIC_SOURCE
    include/aeon/mono/mono_assembly.h
    include/aeon/mono/mono_class.h
    include/aeon/mono/mono_class_instance.h
    include/aeon/mono/mono_exception.h
    include/aeon/mono/mono_gc_handle.h
    include/aeon/mono/mono_jit.h
    include/aeon/mono/mono_method.h
    include/aeon/mono/mono_object.h
    include/aeon/mono/mono_string.h
    include/aeon/mono/mono_class_field.h
    include/aeon/mono/mono_static_function.h
    include/aeon/mono/mono_thunk_base.h
    include/aeon/mono/mono_thunk.h
    include/aeon/mono/mono_method_thunk.h
    include/aeon/mono/mono_type_conversion.h
    include/aeon/mono/mono_thunk_signature.h
)

source_group(public FILES ${LIB_AEON_MONO_PUBLIC_SOURCE})

set(LIB_AEON_MONO_PRIVATE_SOURCE
    src/mono_assembly.cpp
    src/mono_class.cpp
    src/mono_class_instance.cpp
    src/mono_exception.cpp
    src/mono_gc_handle.cpp
    src/mono_jit.cpp
    src/mono_method.cpp
    src/mono_object.cpp
    src/mono_string.cpp
    src/mono_class_field.cpp
    src/mono_static_function.cpp
)

source_group(private FILES ${LIB_AEON_MONO_PRIVATE_SOURCE})

add_library(aeon_mono STATIC
    ${LIB_AEON_MONO_PUBLIC_SOURCE}
    ${LIB_AEON_MONO_PRIVATE_SOURCE}
)

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

target_link_libraries(aeon_mono
    aeon_common
    ${MONO_LIBRARIES}
)

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

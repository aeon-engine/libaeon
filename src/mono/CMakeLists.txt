# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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

set(SOURCES
    private/mono_assembly.cpp
    private/mono_class.cpp
    private/mono_class_field.cpp
    private/mono_class_instance.cpp
    private/mono_exception.cpp
    private/mono_gc_handle.cpp
    private/mono_jit.cpp
    private/mono_method.cpp
    private/mono_object.cpp
    private/mono_static_function.cpp
    private/mono_string.cpp
    public/aeon/mono/mono_assembly.h
    public/aeon/mono/mono_class.h
    public/aeon/mono/mono_class_field.h
    public/aeon/mono/mono_class_instance.h
    public/aeon/mono/mono_exception.h
    public/aeon/mono/mono_gc_handle.h
    public/aeon/mono/mono_jit.h
    public/aeon/mono/mono_method.h
    public/aeon/mono/mono_method_thunk.h
    public/aeon/mono/mono_object.h
    public/aeon/mono/mono_static_function.h
    public/aeon/mono/mono_string.h
    public/aeon/mono/mono_thunk.h
    public/aeon/mono/mono_thunk_base.h
    public/aeon/mono/mono_thunk_signature.h
    public/aeon/mono/mono_type_conversion.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_mono STATIC
    ${SOURCES}
)

set_target_properties(aeon_mono PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_mono
    PUBLIC
        public
        ${MONO_INCLUDE_PATH}
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(aeon_mono
    aeon_common
    ${MONO_LIBRARIES}
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_mono
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

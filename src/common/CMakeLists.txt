# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(SOURCES
    private/base64.cpp
    private/commandline_parser.cpp
    private/dll_loader.cpp
    private/from_chars.cpp
    private/hexdump.cpp
    private/lexical_parse.cpp
    private/string.cpp
    private/uuid.cpp
    public/aeon/common/assert.h
    public/aeon/common/base64.h
    public/aeon/common/bits.h
    public/aeon/common/bom.h
    public/aeon/common/cached_container.h
    public/aeon/common/collection.h
    public/aeon/common/color.h
    public/aeon/common/color_limits.h
    public/aeon/common/commandline_parser.h
    public/aeon/common/compilers.h
    public/aeon/common/concepts.h
    public/aeon/common/container.h
    public/aeon/common/delay.h
    public/aeon/common/deprecated.h
    public/aeon/common/dispatcher.h
    public/aeon/common/dispatcher_fwd.h
    public/aeon/common/dll_export.h
    public/aeon/common/dll_loader.h
    public/aeon/common/element_type.h
    public/aeon/common/endianness.h
    public/aeon/common/expect.h
    public/aeon/common/flags.h
    public/aeon/common/fmtflags.h
    public/aeon/common/fourcc.h
    public/aeon/common/from_chars.h
    public/aeon/common/hash.h
    public/aeon/common/hexdump.h
    public/aeon/common/impl/color_impl.h
    public/aeon/common/impl/string_impl.h
    public/aeon/common/impl/version_impl.h
    public/aeon/common/intrinsics.h
    public/aeon/common/intrusive_ptr.h
    public/aeon/common/lexical_parse.h
    public/aeon/common/listener_subject.h
    public/aeon/common/literals.h
    public/aeon/common/memory.h
    public/aeon/common/parallelizer.h
    public/aeon/common/parameters.h
    public/aeon/common/platform.h
    public/aeon/common/preprocessor.h
    public/aeon/common/scope_guard.h
    public/aeon/common/shared_vector.h
    public/aeon/common/shared_vector_fwd.h
    public/aeon/common/signals.h
    public/aeon/common/signed_sizeof.h
    public/aeon/common/singleton.h
    public/aeon/common/string.h
    public/aeon/common/string_table.h
    public/aeon/common/string_traits.h
    public/aeon/common/tempfile.h
    public/aeon/common/term_colors.h
    public/aeon/common/timer.h
    public/aeon/common/tribool.h
    public/aeon/common/type_traits.h
    public/aeon/common/unique_obj.h
    public/aeon/common/unordered_flatmap.h
    public/aeon/common/unordered_flatset.h
    public/aeon/common/uuid.h
    public/aeon/common/version.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_common STATIC
    ${SOURCES}
)

set_target_properties(aeon_common PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_common
    PUBLIC
        public
    PRIVATE
        ${CMAKE_BINARY_DIR}
)

# On linux, we must link with libdl to use dlopen, dlclose etc.
if (UNIX AND NOT APPLE)
    target_link_libraries(aeon_common dl)
endif ()

# On unix we must link to a threading library like pthread
if (UNIX)
    set(CMAKE_THREAD_PREFER_PTHREAD ON)
    find_package(Threads)

    target_link_libraries(aeon_common
        ${CMAKE_THREAD_LIBS_INIT}
    )
endif ()

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

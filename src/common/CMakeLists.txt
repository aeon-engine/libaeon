# Copyright (c) 2012-2019 Robin Degen

set(LIB_AEON_COMMON_PUBLIC_SOURCE
    include/aeon/common/assert.h
    include/aeon/common/bitflags.h
    include/aeon/common/compilers.h
    include/aeon/common/container.h
    include/aeon/common/deprecated.h
    include/aeon/common/dll_export.h
    include/aeon/common/dll_loader.h
    include/aeon/common/endianness.h
    include/aeon/common/flags.h
    include/aeon/common/fourcc.h
    include/aeon/common/intrinsics.h
    include/aeon/common/literals.h
    include/aeon/common/lexical_parse.h
    include/aeon/common/platform.h
    include/aeon/common/preprocessor.h
    include/aeon/common/scope_guard.h
    include/aeon/common/signed_sizeof.h
    include/aeon/common/singleton.h
    include/aeon/common/span.h
    include/aeon/common/stdfilesystem.h
    include/aeon/common/string.h
    include/aeon/common/string_table.h
    include/aeon/common/string_traits.h
    include/aeon/common/term_colors.h
    include/aeon/common/timer.h
    include/aeon/common/type_traits.h
    include/aeon/common/unused.h
    include/aeon/common/variant.h
    include/aeon/common/version.h
)

source_group(public FILES ${LIB_AEON_COMMON_PUBLIC_SOURCE})

set(LIB_AEON_COMMON_PUBLIC_IMPL_SOURCE
    include/aeon/common/impl/string_impl.h
)

source_group(public\\impl FILES ${LIB_AEON_COMMON_PUBLIC_IMPL_SOURCE})

set(LIB_AEON_COMMON_PRIVATE_SOURCE
    src/dll_loader.cpp
    src/lexical_parse.cpp
    src/string.cpp
)

source_group(private FILES ${LIB_AEON_COMMON_PRIVATE_SOURCE})

add_library(aeon_common STATIC
    ${LIB_AEON_COMMON_PUBLIC_SOURCE}
    ${LIB_AEON_COMMON_PUBLIC_IMPL_SOURCE}
    ${LIB_AEON_COMMON_PRIVATE_SOURCE}
)

set_target_properties(aeon_common PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_common
    PUBLIC
        include
    PRIVATE
        ${CMAKE_BINARY_DIR}
)

# On linux, we must link with libdl to use dlopen, dlclose etc.
if (UNIX AND NOT APPLE)
    target_link_libraries(aeon_common dl)
endif ()

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_common
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

add_subdirectory(tests)

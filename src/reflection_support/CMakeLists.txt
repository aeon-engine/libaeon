# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

set(LIB_AEON_REFLECTION_SUPPORT_PUBLIC_SOURCE
    include/aeon/reflection_support/annotate.h
)

source_group(public FILES ${LIB_AEON_REFLECTION_SUPPORT_PUBLIC_SOURCE})

add_library(aeon_reflection_support INTERFACE)

target_sources(aeon_reflection_support
    INTERFACE
        ${LIB_AEON_REFLECTION_SUPPORT_PUBLIC_SOURCE}
)

target_include_directories(aeon_reflection_support
    INTERFACE
        include
        ${CMAKE_CURRENT_BINARY_DIR}
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_reflection_support
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

set(AEON_REFLECTION_SUPPORT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
configure_file(reflection_support_path.h.in reflection_support_path.h @ONLY)

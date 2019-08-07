# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

set(LIB_AEON_REFLECTION_PUBLIC_SOURCE
    include/aeon/reflection/annotate.h
)

source_group(public FILES ${LIB_AEON_REFLECTION_PUBLIC_SOURCE})

add_library(aeon_reflection INTERFACE)

target_sources(aeon_reflection
    INTERFACE
        ${LIB_AEON_REFLECTION_PUBLIC_SOURCE}
)

target_include_directories(aeon_reflection
    INTERFACE
        include
        ${CMAKE_CURRENT_BINARY_DIR}
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_reflection
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

set(AEON_REFLECTION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
configure_file(reflection_path.h.in reflection_path.h @ONLY)

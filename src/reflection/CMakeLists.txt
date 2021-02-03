# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(LIB_AEON_REFLECTION_PUBLIC_SOURCE
    include/aeon/reflection/annotate.h
    include/aeon/reflection/exception.h
    include/aeon/reflection/field_info.h
    include/aeon/reflection/reflection.h
    include/aeon/reflection/reflection_info.h
    include/aeon/reflection/reflection_object.h
)

source_group(public FILES ${LIB_AEON_REFLECTION_PUBLIC_SOURCE})

set(LIB_AEON_REFLECTION_PRIVATE_SOURCE
    src/reflection_info.cpp
)

source_group(private FILES ${LIB_AEON_REFLECTION_PRIVATE_SOURCE})

add_library(aeon_reflection STATIC
    ${LIB_AEON_REFLECTION_PUBLIC_SOURCE}
    ${LIB_AEON_REFLECTION_PRIVATE_SOURCE}
)

set_target_properties(aeon_reflection PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_reflection
    PUBLIC
        include
        ${CMAKE_CURRENT_BINARY_DIR}
    PRIVATE
        src
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

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

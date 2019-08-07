# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_CLANG_PUBLIC_SOURCE
    include/aeon/clang/parser_settings.h
    include/aeon/clang/reflection.h
)

source_group(public FILES ${LIB_AEON_CLANG_PUBLIC_SOURCE})

set(LIB_AEON_CLANG_PRIVATE_SOURCE
    src/clang_index.h
    src/clang_string.h
    src/clang_translation_unit.h
    src/clang_visitor.h
    src/entity_visitor.cpp
    src/entity_visitor.h
    src/parser_settings.cpp
    src/reflection.cpp
)

source_group(private FILES ${LIB_AEON_CLANG_PRIVATE_SOURCE})

add_library(aeon_clang STATIC
    ${LIB_AEON_CLANG_PUBLIC_SOURCE}
    ${LIB_AEON_CLANG_PRIVATE_SOURCE}
)

set_target_properties(aeon_clang PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_clang
    PUBLIC
        include
)

target_link_libraries(aeon_clang
    aeon_ast
    aeon_common
    aeon_streams
    aeon_reflection
    Clang::Clang
)

install(
    DIRECTORY include/aeon
    DESTINATION include
)

install(
    TARGETS aeon_clang
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

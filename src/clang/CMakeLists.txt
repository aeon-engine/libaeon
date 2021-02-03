# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_CLANG_PUBLIC_SOURCE
    include/aeon/clang/ast_entity_visitor.h
    include/aeon/clang/ast_parser.h
    include/aeon/clang/index.h
    include/aeon/clang/parser_settings.h
    include/aeon/clang/string.h
    include/aeon/clang/translation_unit.h
    include/aeon/clang/visitor.h
)

source_group(public FILES ${LIB_AEON_CLANG_PUBLIC_SOURCE})

set(LIB_AEON_CLANG_PRIVATE_SOURCE
    src/ast_entity_visitor.cpp
    src/ast_parser.cpp
    src/index.cpp
    src/parser_settings.cpp
    src/string.cpp
    src/translation_unit.cpp
    src/visitor.cpp
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

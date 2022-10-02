# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

find_package(libclang CONFIG)

set(SOURCES
    private/ast_entity_visitor.cpp
    private/ast_parser.cpp
    private/index.cpp
    private/parser_settings.cpp
    private/string.cpp
    private/translation_unit.cpp
    private/visitor.cpp
    public/aeon/clang/ast_entity_visitor.h
    public/aeon/clang/ast_parser.h
    public/aeon/clang/index.h
    public/aeon/clang/parser_settings.h
    public/aeon/clang/string.h
    public/aeon/clang/translation_unit.h
    public/aeon/clang/visitor.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_clang STATIC
    ${SOURCES}
)

set_target_properties(aeon_clang PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_clang
    PUBLIC
        public
)

target_link_libraries(aeon_clang
    aeon_ast
    aeon_common
    aeon_streams
    aeon_reflection
    libclang::libclang
)

install(
    DIRECTORY public/aeon
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

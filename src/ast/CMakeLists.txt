# Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

set(SOURCES
    private/basic_printer.cpp
    public/aeon/ast/access_specifier.h
    public/aeon/ast/basic_printer.h
    public/aeon/ast/class.h
    public/aeon/ast/constructor.h
    public/aeon/ast/destructor.h
    public/aeon/ast/entity.h
    public/aeon/ast/entity_collection.h
    public/aeon/ast/entity_type.h
    public/aeon/ast/entity_type_traits.h
    public/aeon/ast/enum.h
    public/aeon/ast/exception.h
    public/aeon/ast/field.h
    public/aeon/ast/function.h
    public/aeon/ast/function_collection.h
    public/aeon/ast/global_namespace.h
    public/aeon/ast/impl/entity_collection_impl.h
    public/aeon/ast/impl/entity_impl.h
    public/aeon/ast/impl/function_collection_impl.h
    public/aeon/ast/method.h
    public/aeon/ast/namespace.h
    public/aeon/ast/source_location.h
    public/aeon/ast/struct.h
    public/aeon/ast/union.h
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

add_library(aeon_ast STATIC
    ${SOURCES}
)

set_target_properties(aeon_ast PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_ast
    PUBLIC
        public
)

target_link_libraries(aeon_ast
    aeon_common
)

install(
    DIRECTORY public/aeon
    DESTINATION include
)

install(
    TARGETS aeon_ast
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

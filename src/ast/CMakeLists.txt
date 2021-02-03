# Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

set(LIB_AEON_AST_PUBLIC_SOURCE
    include/aeon/ast/access_specifier.h
    include/aeon/ast/basic_printer.h
    include/aeon/ast/class.h
    include/aeon/ast/constructor.h
    include/aeon/ast/destructor.h
    include/aeon/ast/entity.h
    include/aeon/ast/entity_collection.h
    include/aeon/ast/entity_type.h
    include/aeon/ast/entity_type_traits.h
    include/aeon/ast/enum.h
    include/aeon/ast/exception.h
    include/aeon/ast/field.h
    include/aeon/ast/function.h
    include/aeon/ast/function_collection.h
    include/aeon/ast/global_namespace.h
    include/aeon/ast/method.h
    include/aeon/ast/namespace.h
    include/aeon/ast/source_location.h
    include/aeon/ast/struct.h
    include/aeon/ast/union.h
)

source_group(public FILES ${LIB_AEON_AST_PUBLIC_SOURCE})

set(LIB_AEON_AST_PUBLIC_IMPL_SOURCE
    include/aeon/ast/impl/entity_collection_impl.h
    include/aeon/ast/impl/entity_impl.h
    include/aeon/ast/impl/function_collection_impl.h
)

source_group(public\\impl FILES ${LIB_AEON_AST_PUBLIC_IMPL_SOURCE})

set(LIB_AEON_AST_PRIVATE_SOURCE
    src/basic_printer.cpp
)

source_group(private FILES ${LIB_AEON_AST_PRIVATE_SOURCE})

add_library(aeon_ast STATIC
    ${LIB_AEON_AST_PUBLIC_SOURCE}
    ${LIB_AEON_AST_PUBLIC_IMPL_SOURCE}
    ${LIB_AEON_AST_PRIVATE_SOURCE}
)

set_target_properties(aeon_ast PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_ast
    PUBLIC
        include
)

target_link_libraries(aeon_ast
    aeon_common
)

install(
    DIRECTORY include/aeon
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

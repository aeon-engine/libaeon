# Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

handle_local_dependencies_file()

set(LIB_AEON_REFLECTION_PUBLIC_SOURCE
    include/aeon/reflection/basic_printer.h
    include/aeon/reflection/reflection.h
    include/aeon/reflection/parser_settings.h
    include/aeon/reflection/exception.h
)

source_group(public FILES ${LIB_AEON_REFLECTION_PUBLIC_SOURCE})

set(LIB_AEON_REFLECTION_PRIVATE_SOURCE
    src/basic_printer.cpp
    src/reflection.cpp
    src/parser_settings.cpp
)

source_group(private FILES ${LIB_AEON_REFLECTION_PRIVATE_SOURCE})

set(LIB_AEON_REFLECTION_PRIVATE_INTERNAL_SOURCE
    src/internal/clang_index.h
    src/internal/clang_string.h
    src/internal/clang_translation_unit.h
    src/internal/clang_visitor.h
    src/internal/entity_visitor.cpp
    src/internal/entity_visitor.h
)

source_group(private\\internal FILES ${LIB_AEON_REFLECTION_PRIVATE_INTERNAL_SOURCE})

set(LIB_AEON_REFLECTION_PUBLIC_AST_SOURCE
    include/aeon/reflection/ast/access_specifier.h
    include/aeon/reflection/ast/constructor.h
    include/aeon/reflection/ast/class.h
    include/aeon/reflection/ast/destructor.h
    include/aeon/reflection/ast/entity.h
    include/aeon/reflection/ast/entity_type.h
    include/aeon/reflection/ast/entity_collection.h
    include/aeon/reflection/ast/enum.h
    include/aeon/reflection/ast/exception.h
    include/aeon/reflection/ast/field.h
    include/aeon/reflection/ast/function.h
    include/aeon/reflection/ast/function_collection.h
    include/aeon/reflection/ast/global_namespace.h
    include/aeon/reflection/ast/method.h
    include/aeon/reflection/ast/namespace.h
    include/aeon/reflection/ast/struct.h
    include/aeon/reflection/ast/union.h
)

source_group(public\\ast FILES ${LIB_AEON_REFLECTION_PUBLIC_AST_SOURCE})

set(LIB_AEON_REFLECTION_PUBLIC_AST_IMPL_SOURCE
    include/aeon/reflection/ast/impl/entity_collection_impl.h
    include/aeon/reflection/ast/impl/entity_impl.h
    include/aeon/reflection/ast/impl/function_collection_impl.h
)

source_group(public\\ast\\impl FILES ${LIB_AEON_REFLECTION_PUBLIC_AST_IMPL_SOURCE})

add_library(aeon_reflection STATIC
    ${LIB_AEON_REFLECTION_PUBLIC_SOURCE}
    ${LIB_AEON_REFLECTION_PRIVATE_SOURCE}
    ${LIB_AEON_REFLECTION_PRIVATE_INTERNAL_SOURCE}
    ${LIB_AEON_REFLECTION_PUBLIC_AST_SOURCE}
    ${LIB_AEON_REFLECTION_PUBLIC_AST_IMPL_SOURCE}
)

set_target_properties(aeon_reflection PROPERTIES
    FOLDER dep/libaeon
    LINKER_LANGUAGE CXX
)

target_include_directories(aeon_reflection
    PUBLIC
        include
)

target_link_libraries(aeon_reflection
    aeon_common
    aeon_streams
    aeon_reflection_support
    Clang::Clang
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

if (AEON_ENABLE_TESTING)
    add_subdirectory(tests)
endif ()

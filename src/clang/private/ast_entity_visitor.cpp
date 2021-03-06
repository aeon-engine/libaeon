// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/clang/visitor.h>
#include <aeon/clang/string.h>
#include <aeon/ast/constructor.h>
#include <aeon/ast/destructor.h>
#include <aeon/ast/namespace.h>
#include <aeon/ast/struct.h>
#include <aeon/ast/class.h>
#include <aeon/ast/enum.h>
#include <aeon/ast/union.h>
#include <aeon/ast/field.h>
#include <aeon/ast/function.h>
#include <aeon/ast/method.h>
#include <aeon/common/assert.h>
#include <memory>

namespace aeon::clang
{

namespace internal
{

auto get_linkage_kind(const CXCursor cursor) noexcept -> ast::linkage_kind
{
    switch (clang_getCursorLinkage(cursor))
    {
        case CXLinkage_Invalid:
            return ast::linkage_kind::invalid;
        case CXLinkage_NoLinkage:
            return ast::linkage_kind::no_linkage;
        case CXLinkage_Internal:
            return ast::linkage_kind::invalid;
        case CXLinkage_UniqueExternal:
            return ast::linkage_kind::unique_external;
        case CXLinkage_External:
            return ast::linkage_kind::external;
        default:
            aeon_assert_fail("Unknown linkage kind");
            return ast::linkage_kind::invalid;
    }
}

auto get_access_specifier(const CXCursor cursor) noexcept -> ast::access_specifier
{
    switch (clang_getCXXAccessSpecifier(cursor))
    {
        case CX_CXXInvalidAccessSpecifier:
            return ast::access_specifier::invalid_t;
        case CX_CXXPublic:
            return ast::access_specifier::public_t;
        case CX_CXXProtected:
            return ast::access_specifier::protected_t;
        case CX_CXXPrivate:
            return ast::access_specifier::private_t;
        default:
            aeon_assert_fail("Unknown access specifier");
            return ast::access_specifier::invalid_t;
    }
}

auto get_exception_specification(const CXCursor cursor) noexcept -> ast::exception_specification
{
    switch (clang_getCursorExceptionSpecificationType(cursor))
    {
        case CXCursor_ExceptionSpecificationKind_None:
            return ast::exception_specification::none;
        case CXCursor_ExceptionSpecificationKind_DynamicNone:
            return ast::exception_specification::dynamic_none;
        case CXCursor_ExceptionSpecificationKind_Dynamic:
            return ast::exception_specification::dynamic;
        case CXCursor_ExceptionSpecificationKind_MSAny:
            return ast::exception_specification::msany;
        case CXCursor_ExceptionSpecificationKind_BasicNoexcept:
            return ast::exception_specification::basic_noexcept;
        case CXCursor_ExceptionSpecificationKind_ComputedNoexcept:
            return ast::exception_specification::computed_noexcept;
        case CXCursor_ExceptionSpecificationKind_Unevaluated:
        case CXCursor_ExceptionSpecificationKind_Uninstantiated:
        case CXCursor_ExceptionSpecificationKind_Unparsed:
        default:
            return ast::exception_specification::unknown;
    }
}

auto get_source_location(const CXCursor cursor)
{
    const auto location = clang_getCursorLocation(cursor);

    CXFile file;
    unsigned int line;
    unsigned int column;
    clang_getFileLocation(location, &file, &line, &column, nullptr);

    return ast::ast_source_location{to_std_string(clang_getFileName(file)), line, column};
}

void parse_function_parameters(ast::ast_function &function, const CXCursor cursor)
{
    clang_visit(cursor, [&function](const CXCursor c, [[maybe_unused]] const CXCursor parent) {
        switch (clang_getCursorKind(c))
        {
            case CXCursor_ParmDecl:
            {
                const auto type = clang_getCursorType(c);
                function.add_parameter(to_std_string(clang_getCursorSpelling(c)),
                                       to_std_string(clang_getTypeSpelling(type)));
            }
            break;
            default:
                break;
        }
    });
}

auto is_forward_declaration(const CXCursor cursor) noexcept -> bool
{
    const auto definition = clang_getCursorDefinition(cursor);

    if (clang_equalCursors(definition, clang_getNullCursor()))
        return true;

    return !clang_equalCursors(cursor, definition);
}

} // namespace internal

void ast_entity_visitor(const CXCursor cursor, ast::ast_entity &ns)
{
    clang_visit(cursor, [&ns](CXCursor c, CXCursor parent) {
        auto source_location = internal::get_source_location(c);

        switch (clang_getCursorKind(c))
        {
            case CXCursor_AnnotateAttr:
            {
                ns.add_annotation(to_std_string(clang_getCursorSpelling(c)));
            }
            break;
            case CXCursor_Namespace:
            {
                if (internal::is_forward_declaration(c))
                    break;

                ast_entity_visitor(c, *ns.emplace_back(std::make_unique<ast::ast_namespace>(
                                          to_std_string(clang_getCursorSpelling(c)), internal::get_linkage_kind(c),
                                          std::move(source_location))));
            }
            break;
            case CXCursor_ClassDecl:
            {
                if (internal::is_forward_declaration(c))
                    break;

                ast_entity_visitor(c, *ns.emplace_back(std::make_unique<ast::ast_class>(
                                          to_std_string(clang_getCursorSpelling(c)), internal::get_linkage_kind(c),
                                          std::move(source_location))));
            }
            break;
            case CXCursor_StructDecl:
            {
                if (internal::is_forward_declaration(c))
                    break;

                ast_entity_visitor(c, *ns.emplace_back(std::make_unique<ast::ast_struct>(
                                          to_std_string(clang_getCursorSpelling(c)), internal::get_linkage_kind(c),
                                          std::move(source_location))));
            }
            break;
            case CXCursor_EnumDecl:
            {
                if (internal::is_forward_declaration(c))
                    break;

                auto &astenum = *ns.emplace_back(
                    std::make_unique<ast::ast_enum>(to_std_string(clang_getCursorSpelling(c)),
                                                    internal::get_linkage_kind(c), std::move(source_location)));

                clang_visit(c, [&astenum](const CXCursor c, [[maybe_unused]] const CXCursor parent) {
                    switch (clang_getCursorKind(c))
                    {
                        case CXCursor_AnnotateAttr:
                        {
                            astenum.add_annotation(to_std_string(clang_getCursorSpelling(c)));
                        }
                        break;
                        case CXCursor_EnumConstantDecl:
                        {
                            astenum.as<ast::ast_enum>().add_constant(to_std_string(clang_getCursorSpelling(c)));
                        }
                        break;
                        default:
                            break;
                    }
                });
            }
            break;
            case CXCursor_UnionDecl:
            {
                if (internal::is_forward_declaration(c))
                    break;

                ast_entity_visitor(c, *ns.emplace_back(std::make_unique<ast::ast_union>(
                                          to_std_string(clang_getCursorSpelling(c)), internal::get_linkage_kind(c),
                                          std::move(source_location))));
            }
            break;
            case CXCursor_VarDecl:
            {
                const auto parent_cursor_kind = clang_getCursorKind(parent);
                if (parent_cursor_kind != CXCursor_ClassDecl && parent_cursor_kind != CXCursor_StructDecl)
                    break;

                ast_entity_visitor(c, *ns.emplace_back(std::make_unique<ast::ast_field>(
                                          to_std_string(clang_getCursorSpelling(c)),
                                          to_std_string(clang_getTypeSpelling(clang_getCursorType(c))),
                                          internal::get_access_specifier(c), ast::field_flag::is_static,
                                          internal::get_linkage_kind(c), std::move(source_location))));
            }
            break;
            case CXCursor_FieldDecl:
            {
                common::flags<ast::field_flag> flags;
                flags.conditional_set(clang_CXXField_isMutable(c), ast::field_flag::is_mutable);

                ast_entity_visitor(c, *ns.emplace_back(std::make_unique<ast::ast_field>(
                                          to_std_string(clang_getCursorSpelling(c)),
                                          to_std_string(clang_getTypeSpelling(clang_getCursorType(c))),
                                          internal::get_access_specifier(c), flags, internal::get_linkage_kind(c),
                                          std::move(source_location))));
            }
            break;
            case CXCursor_Constructor:
            {
                auto &ctor =
                    ns.emplace_back(std::make_unique<ast::ast_constructor>(
                                        to_std_string(clang_getCursorSpelling(c)), internal::get_linkage_kind(c),
                                        internal::get_exception_specification(c), std::move(source_location)))
                        ->as<ast::ast_constructor>();
                internal::parse_function_parameters(ctor, c);
            }
            break;
            case CXCursor_Destructor:
            {
                ns.push_back(std::make_unique<ast::ast_destructor>(to_std_string(clang_getCursorSpelling(c)),
                                                                   internal::get_linkage_kind(c),
                                                                   std::move(source_location)));
            }
            break;
            case CXCursor_CXXMethod:
            {
                common::flags<ast::method_flag> flags;

                flags.conditional_set(clang_CXXMethod_isConst(c), ast::method_flag::is_const);
                flags.conditional_set(clang_CXXMethod_isDefaulted(c), ast::method_flag::is_defaulted);
                flags.conditional_set(clang_CXXMethod_isPureVirtual(c), ast::method_flag::is_pure_virtual);
                flags.conditional_set(clang_CXXMethod_isStatic(c), ast::method_flag::is_static);
                flags.conditional_set(clang_CXXMethod_isVirtual(c), ast::method_flag::is_virtual);

                auto &method =
                    ns
                        .emplace_back(std::make_unique<ast::ast_method>(
                            to_std_string(clang_getCursorSpelling(c)),
                            to_std_string(clang_getTypeSpelling(clang_getResultType(clang_getCursorType(c)))),
                            internal::get_access_specifier(c), flags, internal::get_linkage_kind(c),
                            internal::get_exception_specification(c), std::move(source_location)))
                        ->as<ast::ast_method>();
                internal::parse_function_parameters(method, c);
            }
            break;
            case CXCursor_FunctionDecl:
            {
                auto &function =
                    ns
                        .emplace_back(std::make_unique<ast::ast_function>(
                            to_std_string(clang_getCursorSpelling(c)),
                            to_std_string(clang_getTypeSpelling(clang_getResultType(clang_getCursorType(c)))),
                            internal::get_linkage_kind(c), internal::get_exception_specification(c),
                            std::move(source_location)))
                        ->as<ast::ast_function>();
                internal::parse_function_parameters(function, c);
            }
            break;
            default:
                break;
        }
    });
}

} // namespace aeon::clang

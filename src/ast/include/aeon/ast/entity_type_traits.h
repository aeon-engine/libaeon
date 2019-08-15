// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/ast/entity_type.h>

namespace aeon::ast
{

template <typename T>
struct entity_type_info
{
};

template <>
struct entity_type_info<class global_namespace>
{
    constexpr static auto entity_type = ast_entity_type::global_namespace_t;
};

template <>
struct entity_type_info<class ast_namespace>
{
    constexpr static auto entity_type = ast_entity_type::namespace_t;
};

template <>
struct entity_type_info<class ast_struct>
{
    constexpr static auto entity_type = ast_entity_type::struct_t;
};

template <>
struct entity_type_info<class ast_union>
{
    constexpr static auto entity_type = ast_entity_type::union_t;
};

template <>
struct entity_type_info<class ast_class>
{
    constexpr static auto entity_type = ast_entity_type::class_t;
};

template <>
struct entity_type_info<class ast_enum>
{
    constexpr static auto entity_type = ast_entity_type::enum_t;
};

template <>
struct entity_type_info<class ast_field>
{
    constexpr static auto entity_type = ast_entity_type::field_t;
};

template <>
struct entity_type_info<class ast_method>
{
    constexpr static auto entity_type = ast_entity_type::method_t;
};

template <>
struct entity_type_info<class ast_function>
{
    constexpr static auto entity_type = ast_entity_type::function_t;
};

template <>
struct entity_type_info<class ast_constructor>
{
    constexpr static auto entity_type = ast_entity_type::constructor_t;
};

template <>
struct entity_type_info<class ast_destructor>
{
    constexpr static auto entity_type = ast_entity_type::destructor_t;
};

} // namespace aeon::ast

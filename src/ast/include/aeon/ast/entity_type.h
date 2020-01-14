// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::ast
{

enum class ast_entity_type
{
    global_namespace_t,
    namespace_t,

    struct_t,
    union_t,
    class_t,
    enum_t,

    field_t, // A field (in C) or non-static data member (in C++) in a struct, union, or C++ class.

    method_t,
    function_t,

    constructor_t,
    destructor_t,
};

} // namespace aeon::ast

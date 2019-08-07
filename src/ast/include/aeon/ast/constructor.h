// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/ast/function.h>

namespace aeon::ast
{

class ast_constructor final : public ast_function
{
public:
    explicit ast_constructor(std::string name, const ast::linkage_kind linkage_kind,
                             const ast::exception_specification exception_specification) noexcept
        : ast_function{ast_entity_type::constructor_t, std::move(name), linkage_kind, exception_specification}
    {
    }

    virtual ~ast_constructor() = default;

    ast_constructor(const ast_constructor &) noexcept = delete;
    auto operator=(const ast_constructor &) noexcept -> ast_constructor & = delete;

    ast_constructor(ast_constructor &&) noexcept = default;
    auto operator=(ast_constructor &&) noexcept -> ast_constructor & = default;
};

} // namespace aeon::ast

// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/ast/entity.h>

namespace aeon::ast
{

class ast_namespace : public ast_entity
{
public:
    explicit ast_namespace(std::string name, const ast::linkage_kind linkage_kind) noexcept
        : ast_entity{ast_entity_type::namespace_t, std::move(name), linkage_kind}
    {
    }

    virtual ~ast_namespace() = default;

    ast_namespace(const ast_namespace &) noexcept = delete;
    auto operator=(const ast_namespace &) noexcept -> ast_namespace & = delete;

    ast_namespace(ast_namespace &&) noexcept = default;
    auto operator=(ast_namespace &&) noexcept -> ast_namespace & = default;

protected:
    explicit ast_namespace() noexcept
        : ast_entity{ast_entity_type::global_namespace_t, "", ast::linkage_kind::invalid}
    {
    }
};

} // namespace aeon::ast

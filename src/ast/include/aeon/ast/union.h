// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/ast/entity.h>

namespace aeon::ast
{

class ast_union final : public ast_entity
{
public:
    explicit ast_union(std::string name, const ast::linkage_kind linkage_kind, ast_source_location location) noexcept
        : ast_entity{ast_entity_type::union_t, std::move(name), linkage_kind, std::move(location)}
    {
    }

    virtual ~ast_union() = default;

    ast_union(const ast_union &) noexcept = delete;
    auto operator=(const ast_union &) noexcept -> ast_union & = delete;

    ast_union(ast_union &&) noexcept = default;
    auto operator=(ast_union &&) noexcept -> ast_union & = default;
};

} // namespace aeon::ast

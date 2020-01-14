// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/ast/struct.h>

namespace aeon::ast
{

class ast_class final : public ast_struct
{
public:
    explicit ast_class(std::string name, const ast::linkage_kind linkage_kind, ast_source_location location) noexcept
        : ast_struct{ast_entity_type::class_t, std::move(name), linkage_kind, std::move(location)}
    {
    }

    virtual ~ast_class() = default;

    ast_class(const ast_class &) noexcept = delete;
    auto operator=(const ast_class &) noexcept -> ast_class & = delete;

    ast_class(ast_class &&) noexcept = default;
    auto operator=(ast_class &&) noexcept -> ast_class & = default;
};

} // namespace aeon::ast

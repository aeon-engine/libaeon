// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/struct.h>

namespace aeon::reflection::ast
{

class ast_class final : public ast_struct
{
public:
    explicit ast_class(std::string name, const ast::linkage_kind linkage_kind) noexcept
        : ast_struct{ast_entity_type::class_t, std::move(name), linkage_kind}
    {
    }

    virtual ~ast_class() = default;

    ast_class(const ast_class &) noexcept = delete;
    auto operator=(const ast_class &) noexcept -> ast_class & = delete;

    ast_class(ast_class &&) noexcept = default;
    auto operator=(ast_class &&) noexcept -> ast_class & = default;
};

} // namespace aeon::reflection::ast

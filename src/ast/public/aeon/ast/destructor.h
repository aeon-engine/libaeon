// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ast/entity.h>

namespace aeon::ast
{

class ast_destructor final : public ast_entity
{
public:
    explicit ast_destructor(std::string name, const ast::linkage_kind linkage_kind,
                            ast_source_location location) noexcept
        : ast_entity{ast_entity_type::destructor_t, std::move(name), linkage_kind, std::move(location)}
    {
    }

    virtual ~ast_destructor() = default;

    ast_destructor(const ast_destructor &) noexcept = delete;
    auto operator=(const ast_destructor &) noexcept -> ast_destructor & = delete;

    ast_destructor(ast_destructor &&) noexcept = default;
    auto operator=(ast_destructor &&) noexcept -> ast_destructor & = default;
};

} // namespace aeon::ast

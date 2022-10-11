// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/ast/entity.h>
#include <aeon/common/string.h>

namespace aeon::ast
{

class ast_enum final : public ast_entity
{
public:
    explicit ast_enum(common::string name, const ast::linkage_kind linkage_kind, ast_source_location location) noexcept
        : ast_entity{ast_entity_type::enum_t, std::move(name), linkage_kind, std::move(location)}
    {
    }

    virtual ~ast_enum() = default;

    ast_enum(const ast_enum &) noexcept = delete;
    auto operator=(const ast_enum &) noexcept -> ast_enum & = delete;

    ast_enum(ast_enum &&) noexcept = default;
    auto operator=(ast_enum &&) noexcept -> ast_enum & = default;

    void add_constant(common::string constant)
    {
        constants_.push_back(std::move(constant));
    }

    [[nodiscard]] const auto &constants() const noexcept
    {
        return constants_;
    }

    [[nodiscard]] auto constants_count() const noexcept
    {
        return std::size(constants_);
    }

    [[nodiscard]] auto has_constants() const noexcept
    {
        return !std::empty(constants_);
    }

private:
    std::vector<common::string> constants_;
};

} // namespace aeon::ast

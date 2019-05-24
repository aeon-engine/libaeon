// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/entity_type.h>
#include <aeon/reflection/ast/entity_collection.h>
#include <aeon/reflection/ast/exception.h>
#include <memory>
#include <string>

namespace aeon::reflection::ast
{

enum class linkage_kind
{
    invalid,
    no_linkage,
    internal,
    unique_external,
    external
};

class ast_entity : public ast_entity_collection<std::unique_ptr<ast_entity>>
{
public:
    virtual ~ast_entity() = default;

    ast_entity(const ast_entity &) noexcept = delete;
    auto operator=(const ast_entity &) noexcept -> ast_entity & = delete;

    ast_entity(ast_entity &&) noexcept = default;
    auto operator=(ast_entity &&) noexcept -> ast_entity & = default;

    [[nodiscard]] auto entity_type() const noexcept -> ast_entity_type;

    [[nodiscard]] auto name() const noexcept -> const std::string &;

    template <typename T>
    [[nodiscard]] auto as() -> T &;

    template <typename T>
    [[nodiscard]] auto as() const -> const T &;

    [[nodiscard]] auto linkage_kind() const noexcept -> ast::linkage_kind;

protected:
    explicit ast_entity(const ast_entity_type type, const ast::linkage_kind linkage_kind) noexcept;
    explicit ast_entity(const ast_entity_type type, std::string name, const ast::linkage_kind linkage_kind) noexcept;

    ast_entity_type entity_type_;
    std::string name_;
    ast::linkage_kind linkage_kind_;
};

} // namespace aeon::reflection::ast

#include <aeon/reflection/ast/impl/entity_impl.h>

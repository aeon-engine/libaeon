// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ast/entity.h>
#include <aeon/ast/function_collection.h>
#include <aeon/ast/method.h>
#include <aeon/ast/constructor.h>
#include <aeon/ast/access_specifier.h>
#include <aeon/ast/field.h>
#include <aeon/common/assert.h>

namespace aeon::ast
{

class ast_struct : public ast_entity
{
public:
    explicit ast_struct(std::string name, const ast::linkage_kind linkage_kind, ast_source_location location) noexcept
        : ast_struct{ast_entity_type::struct_t, std::move(name), linkage_kind, std::move(location)}
    {
    }

    ~ast_struct() override = default;

    ast_struct(const ast_struct &) noexcept = delete;
    auto operator=(const ast_struct &) noexcept -> ast_struct & = delete;

    ast_struct(ast_struct &&) noexcept = default;
    auto operator=(ast_struct &&) noexcept -> ast_struct & = default;

    auto constructors() const noexcept -> ast_function_collection<const ast_constructor *>
    {
        std::vector<const ast_constructor *> ctors;
        for (const auto &child : data_)
        {
            if (child->entity_type() != ast_entity_type::constructor_t)
                continue;

            const auto f = dynamic_cast<const ast_constructor *>(child.get());
            aeon_assert(f, "Entity type mismatch.");
            ctors.push_back(f);
        }

        return ast_function_collection{std::move(ctors)};
    }

    auto methods() const noexcept -> ast_function_collection<const ast_method *>
    {
        std::vector<const ast_method *> entities;
        for (const auto &child : data_)
        {
            if (child->entity_type() != ast_entity_type::method_t)
                continue;

            const auto f = dynamic_cast<const ast_method *>(child.get());
            aeon_assert(f, "Entity type mismatch.");
            entities.push_back(f);
        }

        return ast_function_collection{std::move(entities)};
    }

    auto methods(const common::flags<access_specifier> access) const -> ast_function_collection<const ast_method *>
    {
        std::vector<const ast_method *> entities;
        for (const auto &child : data_)
        {
            if (child->entity_type() != ast_entity_type::method_t)
                continue;

            const auto f = dynamic_cast<const ast_method *>(child.get());
            aeon_assert(f, "Entity type mismatch.");

            if (access.is_set(f->access()))
                entities.push_back(f);
        }

        return ast_function_collection{std::move(entities)};
    }

    [[nodiscard]] auto fields() const noexcept -> ast_entity_collection<const ast_field *>
    {
        return children<ast_field>();
    }

    [[nodiscard]] auto fields(const common::flags<access_specifier> access) const noexcept
        -> ast_entity_collection<const ast_field *>
    {
        std::vector<const ast_field *> fields;
        for (const auto &field : children<ast_field>())
        {
            if (access.is_set(field->access()))
                fields.push_back(field);
        }

        return ast_entity_collection<const ast_field *>{std::move(fields)};
    }

protected:
    explicit ast_struct(const ast_entity_type type, std::string name, const ast::linkage_kind linkage_kind,
                        ast_source_location location) noexcept
        : ast_entity{type, std::move(name), linkage_kind, std::move(location)}
    {
    }
};

} // namespace aeon::ast

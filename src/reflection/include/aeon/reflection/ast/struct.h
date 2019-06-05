// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/entity.h>
#include <aeon/reflection/ast/function_collection.h>
#include <aeon/reflection/ast/method.h>
#include <aeon/reflection/ast/constructor.h>
#include <aeon/reflection/ast/access_specifier.h>
#include <aeon/common/assert.h>

namespace aeon::reflection::ast
{

class ast_struct : public ast_entity
{
public:
    explicit ast_struct(std::string name, const ast::linkage_kind linkage_kind) noexcept
        : ast_struct{ast_entity_type::struct_t, std::move(name), linkage_kind}
    {
    }

    virtual ~ast_struct() = default;

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

protected:
    explicit ast_struct(const ast_entity_type type, std::string name, const ast::linkage_kind linkage_kind) noexcept
        : ast_entity{type, std::move(name), linkage_kind}
    {
    }
};

} // namespace aeon::reflection::ast

// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/entity_type.h>
#include <aeon/common/collection.h>

namespace aeon::reflection::ast
{

class ast_entity;

template <typename T>
class ast_entity_collection : public common::collection<T>
{
public:
    ast_entity_collection() noexcept = default;

    explicit ast_entity_collection(std::vector<T> vec) noexcept;

    ~ast_entity_collection() = default;

    ast_entity_collection(const ast_entity_collection &) noexcept = default;
    auto operator=(const ast_entity_collection &) noexcept -> ast_entity_collection & = default;

    ast_entity_collection(ast_entity_collection &&) noexcept = default;
    auto operator=(ast_entity_collection &&) noexcept -> ast_entity_collection & = default;

    template <typename U>
    [[nodiscard]] auto children() const -> ast_entity_collection<const U *>;

    [[nodiscard]] auto children(const ast_entity_type type) const -> ast_entity_collection<const ast_entity *>;

    [[nodiscard]] auto find(const std::string_view name) const noexcept ->
        typename common::collection<T>::const_iterator;

    [[nodiscard]] auto find(const std::string_view name, const ast_entity_type type) const noexcept ->
        typename common::collection<T>::const_iterator;

    [[nodiscard]] auto find_recursive(const std::string_view name) const noexcept -> ast_entity *;

    [[nodiscard]] auto find_recursive(const std::string_view name, const ast_entity_type type) const noexcept
        -> ast_entity *;

    [[nodiscard]] auto contains(const std::string_view name) const noexcept -> bool;

    [[nodiscard]] auto contains(const std::string_view name, const ast_entity_type type) const noexcept -> bool;

    // ReSharper disable once CppHidingFunction
    [[nodiscard]] auto operator[](const std::string_view name) const -> const ast_entity &;

    /*!
     * The visitor must be a struct which contains operator() overloads for all ast types in the form of:
     * void operator()(const ast::ast_entity &entity, const int depth);
     */
    template <typename U>
    void visit(U &&visitor, const bool recursive = false) const;

private:
    template <typename U>
    void visit_internal(U &&visitor, const bool recursive, const int depth) const;
};

} // namespace aeon::reflection::ast

#include <aeon/reflection/ast/impl/entity_collection_impl.h>

// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/entity_collection.h>

namespace aeon::reflection::ast
{

template <typename T>
class ast_function_collection final : public ast_entity_collection<T>
{
public:
    ast_function_collection() noexcept = default;

    explicit ast_function_collection(std::vector<T> vec) noexcept;

    ~ast_function_collection() = default;

    ast_function_collection(const ast_function_collection &) = default;
    auto operator=(const ast_function_collection &) -> ast_function_collection & = default;

    ast_function_collection(ast_function_collection &&) noexcept = default;
    auto operator=(ast_function_collection &&) noexcept -> ast_function_collection & = default;

    [[nodiscard]] auto find(const std::string_view name) const noexcept -> ast_function_collection<T>;

    [[nodiscard]] auto find(const std::string_view name, const unsigned int parameter_count) const noexcept
        -> ast_function_collection<T>;

    [[nodiscard]] auto find(const std::string_view name, const std::vector<std::string_view> &parameter_types) const
        noexcept -> typename common::collection<T>::const_iterator;

    [[nodiscard]] auto find(const unsigned int parameter_count) const noexcept -> ast_function_collection<T>;

    [[nodiscard]] auto find(const std::vector<std::string_view> &parameter_types) const noexcept
        -> ast_function_collection<T>;

    [[nodiscard]] auto contains(const std::string_view name) const noexcept -> bool;

    [[nodiscard]] auto contains(const std::string_view name, const unsigned int parameter_count) const noexcept -> bool;

    [[nodiscard]] auto contains(const std::string_view name, const std::vector<std::string_view> &parameter_types) const
        noexcept -> bool;
};

} // namespace aeon::reflection::ast

#include <aeon/reflection/ast/impl/function_collection_impl.h>

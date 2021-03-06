// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ast/exception.h>
#include <aeon/ast/entity_type_traits.h>
#include <aeon/common/assert.h>
#include <type_traits>
#include <utility>

namespace aeon::ast
{

class ast_namespace;
class ast_struct;
class ast_union;
class ast_class;
class ast_enum;
class ast_field;
class ast_method;
class ast_function;
class ast_constructor;
class ast_destructor;

template <typename T>
inline ast_entity_collection<T>::ast_entity_collection(std::vector<T> vec) noexcept
    : common::collection<T>{std::move(vec)}
{
}

template <typename T>
template <typename U>
inline auto ast_entity_collection<T>::children() const -> ast_entity_collection<const U *>
{
    std::vector<const U *> entities;
    for (const auto &child : common::collection<T>::data_)
    {
        const auto entity = dynamic_cast<const U *>(child.get());

        if (entity)
            entities.push_back(entity);
    }

    return ast_entity_collection<const U *>{std::move(entities)};
}

template <typename T>
inline auto ast_entity_collection<T>::children(const ast_entity_type type) const
    -> ast_entity_collection<const ast_entity *>
{
    std::vector<const ast_entity *> entities;
    for (const auto &child : common::collection<T>::data_)
    {
        if (child->type() == type)
            entities.push_back(child.get());
    }

    return ast_entity_collection{std::move(entities)};
}

template <typename T>
inline auto ast_entity_collection<T>::find(const std::string_view name) const noexcept ->
    typename common::collection<T>::const_iterator
{
    for (auto itr = std::begin(common::collection<T>::data_); itr != std::end(common::collection<T>::data_); ++itr)
    {
        if ((*itr)->name() == name)
            return itr;
    }

    return std::end(common::collection<T>::data_);
}

template <typename T>
auto ast_entity_collection<T>::find(const std::string_view name, const ast_entity_type type) const noexcept ->
    typename common::collection<T>::const_iterator
{
    for (auto itr = std::begin(common::collection<T>::data_); itr != std::end(common::collection<T>::data_); ++itr)
    {
        if ((*itr)->name() == name && (*itr)->entity_type() == type)
            return itr;
    }

    return std::end(common::collection<T>::data_);
}

template <typename T>
auto ast_entity_collection<T>::find_recursive(const std::string_view name) const noexcept -> ast_entity *
{
    for (auto itr = std::begin(common::collection<T>::data_); itr != std::end(common::collection<T>::data_); ++itr)
    {
        if ((*itr)->name() == name)
        {
            if constexpr (std::is_pointer_v<T>)
                return *itr;
            else
                return itr->get();
        }

        const auto recursive_result = (*itr)->find_recursive(name);

        if (recursive_result)
            return recursive_result;
    }

    return nullptr;
}

template <typename T>
auto ast_entity_collection<T>::find_recursive(const std::string_view name, const ast_entity_type type) const noexcept
    -> ast_entity *
{
    for (auto itr = std::begin(common::collection<T>::data_); itr != std::end(common::collection<T>::data_); ++itr)
    {
        if ((*itr)->name() == name && (*itr)->entity_type() == type)
        {
            if constexpr (std::is_pointer_v<T>)
                return *itr;
            else
                return itr->get();
        }

        const auto recursive_result = (*itr)->find_recursive(name, type);

        if (recursive_result)
            return recursive_result;
    }

    return nullptr;
}

template <typename T>
template <typename U>
inline auto ast_entity_collection<T>::find_recursive_typed() const -> std::vector<U *>
{
    std::vector<U *> results;

    for (const auto &child : common::collection<T>::data_)
    {
        if (child->entity_type() == entity_type_info<U>::entity_type)
            results.push_back(reinterpret_cast<U *>(child.get()));

        auto recurse_result = child->template find_recursive_typed<U>();
        results.insert(std::end(results), std::begin(recurse_result), std::end(recurse_result));
    }

    return results;
}

template <typename T>
inline auto ast_entity_collection<T>::contains(const std::string_view name) const noexcept -> bool
{
    for (const auto &child : common::collection<T>::data_)
    {
        if (child->name() == name)
            return true;
    }

    return false;
}

template <typename T>
auto ast_entity_collection<T>::contains(const std::string_view name, const ast_entity_type type) const noexcept -> bool
{
    for (const auto &child : common::collection<T>::data_)
    {
        if (child->name() == name && child->entity_type() == type)
            return true;
    }

    return false;
}

template <typename T>
inline auto ast_entity_collection<T>::operator[](const std::string_view name) const -> const ast_entity &
{
    for (const auto &child : common::collection<T>::data_)
    {
        if (child->name() == name)
            return *child;
    }

    throw ast_exception{};
}

template <typename T>
template <typename U>
inline void ast_entity_collection<T>::visit(U &&visitor, const bool recursive) const
{
    visit_internal(std::forward<U>(visitor), recursive);
}

template <typename T>
template <typename U>
inline void ast_entity_collection<T>::visit_internal(U &&visitor, const bool recursive) const
{
    for (const auto &child : common::collection<T>::data_)
    {
        switch (child->entity_type())
        {
            case ast_entity_type::global_namespace_t:
            case ast_entity_type::namespace_t:
                visitor(child->template as<ast_namespace>());
                break;
            case ast_entity_type::struct_t:
                visitor(child->template as<ast_struct>());
                break;
            case ast_entity_type::union_t:
                visitor(child->template as<ast_union>());
                break;
            case ast_entity_type::class_t:
                visitor(child->template as<ast_class>());
                break;
            case ast_entity_type::enum_t:
                visitor(child->template as<ast_enum>());
                break;
            case ast_entity_type::field_t:
                visitor(child->template as<ast_field>());
                break;
            case ast_entity_type::method_t:
                visitor(child->template as<ast_method>());
                break;
            case ast_entity_type::function_t:
                visitor(child->template as<ast_function>());
                break;
            case ast_entity_type::constructor_t:
                visitor(child->template as<ast_constructor>());
                break;
            case ast_entity_type::destructor_t:
                visitor(child->template as<ast_destructor>());
                break;
            default:
                aeon_assert_fail("Unhandled entity type.");
        }

        if (recursive)
            child->visit_internal(std::forward<U>(visitor), recursive);
    }
}

} // namespace aeon::ast

// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

namespace aeon::ast
{

template <typename T>
inline ast_function_collection<T>::ast_function_collection(std::vector<T> vec) noexcept
    : ast_entity_collection<T>{std::move(vec)}
{
}

template <typename T>
inline auto ast_function_collection<T>::find(const std::string_view name) const noexcept -> ast_function_collection<T>
{
    std::vector<T> entities;
    for (const auto &entity : common::collection<T>::data_)
    {
        if (entity->name() == name)
            entities.push_back(entity);
    }

    return ast_function_collection{std::move(entities)};
}

template <typename T>
inline auto ast_function_collection<T>::find(const std::string_view name, const unsigned int parameter_count) const
    noexcept -> ast_function_collection<T>
{
    std::vector<T> entities;
    for (const auto &entity : common::collection<T>::data_)
    {
        if (entity->name() == name && entity->parameter_count() == parameter_count)
            entities.push_back(entity);
    }

    return ast_function_collection{std::move(entities)};
}

template <typename T>
inline auto ast_function_collection<T>::find(const std::string_view name,
                                             const std::vector<std::string_view> &parameter_types) const noexcept ->
    typename common::collection<T>::const_iterator
{
    const auto parameter_count = std::size(parameter_types);

    for (auto itr = std::begin(common::collection<T>::data_); itr != std::end(common::collection<T>::data_); ++itr)
    {
        if ((*itr)->name() == name && (*itr)->parameter_count() == parameter_count)
        {
            const auto &parameters = (*itr)->parameters();
            if (std::equal(std::begin(parameters), std::end(parameters), std::begin(parameter_types),
                           std::end(parameter_types),
                           [](const auto &lhs, const auto &rhs) { return lhs.type() == rhs; }))
                return itr;
        }
    }

    return std::end(common::collection<T>::data_);
}

template <typename T>
inline auto ast_function_collection<T>::find(const unsigned int parameter_count) const noexcept
    -> ast_function_collection<T>
{
    std::vector<T> entities;
    for (const auto &entity : common::collection<T>::data_)
    {
        if (entity->parameter_count() == parameter_count)
            entities.push_back(entity);
    }

    return ast_function_collection{std::move(entities)};
}

template <typename T>
inline auto ast_function_collection<T>::find(const std::vector<std::string_view> &parameter_types) const noexcept
    -> ast_function_collection<T>
{
    std::vector<T> entities;

    const auto parameter_count = std::size(parameter_types);

    for (auto itr = std::begin(common::collection<T>::data_); itr != std::end(common::collection<T>::data_); ++itr)
    {
        if ((*itr)->parameter_count() == parameter_count)
        {
            const auto &parameters = (*itr)->parameters();
            if (std::equal(std::begin(parameters), std::end(parameters), std::begin(parameter_types),
                           std::end(parameter_types),
                           [](const auto &lhs, const auto &rhs) { return lhs.type() == rhs; }))
                entities.push_back(*itr);
        }
    }

    return ast_function_collection{std::move(entities)};
}

template <typename T>
inline auto ast_function_collection<T>::contains(const std::string_view name) const noexcept -> bool
{
    return ast_entity_collection<T>::contains(name);
}

template <typename T>
inline auto ast_function_collection<T>::contains(const std::string_view name, const unsigned parameter_count) const
    noexcept -> bool
{
    for (const auto &entity : common::collection<T>::data_)
    {
        if (entity->name() == name && entity->parameter_count() == parameter_count)
            return true;
    }

    return false;
}

template <typename T>
inline auto ast_function_collection<T>::contains(const std::string_view name,
                                                 const std::vector<std::string_view> &parameter_types) const noexcept
    -> bool
{
    return find(name, parameter_types) != std::end(common::collection<T>::data_);
}

} // namespace aeon::ast

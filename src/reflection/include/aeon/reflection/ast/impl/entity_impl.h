// Copyright (c) 2012-2019 Robin Degen

#pragma once

namespace aeon::reflection::ast
{

inline auto ast_entity::entity_type() const noexcept -> ast_entity_type
{
    return entity_type_;
}

inline auto ast_entity::name() const noexcept -> const std::string &
{
    return name_;
}

template <typename T>
inline auto ast_entity::as() -> T &
{
    return dynamic_cast<T &>(*this);
}

template <typename T>
inline auto ast_entity::as() const -> const T &
{
    return dynamic_cast<const T &>(*this);
}

inline ast_entity::ast_entity(const ast_entity_type type, const ast::linkage_kind linkage_kind) noexcept
    : ast_entity_collection<std::unique_ptr<ast_entity>>{}
    , entity_type_{type}
    , name_{}
    , linkage_kind_{linkage_kind}
{
}

inline ast_entity::ast_entity(const ast_entity_type type, std::string name,
                              const ast::linkage_kind linkage_kind) noexcept
    : ast_entity_collection<std::unique_ptr<ast_entity>>{}
    , entity_type_{type}
    , name_{std::move(name)}
    , linkage_kind_{linkage_kind}
{
}

inline auto ast_entity::linkage_kind() const noexcept -> ast::linkage_kind
{
    return linkage_kind_;
}

} // namespace aeon::reflection::ast

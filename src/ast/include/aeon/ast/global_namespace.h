// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/ast/namespace.h>

namespace aeon::ast
{

class global_namespace final : public ast_namespace
{
public:
    global_namespace(ast_source_location location) noexcept
        : ast_namespace{std::move(location)}
    {
    }

    virtual ~global_namespace() = default;

    global_namespace(const global_namespace &) noexcept = delete;
    auto operator=(const global_namespace &) noexcept -> global_namespace & = delete;

    global_namespace(global_namespace &&) noexcept = default;
    auto operator=(global_namespace &&) noexcept -> global_namespace & = default;
};

} // namespace aeon::ast

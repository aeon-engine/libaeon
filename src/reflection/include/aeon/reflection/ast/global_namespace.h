// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/reflection/ast/namespace.h>

namespace aeon::reflection::ast
{

class global_namespace final : public ast_namespace
{
public:
    global_namespace() noexcept = default;
    virtual ~global_namespace() = default;

    global_namespace(const global_namespace &) noexcept = delete;
    auto operator=(const global_namespace &) noexcept -> global_namespace & = delete;

    global_namespace(global_namespace &&) noexcept = default;
    auto operator=(global_namespace &&) noexcept -> global_namespace & = default;
};

} // namespace aeon::reflection::ast

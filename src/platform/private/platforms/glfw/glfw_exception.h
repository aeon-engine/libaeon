// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/platform/exception.h>

namespace aeon::platform
{

class glfw_platform_exception final : public platform_exception
{
public:
    explicit glfw_platform_exception(common::string msg) noexcept
        : platform_exception{std::move(msg)}
    {
    }

    ~glfw_platform_exception() = default;

    glfw_platform_exception(const glfw_platform_exception &) = default;
    auto operator=(const glfw_platform_exception &) -> glfw_platform_exception & = default;

    glfw_platform_exception(glfw_platform_exception &&) noexcept = default;
    auto operator=(glfw_platform_exception &&) noexcept -> glfw_platform_exception & = default;
};

} // namespace aeon::platform

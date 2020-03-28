// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <stdexcept>

namespace aeon::vulkan
{

class vulkan_exception : public std::runtime_error
{
public:
    explicit vulkan_exception(const std::string &str)
        : std::runtime_error{str}
    {
    }

    explicit vulkan_exception(const char *const message)
        : std::runtime_error{message}
    {
    }

    ~vulkan_exception() override = default;

    vulkan_exception(const vulkan_exception &) noexcept = default;
    auto operator=(const vulkan_exception &) noexcept -> vulkan_exception & = default;

    vulkan_exception(vulkan_exception &&) noexcept = default;
    auto operator=(vulkan_exception &&) noexcept -> vulkan_exception & = default;
};

} // namespace aeon::vulkan

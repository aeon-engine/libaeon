// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/version.h>
#include <string>

struct VkExtensionProperties;

namespace aeon::vulkan
{

class extension final
{
public:
    explicit extension(std::string name, common::version3<uint32_t> version);
    explicit extension(const VkExtensionProperties &extension_properties);
    ~extension() = default;

    extension(const extension &) = default;
    auto operator=(const extension &) -> extension & = default;

    extension(extension &&) noexcept = default;
    auto operator=(extension &&) noexcept -> extension & = default;

    [[nodiscard]] auto name() const noexcept -> const std::string &;
    [[nodiscard]] auto version() const noexcept -> const common::version3<uint32_t> &;

    auto operator==(const extension &other) const noexcept -> bool;
    auto operator!=(const extension &other) const noexcept -> bool;

private:
    std::string name_;
    common::version3<uint32_t> version_;
};

} // namespace aeon::vulkan

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/extension.h>
#include <aeon/vulkan/version.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

extension::extension(std::string name, common::version3<uint32_t> version)
    : name_{std::move(name)}
    , version_{std::move(version)}
{
}

extension::extension(const VkExtensionProperties &extension_properties)
    : name_{extension_properties.extensionName}
    , version_{version::from_vulkan(extension_properties.specVersion)}
{
}

auto extension::name() const noexcept -> const std::string &
{
    return name_;
}

auto extension::version() const noexcept -> const common::version3<uint32_t> &
{
    return version_;
}

auto extension::operator==(const extension &other) const noexcept -> bool
{
    return name_ == other.name_ && version_ == other.version_;
}

auto extension::operator!=(const extension &other) const noexcept -> bool
{
    return !(*this == other);
}

} // namespace aeon::vulkan

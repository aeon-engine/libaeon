// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/version.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan::version
{

inline auto from_vulkan(const std::uint32_t v) noexcept
{
    return common::version3<uint32_t>{VK_VERSION_MAJOR(v), VK_VERSION_MINOR(v), VK_VERSION_PATCH(v)};
}

inline auto to_vulkan(const common::version3<uint32_t> &v) noexcept
{
    return VK_MAKE_VERSION(v.major, v.minor, v.patch);
}

} // namespace aeon::vulkan::version

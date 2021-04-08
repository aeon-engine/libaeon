// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class sampler_create_info final : public VkSamplerCreateInfo
{
public:
    constexpr explicit sampler_create_info(
        const filter min_filter = filter::linear, const filter mag_filter = filter::linear,
        const common::flags<sampler_create_flag> create_flags = sampler_create_flag::none) noexcept;
    ~sampler_create_info() = default;

    constexpr sampler_create_info(const sampler_create_info &) noexcept = default;
    constexpr auto operator=(const sampler_create_info &) noexcept -> sampler_create_info & = default;

    constexpr sampler_create_info(sampler_create_info &&) noexcept = default;
    constexpr auto operator=(sampler_create_info &&) noexcept -> sampler_create_info & = default;

    constexpr auto address_mode_u(const sampler_address_mode u) noexcept -> sampler_create_info &;
    constexpr auto address_mode_v(const sampler_address_mode v) noexcept -> sampler_create_info &;
    constexpr auto address_mode_w(const sampler_address_mode w) noexcept -> sampler_create_info &;
    constexpr auto address_modes(const sampler_address_mode u, const sampler_address_mode v,
                                 const sampler_address_mode w) noexcept -> sampler_create_info &;

    constexpr auto enable_anisotropy(const float max = 1000.0f) noexcept -> sampler_create_info &;

    constexpr auto enable_unnormalized_coordinates() noexcept -> sampler_create_info &;
};

constexpr sampler_create_info::sampler_create_info(const filter min_filter, const filter mag_filter,
                                                   const common::flags<sampler_create_flag> create_flags) noexcept
    : VkSamplerCreateInfo{VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                          nullptr,
                          static_cast<VkSamplerCreateFlags>(create_flags),
                          static_cast<VkFilter>(mag_filter),
                          static_cast<VkFilter>(min_filter),
                          VK_SAMPLER_MIPMAP_MODE_NEAREST,
                          VK_SAMPLER_ADDRESS_MODE_REPEAT,
                          VK_SAMPLER_ADDRESS_MODE_REPEAT,
                          VK_SAMPLER_ADDRESS_MODE_REPEAT,
                          0.0f,
                          VK_FALSE,
                          0.0f,
                          VK_FALSE,
                          VK_COMPARE_OP_NEVER,
                          0.0f,
                          0.0f,
                          VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
                          VK_FALSE}
{
}

constexpr auto sampler_create_info::address_mode_u(const sampler_address_mode u) noexcept -> sampler_create_info &
{
    VkSamplerCreateInfo::addressModeU = static_cast<VkSamplerAddressMode>(u);
    return *this;
}

constexpr auto sampler_create_info::address_mode_v(const sampler_address_mode v) noexcept -> sampler_create_info &
{
    VkSamplerCreateInfo::addressModeV = static_cast<VkSamplerAddressMode>(v);
    return *this;
}

constexpr auto sampler_create_info::address_mode_w(const sampler_address_mode w) noexcept -> sampler_create_info &
{
    VkSamplerCreateInfo::addressModeW = static_cast<VkSamplerAddressMode>(w);
    return *this;
}

constexpr auto sampler_create_info::address_modes(const sampler_address_mode u, const sampler_address_mode v,
                                                  const sampler_address_mode w) noexcept -> sampler_create_info &
{
    VkSamplerCreateInfo::addressModeU = static_cast<VkSamplerAddressMode>(u);
    VkSamplerCreateInfo::addressModeV = static_cast<VkSamplerAddressMode>(v);
    VkSamplerCreateInfo::addressModeW = static_cast<VkSamplerAddressMode>(w);
    return *this;
}

constexpr auto sampler_create_info::enable_anisotropy(const float max) noexcept -> sampler_create_info &
{
    VkSamplerCreateInfo::anisotropyEnable = true;
    VkSamplerCreateInfo::maxAnisotropy = max;
    return *this;
}

constexpr auto sampler_create_info::enable_unnormalized_coordinates() noexcept -> sampler_create_info &
{
    VkSamplerCreateInfo::unnormalizedCoordinates = VK_TRUE;
    return *this;
}

static_assert(sizeof(sampler_create_info) == sizeof(VkSamplerCreateInfo));

} // namespace aeon::vulkan

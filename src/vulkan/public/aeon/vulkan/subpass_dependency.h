// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

static constexpr auto external_subpass = VK_SUBPASS_EXTERNAL;

class subpass_dependency final : public VkSubpassDependency
{
public:
    constexpr subpass_dependency() noexcept;

    constexpr explicit subpass_dependency(const std::uint32_t source_subpass, const std::uint32_t destination_subpass,
                                          const common::flags<pipeline_stage_flag> source_stage_mask,
                                          const common::flags<pipeline_stage_flag> destination_stage_mask,
                                          const common::flags<access_flag> source_access_mask,
                                          const common::flags<access_flag> destination_access_mask,
                                          const common::flags<dependency_flag> dependency_flags) noexcept;

    constexpr explicit subpass_dependency(const std::uint32_t source_subpass, const std::uint32_t destination_subpass,
                                          const VkPipelineStageFlags source_stage_mask,
                                          const VkPipelineStageFlags destination_stage_mask,
                                          const VkAccessFlags source_access_mask,
                                          const VkAccessFlags destination_access_mask,
                                          const VkDependencyFlags dependency_flags) noexcept;

    ~subpass_dependency() = default;

    constexpr subpass_dependency(const subpass_dependency &) noexcept = default;
    constexpr auto operator=(const subpass_dependency &) noexcept -> subpass_dependency & = default;

    constexpr subpass_dependency(subpass_dependency &&) noexcept = default;
    constexpr auto operator=(subpass_dependency &&) noexcept -> subpass_dependency & = default;

    constexpr auto source_subpass(const std::uint32_t subpass) noexcept -> subpass_dependency &;
    constexpr auto destination_subpass(const std::uint32_t subpass) noexcept -> subpass_dependency &;
    constexpr auto source_stage_mask(const common::flags<pipeline_stage_flag> mask) noexcept -> subpass_dependency &;
    constexpr auto destination_stage_mask(const common::flags<pipeline_stage_flag> mask) noexcept
        -> subpass_dependency &;
    constexpr auto source_access_mask(const common::flags<access_flag> mask) noexcept -> subpass_dependency &;
    constexpr auto destination_access_mask(const common::flags<access_flag> mask) noexcept -> subpass_dependency &;
    constexpr auto dependency_flags(const common::flags<dependency_flag> flags) noexcept -> subpass_dependency &;
};

constexpr subpass_dependency::subpass_dependency() noexcept
    : subpass_dependency{0,
                         0,
                         pipeline_stage_flag::none,
                         pipeline_stage_flag::none,
                         access_flag::none,
                         access_flag::none,
                         dependency_flag::by_region}
{
}

constexpr subpass_dependency::subpass_dependency(
    const std::uint32_t source_subpass, const std::uint32_t destination_subpass,
    const common::flags<pipeline_stage_flag> source_stage_mask,
    const common::flags<pipeline_stage_flag> destination_stage_mask,
    const common::flags<access_flag> source_access_mask, const common::flags<access_flag> destination_access_mask,
    const common::flags<dependency_flag> dependency_flags = dependency_flag::by_region) noexcept
    : subpass_dependency{source_subpass,
                         destination_subpass,
                         static_cast<VkPipelineStageFlags>(source_stage_mask),
                         static_cast<VkPipelineStageFlags>(destination_stage_mask),
                         static_cast<VkAccessFlags>(source_access_mask),
                         static_cast<VkAccessFlags>(destination_access_mask),
                         static_cast<VkDependencyFlags>(dependency_flags)}
{
}

constexpr subpass_dependency::subpass_dependency(const std::uint32_t source_subpass,
                                                 const std::uint32_t destination_subpass,
                                                 const VkPipelineStageFlags source_stage_mask,
                                                 const VkPipelineStageFlags destination_stage_mask,
                                                 const VkAccessFlags source_access_mask,
                                                 const VkAccessFlags destination_access_mask,
                                                 const VkDependencyFlags dependency_flags) noexcept
    : VkSubpassDependency{source_subpass,     destination_subpass,     source_stage_mask, destination_stage_mask,
                          source_access_mask, destination_access_mask, dependency_flags}
{
}

constexpr auto subpass_dependency::source_subpass(const std::uint32_t subpass) noexcept -> subpass_dependency &
{
    srcSubpass = subpass;
    return *this;
}

constexpr auto subpass_dependency::destination_subpass(const std::uint32_t subpass) noexcept -> subpass_dependency &
{
    dstSubpass = subpass;
    return *this;
}

constexpr auto subpass_dependency::source_stage_mask(const common::flags<pipeline_stage_flag> mask) noexcept
    -> subpass_dependency &
{
    srcStageMask = mask;
    return *this;
}

constexpr auto subpass_dependency::destination_stage_mask(const common::flags<pipeline_stage_flag> mask) noexcept
    -> subpass_dependency &
{
    dstStageMask = mask;
    return *this;
}

constexpr auto subpass_dependency::source_access_mask(const common::flags<access_flag> mask) noexcept
    -> subpass_dependency &
{
    srcAccessMask = mask;
    return *this;
}

constexpr auto subpass_dependency::destination_access_mask(const common::flags<access_flag> mask) noexcept
    -> subpass_dependency &
{
    dstAccessMask = mask;
    return *this;
}

constexpr auto subpass_dependency::dependency_flags(const common::flags<dependency_flag> flags) noexcept
    -> subpass_dependency &
{
    dependencyFlags = flags;
    return *this;
}

static_assert(sizeof(subpass_dependency) == sizeof(VkSubpassDependency));

} // namespace aeon::vulkan

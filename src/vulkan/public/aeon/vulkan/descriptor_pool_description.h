// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class descriptor_pool_description final : public VkDescriptorPoolCreateInfo
{
public:
    explicit descriptor_pool_description(
        const common::flags<descriptor_pool_create_flag> flags = descriptor_pool_create_flag::none,
        const std::uint32_t max_sets = 1) noexcept;
    ~descriptor_pool_description() noexcept = default;

    descriptor_pool_description(const descriptor_pool_description &other);
    auto operator=(const descriptor_pool_description &other) -> descriptor_pool_description &;

    descriptor_pool_description(descriptor_pool_description &&) noexcept = default;
    auto operator=(descriptor_pool_description &&) noexcept -> descriptor_pool_description & = default;

    auto flags(const common::flags<descriptor_pool_create_flag> flags) noexcept -> descriptor_pool_description &;
    auto max_sets(const std::uint32_t value) noexcept -> descriptor_pool_description &;

    auto add_pool_size(const descriptor_type type, const std::uint32_t count) -> descriptor_pool_description &;
    auto add_pool_size(const VkDescriptorType type, const std::uint32_t count) -> descriptor_pool_description &;

private:
    std::vector<VkDescriptorPoolSize> pool_sizes_;
};

static_assert(sizeof(descriptor_pool_description) >= sizeof(VkDescriptorPoolCreateInfo));

inline descriptor_pool_description::descriptor_pool_description(const common::flags<descriptor_pool_create_flag> flags,
                                                                const std::uint32_t max_sets) noexcept
    : VkDescriptorPoolCreateInfo{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, nullptr, flags, max_sets, 0, nullptr}
    , pool_sizes_{}
{
}

inline descriptor_pool_description::descriptor_pool_description(const descriptor_pool_description &other)
    : VkDescriptorPoolCreateInfo{other}
    , pool_sizes_{other.pool_sizes_}
{
    if (!std::empty(pool_sizes_))
    {
        VkDescriptorPoolCreateInfo::poolSizeCount = static_cast<std::uint32_t>(std::size(pool_sizes_));
        VkDescriptorPoolCreateInfo::pPoolSizes = std::data(pool_sizes_);
    }
}

inline auto descriptor_pool_description::operator=(const descriptor_pool_description &other)
    -> descriptor_pool_description &
{
    if (this == &other) [[unlikely]]
        return *this;

    VkDescriptorPoolCreateInfo::sType = other.sType;
    VkDescriptorPoolCreateInfo::pNext = other.pNext;
    VkDescriptorPoolCreateInfo::flags = other.VkDescriptorPoolCreateInfo::flags;
    VkDescriptorPoolCreateInfo::maxSets = other.maxSets;

    pool_sizes_ = other.pool_sizes_;

    if (!std::empty(pool_sizes_))
    {
        VkDescriptorPoolCreateInfo::poolSizeCount = static_cast<std::uint32_t>(std::size(pool_sizes_));
        VkDescriptorPoolCreateInfo::pPoolSizes = std::data(pool_sizes_);
    }
    else
    {
        VkDescriptorPoolCreateInfo::poolSizeCount = 0;
        VkDescriptorPoolCreateInfo::pPoolSizes = nullptr;
    }

    return *this;
}

inline auto descriptor_pool_description::flags(const common::flags<descriptor_pool_create_flag> flags) noexcept
    -> descriptor_pool_description &
{
    VkDescriptorPoolCreateInfo::flags = flags;
    return *this;
}

inline auto descriptor_pool_description::max_sets(const std::uint32_t value) noexcept -> descriptor_pool_description &
{
    VkDescriptorPoolCreateInfo::maxSets = value;
    return *this;
}

inline auto descriptor_pool_description::add_pool_size(const descriptor_type type, const std::uint32_t count)
    -> descriptor_pool_description &
{
    return add_pool_size(static_cast<VkDescriptorType>(type), count);
}

inline auto descriptor_pool_description::add_pool_size(const VkDescriptorType type, const std::uint32_t count)
    -> descriptor_pool_description &
{
    pool_sizes_.emplace_back(type, count);

    VkDescriptorPoolCreateInfo::poolSizeCount = static_cast<std::uint32_t>(std::size(pool_sizes_));
    VkDescriptorPoolCreateInfo::pPoolSizes = std::data(pool_sizes_);

    return *this;
}

} // namespace aeon::vulkan

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/descriptor_set.h>
#include <aeon/vulkan/descriptor_pool.h>
#include <aeon/vulkan/descriptor_set_layout_ref.h>
#include <aeon/vulkan/descriptor_buffer_info.h>
#include <aeon/vulkan/descriptor_image_info.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_descriptor_set(const descriptor_pool &pool,
                                         const VkDescriptorSetLayout *descriptor_set_layouts,
                                         const std::size_t descriptor_set_layout_count)
{
    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = vulkan::handle(pool);
    allocInfo.descriptorSetCount = static_cast<std::uint32_t>(descriptor_set_layout_count);
    allocInfo.pSetLayouts = descriptor_set_layouts;

    VkDescriptorSet handle;
    checked_result(vkAllocateDescriptorSets(vulkan::handle(pool.device()), &allocInfo, &handle));
    return handle;
}

[[nodiscard]] auto create_descriptor_set(const descriptor_pool &pool,
                                         const std::vector<VkDescriptorSetLayout> &descriptor_set_layouts)
{
    return create_descriptor_set(pool, std::data(descriptor_set_layouts), std::size(descriptor_set_layouts));
}

[[nodiscard]] auto create_descriptor_set(const descriptor_pool &pool,
                                         const std::vector<descriptor_set_layout_ref> &descriptor_set_layouts)
{
    std::vector<VkDescriptorSetLayout> set_layouts;
    set_layouts.reserve(std::size(descriptor_set_layouts));

    for (const auto &set_layout : descriptor_set_layouts)
    {
        set_layouts.push_back(handle(set_layout));
    }

    return create_descriptor_set(pool, set_layouts);
}

} // namespace internal

descriptor_set::descriptor_set() noexcept
    : pool_{nullptr}
    , handle_{nullptr}
{
}

descriptor_set::descriptor_set(const descriptor_pool &pool, const descriptor_set_layout_ref &descriptor_set_layouts)
    : pool_{&pool}
    , handle_{internal::create_descriptor_set(pool, vulkan::handle_ptr(descriptor_set_layouts), 1)}
{
}

descriptor_set::descriptor_set(const descriptor_pool &pool,
                               const std::vector<descriptor_set_layout_ref> &descriptor_set_layouts)
    : pool_{&pool}
    , handle_{internal::create_descriptor_set(pool, descriptor_set_layouts)}
{
}

descriptor_set::descriptor_set(const descriptor_pool &pool,
                               const std::vector<VkDescriptorSetLayout> &descriptor_set_layouts)
    : pool_{&pool}
    , handle_{internal::create_descriptor_set(pool, descriptor_set_layouts)}
{
}

descriptor_set::~descriptor_set()
{
    destroy();
}

descriptor_set::descriptor_set(descriptor_set &&other) noexcept
    : pool_{other.pool_}
    , handle_{other.handle_}
{
    other.handle_ = nullptr;
}

auto descriptor_set::operator=(descriptor_set &&other) noexcept -> descriptor_set &
{
    if (this != &other) [[likely]]
    {
        destroy();

        pool_ = other.pool_;
        handle_ = other.handle_;

        other.handle_ = nullptr;
    }

    return *this;
}

auto descriptor_set::handle() const noexcept -> VkDescriptorSet
{
    return handle_;
}

auto descriptor_set::handle_ptr() const noexcept -> const VkDescriptorSet *
{
    return &handle_;
}

auto descriptor_set::pool() const noexcept -> const descriptor_pool &
{
    return *pool_;
}

void descriptor_set::update(const descriptor_buffer_info description, const descriptor_type type,
                            const std::uint32_t destination_binding) const
{
    VkWriteDescriptorSet write_descriptor_set{};

    write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_descriptor_set.dstSet = handle_;
    write_descriptor_set.descriptorCount = 1;
    write_descriptor_set.descriptorType = static_cast<VkDescriptorType>(type);
    write_descriptor_set.pBufferInfo = &description;
    write_descriptor_set.dstBinding = destination_binding;

    vkUpdateDescriptorSets(vulkan::handle(pool_->device()), 1, &write_descriptor_set, 0, nullptr);
}

void descriptor_set::update(const descriptor_image_info description, const std::uint32_t destination_binding,
                            const descriptor_type type) const
{
    VkWriteDescriptorSet write_descriptor_set{};

    write_descriptor_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_descriptor_set.dstSet = handle_;
    write_descriptor_set.descriptorCount = 1;
    write_descriptor_set.descriptorType = static_cast<VkDescriptorType>(type);
    write_descriptor_set.pImageInfo = &description;
    write_descriptor_set.dstBinding = destination_binding;

    vkUpdateDescriptorSets(vulkan::handle(pool_->device()), 1, &write_descriptor_set, 0, nullptr);
}

void descriptor_set::destroy() const noexcept
{
    if (handle_)
        vkFreeDescriptorSets(vulkan::handle(pool_->device()), vulkan::handle(pool_), 1, &handle_);
}

} // namespace aeon::vulkan

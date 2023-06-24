// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>
#include <cstdint>
#include <vector>

namespace aeon::vulkan
{

class descriptor_pool;
class descriptor_set_layout_ref;
class descriptor_buffer_info;
class descriptor_image_info;

class descriptor_set
{
public:
    descriptor_set() noexcept;
    explicit descriptor_set(const descriptor_pool &pool, const descriptor_set_layout_ref &descriptor_set_layouts);
    explicit descriptor_set(const descriptor_pool &pool,
                            const std::vector<descriptor_set_layout_ref> &descriptor_set_layouts);
    explicit descriptor_set(const descriptor_pool &pool,
                            const std::vector<VkDescriptorSetLayout> &descriptor_set_layouts);
    ~descriptor_set();

    descriptor_set(const descriptor_set &) noexcept = delete;
    auto operator=(const descriptor_set &) noexcept -> descriptor_set & = delete;

    descriptor_set(descriptor_set &&other) noexcept;
    auto operator=(descriptor_set &&other) noexcept -> descriptor_set &;

    [[nodiscard]] auto handle() const noexcept -> VkDescriptorSet;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkDescriptorSet *;

    [[nodiscard]] auto pool() const noexcept -> const descriptor_pool &;

    void update(const descriptor_buffer_info description, const descriptor_type type,
                const std::uint32_t destination_binding) const;

    void update(const descriptor_image_info description, const std::uint32_t destination_binding,
                const descriptor_type type = descriptor_type::combined_image_sampler) const;

protected:
    void destroy() const noexcept;

    const descriptor_pool *pool_;
    VkDescriptorSet handle_;
};

[[nodiscard]] inline auto handle(const descriptor_set &d) noexcept
{
    return d.handle();
}

[[nodiscard]] inline auto handle_ptr(const descriptor_set &d) noexcept
{
    return d.handle_ptr();
}

} // namespace aeon::vulkan

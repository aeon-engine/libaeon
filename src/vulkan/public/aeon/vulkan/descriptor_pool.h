// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/descriptor_pool_description.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class device;

class descriptor_pool final
{
public:
    descriptor_pool() noexcept;
    explicit descriptor_pool(const vulkan::device &device, const descriptor_pool_description &description);
    ~descriptor_pool() noexcept;

    descriptor_pool(const descriptor_pool &) noexcept = delete;
    auto operator=(const descriptor_pool &) noexcept -> descriptor_pool & = delete;

    descriptor_pool(descriptor_pool &&other) noexcept;
    auto operator=(descriptor_pool &&other) noexcept -> descriptor_pool &;

    [[nodiscard]] auto device() const noexcept -> const device &;

    [[nodiscard]] auto handle() const noexcept -> VkDescriptorPool;

private:
    void destroy() const noexcept;

    const vulkan::device *device_;
    VkDescriptorPool handle_;
};

[[nodiscard]] inline auto handle(const descriptor_pool &img) noexcept
{
    return img.handle();
}

[[nodiscard]] inline auto handle(const descriptor_pool *img) noexcept
{
    return img->handle();
}

} // namespace aeon::vulkan

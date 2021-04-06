// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/queue_indices.h>
#include <aeon/vulkan/queue.h>
#include <aeon/vulkan/vma/vma.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>

namespace aeon::vulkan
{

class surface;
class physical_device;

class device final
{
public:
    device() noexcept;
    explicit device(const vulkan::physical_device &d, const surface &surface, const std::vector<std::string> &layers,
                    const std::vector<std::string> &extensions, const VkPhysicalDeviceFeatures &features);

    ~device();

    device(const device &) noexcept = delete;
    auto operator=(const device &) noexcept -> device & = delete;

    device(device &&other) noexcept;
    auto operator=(device &&other) noexcept -> device &;

    [[nodiscard]] auto handle() const noexcept -> VkDevice;
    [[nodiscard]] auto physical_device() const noexcept -> const physical_device &;

    [[nodiscard]] auto get_queue_indices() const noexcept -> const queue_indices &;

    [[nodiscard]] auto graphics_queue() const noexcept -> const queue &;
    [[nodiscard]] auto present_queue() const noexcept -> const queue &;
    [[nodiscard]] auto transfer_queue() const noexcept -> const queue &;

    [[nodiscard]] auto allocator_handle() const noexcept -> VmaAllocator;

    void wait_idle() const;

private:
    void destroy() const noexcept;

    const vulkan::physical_device *physical_device_;
    queue_indices queue_indices_;
    VkDevice device_;
    VmaAllocator allocator_;
    queue graphics_queue_;
    queue present_queue_;
    queue transfer_queue_;
};

[[nodiscard]] inline auto device::graphics_queue() const noexcept -> const queue &
{
    return graphics_queue_;
}

[[nodiscard]] inline auto device::present_queue() const noexcept -> const queue &
{
    return present_queue_;
}

[[nodiscard]] inline auto device::transfer_queue() const noexcept -> const queue &
{
    return transfer_queue_;
}

[[nodiscard]] inline auto handle(const device &d) noexcept
{
    return d.handle();
}

[[nodiscard]] inline auto handle(const device *d) noexcept
{
    return handle(*d);
}

} // namespace aeon::vulkan

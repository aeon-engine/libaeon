// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/device_memory.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

device_memory::device_memory() noexcept
    : allocation_{nullptr}
    , device_{nullptr}
    , size_{}

{
}

device_memory::device_memory(const vulkan::device &dev) noexcept
    : device_memory{dev, 0}
{
}

device_memory::device_memory(const vulkan::device &dev, const VkDeviceSize size) noexcept
    : allocation_{nullptr}
    , device_{&dev}
    , size_{size}
{
}

auto device_memory::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto device_memory::size() const noexcept -> VkDeviceSize
{
    return size_;
}

auto device_memory::scope_map() const -> scoped_memory_map
{
    return scoped_memory_map{*this};
}

void device_memory::map(void **data) const
{
    checked_result{vmaMapMemory(device_->allocator_handle(), allocation_, data)};
}

void device_memory::unmap() const
{
    vmaUnmapMemory(device_->allocator_handle(), allocation_);
}

} // namespace aeon::vulkan

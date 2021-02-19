// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/device_memory.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/physical_device.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto allocate_memory(const VkDevice device, const VkDeviceSize size, const std::uint32_t type_index)
{
    const auto alloc_info = initializers::memory_allocate_info(size, type_index);
    VkDeviceMemory handle = nullptr;
    checked_result{vkAllocateMemory(device, &alloc_info, nullptr, &handle)};
    return handle;
}

} // namespace internal

device_memory::device_memory() noexcept
    : device_{nullptr}
    , type_index_{}
    , size_{}
    , handle_{nullptr}
{
}

device_memory::device_memory(const device &dev, const VkMemoryRequirements &requirements,
                             const common::flags<memory_flag> flags)
    : device_memory{dev, requirements.size, requirements.memoryTypeBits, flags}
{
}

device_memory::device_memory(const device &dev, const VkDeviceSize size, const std::uint32_t required_memory_type_bits,
                             const common::flags<memory_flag> flags)
    : device_memory{dev, size,
                    static_cast<std::uint32_t>(find_memory_type_index(dev.physical_device().memory_properties(),
                                                                      required_memory_type_bits, flags))}
{
}

device_memory::device_memory(const device &dev, const VkDeviceSize size, const std::uint32_t type_index)
    : device_{vulkan::handle(dev)}
    , type_index_{type_index}
    , size_{size}
    , handle_{internal::allocate_memory(device_, size_, type_index_)}
{
}

device_memory::~device_memory() noexcept
{
    if (handle_)
        vkFreeMemory(device_, handle_, nullptr);
}

device_memory::device_memory(device_memory &&other) noexcept
    : device_{other.device_}
    , type_index_{other.type_index_}
    , size_{other.size_}
    , handle_{other.handle_}
{
    other.handle_ = nullptr;
}

auto device_memory::operator=(device_memory &&other) noexcept -> device_memory &
{
    device_ = other.device_;
    type_index_ = other.type_index_;
    size_ = other.size_;
    handle_ = other.handle_;
    other.handle_ = nullptr;
    return *this;
}

auto device_memory::handle() const noexcept -> VkDeviceMemory
{
    return handle_;
}

auto device_memory::size() const noexcept -> VkDeviceSize
{
    return size_;
}

auto device_memory::type_index() const noexcept -> std::uint32_t
{
    return type_index_;
}

auto device_memory::scope_map(const VkDeviceSize offset) const -> scoped_memory_map
{
    return scope_map(offset, size_);
}

auto device_memory::scope_map(const VkDeviceSize offset, const VkDeviceSize size) const -> scoped_memory_map
{
    return scoped_memory_map{*this, offset, size};
}

void device_memory::map(const VkDeviceSize offset, const VkDeviceSize size, void **data) const
{
    checked_result{vkMapMemory(device_, handle_, offset, size, 0, data)};
}

void device_memory::unmap() const
{
    vkUnmapMemory(device_, handle_);
}

} // namespace aeon::vulkan

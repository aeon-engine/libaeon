// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/buffer.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/command_buffer.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_buffer(VmaAllocation &out_allocation, const vulkan::device &device, const std::size_t size,
                                 const common::flags<buffer_usage_flag> usage_flags,
                                 const memory_allocation_usage allocation_usage) -> VkBuffer
{
    VkBufferCreateInfo create_info{};
    create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    create_info.size = size;
    create_info.usage = static_cast<VkBufferUsageFlags>(usage_flags);

    VmaAllocationCreateInfo alloc_info{};
    alloc_info.usage = static_cast<VmaMemoryUsage>(allocation_usage);

    VkBuffer buffer;
    vmaCreateBuffer(device.allocator_handle(), &create_info, &alloc_info, &buffer, &out_allocation, nullptr);
    return buffer;
}

} // namespace internal

buffer::buffer() noexcept
    : device_memory{}
    , handle_{VK_NULL_HANDLE}
{
}

buffer::buffer(const vulkan::device &device, const std::size_t size, const common::flags<buffer_usage_flag> usage_flags,
               const memory_allocation_usage allocation_usage)
    : device_memory{device, size}
    , handle_{internal::create_buffer(allocation_, device, size, usage_flags, allocation_usage)}
{
}

buffer::~buffer() noexcept
{
    destroy();
}

buffer::buffer(buffer &&other) noexcept
    : device_memory{std::move(other)}
    , handle_{other.handle_}
{
    other.handle_ = VK_NULL_HANDLE;
    other.allocation_ = nullptr;
}

auto buffer::operator=(buffer &&other) noexcept -> buffer &
{
    if (this != &other) [[likely]]
    {
        destroy();

        allocation_ = other.allocation_;
        device_ = other.device_;
        size_ = other.size_;
        handle_ = other.handle_;

        other.handle_ = VK_NULL_HANDLE;
        other.allocation_ = nullptr;
    }

    return *this;
}

auto buffer::handle() const noexcept -> VkBuffer
{
    return handle_;
}

auto buffer::handle_ptr() const noexcept -> const VkBuffer *
{
    return &handle_;
}

void buffer::destroy() const noexcept
{
    if (handle_ && allocation_)
        vmaDestroyBuffer(device_->allocator_handle(), handle_, allocation_);
}

} // namespace aeon::vulkan

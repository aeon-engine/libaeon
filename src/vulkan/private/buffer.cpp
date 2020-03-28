// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/buffer.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/command_buffer.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_buffer(const VkDevice device, const std::size_t size,
                                 const common::flags<buffer_usage_flag> usage_flags) -> VkBuffer
{
    const auto create_info = initializers::buffer_create_info(size, usage_flags, buffer_sharing_mode::exclusive, {});

    VkBuffer handle = nullptr;
    checked_result{vkCreateBuffer(device, &create_info, nullptr, &handle)};
    return handle;
}

[[nodiscard]] auto get_buffer_memory_requirements(const VkDevice device, const VkBuffer buffer) noexcept
{
    VkMemoryRequirements requirements{};
    vkGetBufferMemoryRequirements(device, buffer, &requirements);
    return requirements;
}

} // namespace internal

buffer::buffer() noexcept
    : size_{0}
    , device_{nullptr}
    , handle_{nullptr}
    , requirements_{}
{
}

buffer::buffer(const vulkan::device &device, const std::size_t size, const common::flags<buffer_usage_flag> usage_flags)
    : size_{size}
    , device_{&device}
    , handle_{internal::create_buffer(vulkan::handle(device), size_, usage_flags)}
    , requirements_{internal::get_buffer_memory_requirements(vulkan::handle(device), handle_)}
{
}

buffer::~buffer() noexcept
{
    destroy();
}

buffer::buffer(buffer &&other) noexcept
    : size_{other.size_}
    , device_{other.device_}
    , handle_{other.handle_}
    , requirements_{other.requirements_}
{
    other.handle_ = nullptr;
}

auto buffer::operator=(buffer &&other) noexcept -> buffer &
{
    if (this != &other) [[likely]]
    {
        destroy();

        size_ = other.size_;
        device_ = other.device_;
        handle_ = other.handle_;
        requirements_ = other.requirements_;

        other.handle_ = nullptr;
    }

    return *this;
}

auto buffer::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto buffer::size() const noexcept -> std::size_t
{
    return size_;
}

auto buffer::handle() const noexcept -> VkBuffer
{
    return handle_;
}

auto buffer::handle_ptr() const noexcept -> const VkBuffer *
{
    return &handle_;
}

auto buffer::memory_requirements() const noexcept -> VkMemoryRequirements
{
    return requirements_;
}

auto buffer::required_size() const noexcept -> std::size_t
{
    return requirements_.size;
}

auto buffer::required_alignment() const noexcept -> std::size_t
{
    return requirements_.alignment;
}

auto buffer::required_memory_type_bits() const noexcept -> std::uint32_t
{
    return requirements_.memoryTypeBits;
}

void buffer::bind_memory(const device_memory &memory, const VkDeviceSize offset) const
{
    checked_result{vkBindBufferMemory(vulkan::handle(device_), handle_, vulkan::handle(memory), offset)};
}

void buffer::destroy() const noexcept
{
    if (handle_)
        vkDestroyBuffer(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan

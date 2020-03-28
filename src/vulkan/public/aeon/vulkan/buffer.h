// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/device_memory.h>
#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>
#include <cstddef>

namespace aeon::vulkan
{

class command_buffer;
class device;

class buffer final
{
public:
    buffer() noexcept;
    explicit buffer(const vulkan::device &device, const std::size_t size,
                    const common::flags<buffer_usage_flag> usage_flags);
    ~buffer() noexcept;

    buffer(const buffer &) noexcept = delete;
    auto operator=(const buffer &) noexcept -> buffer & = delete;

    buffer(buffer &&other) noexcept;
    auto operator=(buffer &&other) noexcept -> buffer &;

    [[nodiscard]] auto device() const noexcept -> const device &;

    [[nodiscard]] auto size() const noexcept -> std::size_t;
    [[nodiscard]] auto handle() const noexcept -> VkBuffer;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkBuffer *;

    [[nodiscard]] auto memory_requirements() const noexcept -> VkMemoryRequirements;
    [[nodiscard]] auto required_size() const noexcept -> std::size_t;
    [[nodiscard]] auto required_alignment() const noexcept -> std::size_t;
    [[nodiscard]] auto required_memory_type_bits() const noexcept -> std::uint32_t;

    void bind_memory(const device_memory &memory, const VkDeviceSize offset = 0) const;

private:
    void destroy() const noexcept;

    std::size_t size_;
    const vulkan::device *device_;
    VkBuffer handle_;
    VkMemoryRequirements requirements_;
};

[[nodiscard]] inline auto handle(const buffer &buffer) noexcept
{
    return buffer.handle();
}

[[nodiscard]] inline auto handle_ptr(const buffer &buffer) noexcept
{
    return buffer.handle_ptr();
}

/*!
 * Create staging memory that would be suitable for this buffer. This does not bind the memory to the buffer.
 */
[[nodiscard]] inline auto make_staging_memory(const device &dev, const buffer &buffer) -> device_memory
{
    return device_memory{dev, buffer.memory_requirements(),
                         vulkan::memory_flag::host_visible | vulkan::memory_flag::host_coherent};
}

} // namespace aeon::vulkan

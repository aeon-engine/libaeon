// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/device_memory.h>
#include <vulkan/vulkan_core.h>
#include <cstddef>

namespace aeon::vulkan
{

class command_buffer;
class device;

class buffer final : public device_memory
{
public:
    buffer() noexcept;
    explicit buffer(const vulkan::device &device, const std::size_t size,
                    const common::flags<buffer_usage_flag> usage_flags, const memory_allocation_usage allocation_usage);
    ~buffer() noexcept;

    buffer(const buffer &) noexcept = delete;
    auto operator=(const buffer &) noexcept -> buffer & = delete;

    buffer(buffer &&other) noexcept;
    auto operator=(buffer &&other) noexcept -> buffer &;

    [[nodiscard]] auto handle() const noexcept -> VkBuffer;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkBuffer *;

private:
    void destroy() const noexcept;

    VkBuffer handle_;
};

[[nodiscard]] inline auto handle(const buffer &buffer) noexcept
{
    return buffer.handle();
}

[[nodiscard]] inline auto handle_ptr(const buffer &buffer) noexcept
{
    return buffer.handle_ptr();
}

} // namespace aeon::vulkan

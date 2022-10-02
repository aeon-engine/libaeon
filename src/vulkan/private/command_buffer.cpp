// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/command_buffer.h>
#include <aeon/vulkan/command_pool.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/buffer.h>
#include <aeon/vulkan/fence.h>
#include <aeon/vulkan/queue.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/initializers.h>
#include <chrono>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_command_buffer(const command_pool &command_pool, const command_buffer_level level)
{
    const auto info = initializers::command_buffer_create_info(handle(command_pool), level);

    VkCommandBuffer buffer;
    checked_result{vkAllocateCommandBuffers(handle(command_pool.device()), &info, &buffer)};
    return buffer;
}

} // namespace internal

command_buffer::command_buffer() noexcept
    : command_buffer_ref{}
{
}

command_buffer::command_buffer(const vulkan::command_pool &command_pool, const VkCommandBuffer buffer,
                               const command_buffer_auto_begin auto_begin)
    : command_buffer_ref{command_pool, buffer}
{
    if (auto_begin == command_buffer_auto_begin::enabled)
        begin();
}

command_buffer::command_buffer(const vulkan::command_pool &command_pool, const command_buffer_auto_begin auto_begin,
                               const command_buffer_level level)
    : command_buffer_ref{command_pool, internal::create_command_buffer(command_pool, level)}
{
    if (auto_begin == command_buffer_auto_begin::enabled)
        begin();
}

command_buffer::~command_buffer()
{
    destroy();
}

command_buffer::command_buffer(command_buffer &&other) noexcept
    : command_buffer_ref{other}
{
    other.buffer_ = nullptr;
}

auto command_buffer::operator=(command_buffer &&other) noexcept -> command_buffer &
{
    if (this != &other) [[likely]]
    {
        destroy();

        pool_ = other.pool_;
        buffer_ = other.buffer_;
        other.buffer_ = nullptr;
    }

    return *this;
}

} // namespace aeon::vulkan

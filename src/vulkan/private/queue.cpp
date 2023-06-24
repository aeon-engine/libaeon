// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/queue.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/semaphore_ref.h>
#include <aeon/vulkan/fence_ref.h>
#include <aeon/vulkan/command_buffer.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto get_device_queue(const VkDevice device, const std::uint32_t index)
{
    VkQueue queue_handle;
    vkGetDeviceQueue(device, index, 0, &queue_handle);
    return queue_handle;
}

} // namespace internal

queue::queue() noexcept
    : queue_{nullptr}
    , index_{0}
{
}

queue::queue(const device &dev, const std::uint32_t index) noexcept
    : queue{vulkan::handle(dev), index}
{
}

queue::queue(const VkDevice device, const std::uint32_t index) noexcept
    : queue{internal::get_device_queue(device, index), index}
{
}

queue::queue(const VkQueue queue, const std::uint32_t index) noexcept
    : queue_{queue}
    , index_{index}
{
}

auto queue::handle() const noexcept -> VkQueue
{
    return queue_;
}

auto queue::index() const noexcept -> std::uint32_t
{
    return index_;
}

void queue::submit(const VkCommandBuffer command_buffer) const
{
    const VkPipelineStageFlags flags = 0;
    const auto submit_info = initializers::submit_info(&command_buffer, flags);
    checked_result{vkQueueSubmit(queue_, 1, &submit_info, VK_NULL_HANDLE)};
}

void queue::submit(const command_buffer &command_buffer) const
{
    submit(vulkan::handle(command_buffer));
}

void queue::submit(const VkCommandBuffer command_buffer, const fence_ref &fence) const
{
    const VkPipelineStageFlags flags = 0;
    const auto submit_info = initializers::submit_info(&command_buffer, flags);
    checked_result{vkQueueSubmit(queue_, 1, &submit_info, vulkan::handle(fence))};
}

void queue::submit(const command_buffer &command_buffer, const fence_ref &fence) const
{
    submit(vulkan::handle(command_buffer), fence);
}

void queue::submit(const VkCommandBuffer command_buffer, const semaphore_ref &wait, const semaphore_ref &signal) const
{
    const VkPipelineStageFlags flags = 0;
    const auto wait_semaphore_handle = vulkan::handle(wait);
    const auto signal_semaphore_handle = vulkan::handle(signal);
    const auto submit_info =
        initializers::submit_info(&wait_semaphore_handle, &command_buffer, &signal_semaphore_handle, flags);

    checked_result{vkQueueSubmit(queue_, 1, &submit_info, VK_NULL_HANDLE)};
}

void queue::submit(const command_buffer &command_buffer, const semaphore_ref &wait, const semaphore_ref &signal) const
{
    submit(vulkan::handle(command_buffer), wait, signal);
}

void queue::submit(const VkCommandBuffer command_buffer, const semaphore_ref &wait,
                   const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal) const
{
    const auto wait_semaphore_handle = vulkan::handle(wait);
    const auto signal_semaphore_handle = vulkan::handle(signal);
    const auto submit_info =
        initializers::submit_info(&wait_semaphore_handle, &command_buffer, &signal_semaphore_handle, wait_stage);
    checked_result{vkQueueSubmit(queue_, 1, &submit_info, VK_NULL_HANDLE)};
}

void queue::submit(const command_buffer &command_buffer, const semaphore_ref &wait,
                   const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal) const
{
    submit(vulkan::handle(command_buffer), wait, wait_stage, signal);
}

void queue::submit(const VkCommandBuffer command_buffer, const semaphore_ref &wait,
                   const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal,
                   const fence_ref &fence) const
{
    const auto wait_semaphore_handle = vulkan::handle(wait);
    const auto signal_semaphore_handle = vulkan::handle(signal);
    const auto submit_info =
        initializers::submit_info(&wait_semaphore_handle, &command_buffer, &signal_semaphore_handle, wait_stage);
    checked_result{vkQueueSubmit(queue_, 1, &submit_info, vulkan::handle(fence))};
}

void queue::submit(const command_buffer &command_buffer, const semaphore_ref &wait,
                   const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal,
                   const fence_ref &fence) const
{
    submit(vulkan::handle(command_buffer), wait, wait_stage, signal, fence);
}

void queue::wait_idle() const
{
    checked_result{vkQueueWaitIdle(queue_)};
}

} // namespace aeon::vulkan

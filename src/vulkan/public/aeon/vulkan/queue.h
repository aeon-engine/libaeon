// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>
#include <cstdint>

namespace aeon::vulkan
{

class device;
class fence_ref;
class semaphore_ref;
class command_buffer;

class queue
{
public:
    queue() noexcept;
    explicit queue(const device &dev, const std::uint32_t index) noexcept;
    explicit queue(const VkDevice device, const std::uint32_t index) noexcept;
    explicit queue(const VkQueue queue, const std::uint32_t index) noexcept;
    ~queue() noexcept = default;

    queue(const queue &) noexcept = default;
    auto operator=(const queue &) noexcept -> queue & = default;

    queue(queue &&other) noexcept = default;
    auto operator=(queue &&other) noexcept -> queue & = default;

    [[nodiscard]] auto handle() const noexcept -> VkQueue;
    [[nodiscard]] auto index() const noexcept -> std::uint32_t;

    void submit(const VkCommandBuffer command_buffer) const;

    void submit(const command_buffer &command_buffer) const;

    void submit(const VkCommandBuffer command_buffer, const fence_ref &fence) const;

    void submit(const command_buffer &command_buffer, const fence_ref &fence) const;

    void submit(const VkCommandBuffer command_buffer, const semaphore_ref &wait, const semaphore_ref &signal) const;

    void submit(const command_buffer &command_buffer, const semaphore_ref &wait, const semaphore_ref &signal) const;

    void submit(const VkCommandBuffer command_buffer, const semaphore_ref &wait,
                const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal) const;

    void submit(const command_buffer &command_buffer, const semaphore_ref &wait,
                const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal) const;

    void submit(const VkCommandBuffer command_buffer, const semaphore_ref &wait,
                const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal,
                const fence_ref &fence) const;

    void submit(const command_buffer &command_buffer, const semaphore_ref &wait,
                const common::flags<pipeline_stage_flag> wait_stage, const semaphore_ref &signal,
                const fence_ref &fence) const;

    void wait_idle() const;

    /*void present(SwapChain& swap_chain,
                    std::uint32_t indices,
                    Semaphore& wait);

    void present(SwapChain& swap_chain,
                    std::uint32_t indices);*/

private:
    VkQueue queue_;
    std::uint32_t index_;
};

[[nodiscard]] inline auto handle(const queue &q) noexcept
{
    return q.handle();
}

} // namespace aeon::vulkan

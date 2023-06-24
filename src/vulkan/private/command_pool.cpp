// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/vulkan/command_pool.h>
#include <aeon/vulkan/command_buffer.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_command_pool(const device &device, const std::uint32_t queue_family_index,
                                       const common::flags<command_pool_create_flag> create_flags)
{
    const auto info = initializers::command_pool_create_info(queue_family_index, create_flags);

    VkCommandPool pool;
    checked_result{vkCreateCommandPool(handle(device), &info, nullptr, &pool)};
    return pool;
}

} // namespace internal

command_pool::command_pool() noexcept
    : device_{nullptr}
    , pool_{VK_NULL_HANDLE}
{
}

command_pool::command_pool(const vulkan::device &device, const common::flags<command_pool_create_flag> create_flags)
    : command_pool{device, device.get_queue_indices().graphics_queue_index(), create_flags}
{
}

command_pool::command_pool(const vulkan::device &device, const std::uint32_t queue_family_index,
                           const common::flags<command_pool_create_flag> create_flags)
    : device_{&device}
    , pool_{internal::create_command_pool(device, queue_family_index, create_flags)}

{
}

command_pool::~command_pool()
{
    destroy();
}

command_pool::command_pool(command_pool &&other) noexcept
    : device_{other.device_}
    , pool_{other.pool_}
{
    other.device_ = nullptr;
    other.pool_ = VK_NULL_HANDLE;
}

auto command_pool::operator=(command_pool &&other) noexcept -> command_pool &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        pool_ = other.pool_;
        other.device_ = nullptr;
        other.pool_ = VK_NULL_HANDLE;
    }

    return *this;
}

auto command_pool::handle() const noexcept -> VkCommandPool
{
    return pool_;
}

auto command_pool::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto command_pool::create_command_buffer(const command_buffer_auto_begin auto_begin,
                                         const command_buffer_level level) const noexcept -> command_buffer
{
    return command_buffer{*this, auto_begin, level};
}

auto command_pool::create_command_buffers(const std::uint32_t count, const command_buffer_auto_begin auto_begin,
                                          const command_buffer_level level) const -> std::vector<command_buffer>
{
    const auto info = initializers::command_buffer_create_info(pool_, level, count);

    std::vector<VkCommandBuffer> buffers(count);
    checked_result{vkAllocateCommandBuffers(vulkan::handle(device_), &info, std::data(buffers))};

    std::vector<command_buffer> result;
    result.reserve(count);

    for (auto *const buffer : buffers)
    {
        result.emplace_back(*this, buffer, auto_begin);
    }

    return result;
}

void command_pool::destroy() const noexcept
{
    if (pool_)
        vkDestroyCommandPool(vulkan::handle(device_), pool_, nullptr);
}

} // namespace aeon::vulkan

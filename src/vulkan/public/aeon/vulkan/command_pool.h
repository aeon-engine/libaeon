// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class command_buffer;
class device;

class command_pool final
{
public:
    command_pool() noexcept;
    /*!
     * Create a command pool on the graphics queue family index
     */
    explicit command_pool(const vulkan::device &device,
                          const common::flags<command_pool_create_flag> create_flags = {});

    explicit command_pool(const vulkan::device &device, const std::uint32_t queue_family_index,
                          const common::flags<command_pool_create_flag> create_flags = {});
    ~command_pool();

    command_pool(const command_pool &) noexcept = delete;
    auto operator=(const command_pool &) noexcept -> command_pool & = delete;

    command_pool(command_pool &&other) noexcept;
    auto operator=(command_pool &&other) noexcept -> command_pool &;

    [[nodiscard]] auto handle() const noexcept -> VkCommandPool;

    [[nodiscard]] auto device() const noexcept -> const device &;

    [[nodiscard]] auto
        create_command_buffer(const command_buffer_auto_begin auto_begin = command_buffer_auto_begin::disabled,
                              const command_buffer_level level = command_buffer_level::primary) const noexcept
        -> command_buffer;

    [[nodiscard]] auto create_command_buffers(
        const std::uint32_t count, const command_buffer_auto_begin auto_begin = command_buffer_auto_begin::disabled,
        const command_buffer_level level = command_buffer_level::primary) const -> std::vector<command_buffer>;

private:
    void destroy() const noexcept;

    const vulkan::device *device_;
    VkCommandPool pool_;
};

[[nodiscard]] inline auto handle(const command_pool &p) noexcept
{
    return p.handle();
}

[[nodiscard]] inline auto handle(const command_pool *p) noexcept
{
    return handle(*p);
}

} // namespace aeon::vulkan

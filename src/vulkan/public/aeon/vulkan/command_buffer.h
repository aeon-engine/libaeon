// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/command_buffer_ref.h>
#include <aeon/vulkan/enums.h>

namespace aeon::vulkan
{

class command_buffer final : public command_buffer_ref
{
public:
    command_buffer() noexcept;
    explicit command_buffer(const vulkan::command_pool &command_pool, const VkCommandBuffer buffer,
                            const command_buffer_auto_begin auto_begin = command_buffer_auto_begin::disabled);
    explicit command_buffer(const vulkan::command_pool &command_pool,
                            const command_buffer_auto_begin auto_begin = command_buffer_auto_begin::disabled,
                            const command_buffer_level level = command_buffer_level::primary);
    ~command_buffer();

    command_buffer(const command_buffer &) noexcept = delete;
    auto operator=(const command_buffer &) noexcept -> command_buffer & = delete;

    command_buffer(command_buffer &&other) noexcept;
    auto operator=(command_buffer &&other) noexcept -> command_buffer &;
};

} // namespace aeon::vulkan

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <aeon/math/rectangle.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class buffer;
class command_pool;
class descriptor_set;
class pipeline;
class pipeline_layout;
class queue;
class render_pass_begin_info;
class viewport;
class image;

class command_buffer_ref
{
public:
    command_buffer_ref() noexcept;
    explicit command_buffer_ref(const vulkan::command_pool &command_pool, const VkCommandBuffer command_buffer);
    ~command_buffer_ref() = default;

    command_buffer_ref(const command_buffer_ref &) noexcept = default;
    auto operator=(const command_buffer_ref &) noexcept -> command_buffer_ref & = default;

    command_buffer_ref(command_buffer_ref &&other) noexcept = default;
    auto operator=(command_buffer_ref &&other) noexcept -> command_buffer_ref & = default;

    [[nodiscard]] auto handle() const noexcept -> VkCommandBuffer;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkCommandBuffer *;
    [[nodiscard]] auto command_pool() const noexcept -> const command_pool &;

    void begin(const common::flags<command_buffer_usage_flag> flags = command_buffer_usage_flag::none) const;
    void end() const;

    void begin_render_pass(const render_pass_begin_info &begin_info,
                           const subpass_contents contents = subpass_contents::inline_contents) const noexcept;
    void end_render_pass() const noexcept;

    void copy_buffer(const buffer &source, const VkDeviceSize source_offset, const buffer &destination,
                     const VkDeviceSize destination_offset, const VkDeviceSize size) const;

    void copy_staging_buffer_to_image(const buffer &source, const image &destination,
                                      const math::size2d<std::uint32_t> dimensions) const noexcept;

    void set_scissor(const math::rectangle<std::int32_t> rectangle) const noexcept;
    void set_viewport(const viewport &viewport) const noexcept;

    void bind_descriptor_set(const pipeline_bind_point bind_point, const pipeline_layout &layout,
                             const descriptor_set &descriptor_set) const noexcept;

    void bind_pipeline(const pipeline_bind_point bind_point, const pipeline &pipeline) const noexcept;
    void bind_graphics_pipeline(const pipeline &pipeline) const noexcept;
    void bind_compute_pipeline(const pipeline &pipeline) const noexcept;

    void bind_vertex_buffer(const buffer &buffer, const VkDeviceSize offset = 0) const noexcept;

    void bind_index_buffer(const buffer &buffer, const VkDeviceSize offset = 0,
                           const index_type type = index_type::uint32) const noexcept;

    void draw_indexed(const std::uint32_t index_count, const std::uint32_t first_index = 0,
                      const std::uint32_t vertex_offset = 0) const noexcept;

    /*!
     * Submit the command buffer to the queue and wait for it to be flushed by using a fence.
     */
    void flush(const queue &queue) const;

    void destroy() noexcept;

protected:
    const vulkan::command_pool *pool_;
    VkCommandBuffer buffer_;
};

[[nodiscard]] inline auto handle(const command_buffer_ref &b) noexcept
{
    return b.handle();
}

[[nodiscard]] inline auto handle(const command_buffer_ref *b) noexcept
{
    return handle(*b);
}

[[nodiscard]] inline auto handle_ptr(const command_buffer_ref &b) noexcept
{
    return b.handle_ptr();
}

[[nodiscard]] inline auto handle_ptr(const command_buffer_ref *b) noexcept
{
    return handle_ptr(*b);
}

} // namespace aeon::vulkan

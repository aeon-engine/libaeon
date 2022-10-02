// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/command_buffer_ref.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/fence.h>
#include <aeon/vulkan/buffer.h>
#include <aeon/vulkan/command_pool.h>
#include <aeon/vulkan/pipeline_layout.h>
#include <aeon/vulkan/descriptor_set.h>
#include <aeon/vulkan/render_pass_begin_info.h>
#include <aeon/vulkan/queue.h>
#include <aeon/vulkan/pipeline.h>
#include <aeon/vulkan/image.h>
#include <aeon/vulkan/viewport.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/initializers.h>
#include <chrono>

namespace aeon::vulkan
{

static constexpr auto command_buffer_fence_timeout = std::chrono::nanoseconds{100000000000};

command_buffer_ref::command_buffer_ref() noexcept
    : pool_{nullptr}
    , buffer_{nullptr}
{
}

command_buffer_ref::command_buffer_ref(const vulkan::command_pool &command_pool, const VkCommandBuffer command_buffer)
    : pool_{&command_pool}
    , buffer_{command_buffer}
{
}

auto command_buffer_ref::handle() const noexcept -> VkCommandBuffer
{
    return buffer_;
}

auto command_buffer_ref::handle_ptr() const noexcept -> const VkCommandBuffer *
{
    return &buffer_;
}

auto command_buffer_ref::command_pool() const noexcept -> const vulkan::command_pool &
{
    return *pool_;
}

void command_buffer_ref::begin(const common::flags<command_buffer_usage_flag> flags) const
{
    const auto info = initializers::command_buffer_begin_info(flags);
    checked_result{vkBeginCommandBuffer(buffer_, &info)};
}

void command_buffer_ref::end() const
{
    checked_result{vkEndCommandBuffer(buffer_)};
}

void command_buffer_ref::begin_render_pass(const render_pass_begin_info &begin_info,
                                           const subpass_contents contents) const noexcept
{
    vkCmdBeginRenderPass(buffer_, &begin_info, static_cast<VkSubpassContents>(contents));
}

void command_buffer_ref::end_render_pass() const noexcept
{
    vkCmdEndRenderPass(buffer_);
}

void command_buffer_ref::copy_buffer(const buffer &source, const VkDeviceSize source_offset, const buffer &destination,
                                     const VkDeviceSize destination_offset, const VkDeviceSize size) const
{
    VkBufferCopy region{};
    region.srcOffset = source_offset;
    region.dstOffset = destination_offset;
    region.size = size;

    vkCmdCopyBuffer(buffer_, vulkan::handle(source), vulkan::handle(destination), 1, &region);
}

void command_buffer_ref::copy_staging_buffer_to_image(const buffer &source, const image &destination,
                                                      const math::size2d<std::uint32_t> dimensions) const noexcept
{
    VkImageSubresourceRange subresource_range{};
    subresource_range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresource_range.baseMipLevel = 0;
    subresource_range.levelCount = 1;
    subresource_range.layerCount = 1;

    VkImageMemoryBarrier image_memory_barrier{};
    image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_memory_barrier.image = vulkan::handle(destination);
    image_memory_barrier.subresourceRange = subresource_range;
    image_memory_barrier.srcAccessMask = 0;
    image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    image_memory_barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    image_memory_barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

    vkCmdPipelineBarrier(buffer_, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr,
                         1, &image_memory_barrier);

    VkBufferImageCopy region{};
    region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;
    region.imageExtent.width = math::width(dimensions);
    region.imageExtent.height = math::height(dimensions);
    region.imageExtent.depth = 1;
    region.bufferOffset = 0;

    vkCmdCopyBufferToImage(buffer_, vulkan::handle(source), vulkan::handle(destination),
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    image_memory_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    image_memory_barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    image_memory_barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    vkCmdPipelineBarrier(buffer_, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr,
                         0, nullptr, 1, &image_memory_barrier);
}

void command_buffer_ref::set_scissor(const math::rectangle<std::int32_t> rectangle) const noexcept
{
    VkRect2D scissor{};
    scissor.extent.width = static_cast<std::uint32_t>(math::width(rectangle));
    scissor.extent.height = static_cast<std::uint32_t>(math::height(rectangle));
    scissor.offset.x = math::left(rectangle);
    scissor.offset.y = math::top(rectangle);
    vkCmdSetScissor(buffer_, 0, 1, &scissor);
}

void command_buffer_ref::set_viewport(const viewport &viewport) const noexcept
{
    vkCmdSetViewport(buffer_, 0, 1, &viewport);
}

void command_buffer_ref::bind_descriptor_set(const pipeline_bind_point bind_point, const pipeline_layout &layout,
                                             const descriptor_set &descriptor_set) const noexcept
{
    vkCmdBindDescriptorSets(buffer_, static_cast<VkPipelineBindPoint>(bind_point), vulkan::handle(layout), 0, 1,
                            vulkan::handle_ptr(descriptor_set), 0, nullptr);
}

void command_buffer_ref::bind_pipeline(const pipeline_bind_point bind_point, const pipeline &pipeline) const noexcept
{
    vkCmdBindPipeline(buffer_, static_cast<VkPipelineBindPoint>(bind_point), vulkan::handle(pipeline));
}

void command_buffer_ref::bind_graphics_pipeline(const pipeline &pipeline) const noexcept
{
    bind_pipeline(pipeline_bind_point::graphics, pipeline);
}

void command_buffer_ref::bind_compute_pipeline(const pipeline &pipeline) const noexcept
{
    bind_pipeline(pipeline_bind_point::compute, pipeline);
}

void command_buffer_ref::bind_vertex_buffer(const buffer &buffer, const VkDeviceSize offset) const noexcept
{
    vkCmdBindVertexBuffers(buffer_, 0, 1, vulkan::handle_ptr(buffer), &offset);
}

void command_buffer_ref::bind_index_buffer(const buffer &buffer, const VkDeviceSize offset,
                                           const index_type type) const noexcept
{
    vkCmdBindIndexBuffer(buffer_, vulkan::handle(buffer), offset, static_cast<VkIndexType>(type));
}

void command_buffer_ref::draw_indexed(const std::uint32_t index_count, const std::uint32_t first_index,
                                      const std::uint32_t vertex_offset) const noexcept
{
    vkCmdDrawIndexed(buffer_, index_count, 1, first_index, vertex_offset, 1);
}

void command_buffer_ref::flush(const queue &queue) const
{
    const fence fence{pool_->device()};
    queue.submit(buffer_, fence);
    fence.wait(command_buffer_fence_timeout);
}

void command_buffer_ref::destroy() noexcept
{
    if (buffer_)
        vkFreeCommandBuffers(vulkan::handle(pool_->device()), vulkan::handle(pool_), 1, &buffer_);

    buffer_ = nullptr;
}

} // namespace aeon::vulkan

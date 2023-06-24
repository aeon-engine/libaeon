// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/framebuffer.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/render_pass.h>
#include <aeon/vulkan/image_view.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_attachment_vector(const std::vector<image_view_ref> &attachments)
{
    std::vector<VkImageView> vk_attachments;
    vk_attachments.reserve(std::size(attachments));

    for (const auto &attachment : attachments)
    {
        vk_attachments.push_back(handle(attachment));
    }

    return vk_attachments;
}

[[nodiscard]] auto create_framebuffer(const device &device, const std::vector<image_view_ref> &attachments,
                                      const render_pass &render_pass, const math::size3d<std::uint32_t> size,
                                      const common::flags<framebuffer_create_flag> flags)
{
    VkFramebufferCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    info.renderPass = vulkan::handle(render_pass);

    const auto vk_attachments = create_attachment_vector(attachments);

    info.attachmentCount = static_cast<uint32_t>(std::size(vk_attachments));
    info.pAttachments = std::data(vk_attachments);
    info.width = size.width;
    info.height = size.height;
    info.layers = size.depth;
    info.flags = flags;

    VkFramebuffer handle{};
    checked_result(vkCreateFramebuffer(vulkan::handle(device), &info, nullptr, &handle));
    return handle;
}

} // namespace internal

framebuffer::framebuffer() noexcept
    : device_{nullptr}
    , handle_{VK_NULL_HANDLE}
{
}

framebuffer::framebuffer(const device &device, const std::vector<image_view_ref> &attachments,
                         const render_pass &render_pass, const math::size2d<std::uint32_t> size,
                         const std::uint32_t layers, const common::flags<framebuffer_create_flag> flags) noexcept
    : framebuffer{device, attachments, render_pass, math::size3d<std::uint32_t>{size, layers}, flags}
{
}

framebuffer::framebuffer(const device &device, const std::vector<image_view_ref> &attachments,
                         const render_pass &render_pass, const math::size3d<std::uint32_t> size,
                         const common::flags<framebuffer_create_flag> flags) noexcept
    : device_{&device}
    , handle_{internal::create_framebuffer(device, attachments, render_pass, size, flags)}
{
}

framebuffer::~framebuffer() noexcept
{
    destroy();
}

framebuffer::framebuffer(framebuffer &&other) noexcept
    : device_{other.device_}
    , handle_{other.handle_}
{
    other.handle_ = VK_NULL_HANDLE;
}

auto framebuffer::operator=(framebuffer &&other) noexcept -> framebuffer &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        handle_ = other.handle_;
        other.handle_ = VK_NULL_HANDLE;
    }

    return *this;
}

auto framebuffer::handle() const noexcept -> VkFramebuffer
{
    return handle_;
}

void framebuffer::destroy() const noexcept
{
    if (handle_)
        vkDestroyFramebuffer(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan

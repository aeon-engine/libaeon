// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/render_pass.h>
#include <aeon/vulkan/render_pass_description.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/device.h>
#include <aeon/common/assert.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto to_vk_subpass_description(const subpass &subpass) noexcept
{
    VkSubpassDescription description{};

    description.flags = subpass.flags();
    description.pipelineBindPoint = static_cast<VkPipelineBindPoint>(subpass.bind_point());

    if (subpass.has_input_attachments())
    {
        const auto &input_attachments = subpass.input_attachments();
        description.inputAttachmentCount = static_cast<std::uint32_t>(std::size(input_attachments));
        description.pInputAttachments = std::data(input_attachments);
    }

    if (subpass.has_color_attachments())
    {
        const auto &color_attachments = subpass.color_attachments();
        description.colorAttachmentCount = static_cast<std::uint32_t>(std::size(color_attachments));
        description.pColorAttachments = std::data(color_attachments);
    }

    if (subpass.has_resolve_attachments())
    {
        const auto &resolve_attachments = subpass.resolve_attachments();
        aeon_assert(std::size(resolve_attachments) == std::size(subpass.color_attachments()),
                    "Resolve attachments count must be equal to the amount of color attachments.");
        description.pResolveAttachments = std::data(resolve_attachments);
    }

    if (subpass.has_depth_stencil_attachment())
        description.pDepthStencilAttachment = subpass.depth_stencil_attachment_ptr();

    if (subpass.has_preserve_attachments())
    {
        const auto &preserve_attachments = subpass.preserve_attachments();
        description.preserveAttachmentCount = static_cast<std::uint32_t>(std::size(preserve_attachments));
        description.pPreserveAttachments = std::data(preserve_attachments);
    }

    return description;
}

[[nodiscard]] auto create_render_pass(const vulkan::device &device, const render_pass_description &description)
{
    VkRenderPassCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

    const auto &attachments = description.attachments();

    if (!std::empty(attachments))
    {
        info.attachmentCount = static_cast<std::uint32_t>(std::size(attachments));
        info.pAttachments = std::data(attachments);
    }

    const auto &sub_passes = description.subpasses();
    std::vector<VkSubpassDescription> vk_sub_passes;
    if (!std::empty(sub_passes))
    {
        vk_sub_passes.reserve(std::size(sub_passes));
        for (const auto &sub_pass : sub_passes)
        {
            vk_sub_passes.push_back(to_vk_subpass_description(sub_pass));
        }

        info.subpassCount = static_cast<std::uint32_t>(std::size(vk_sub_passes));
        info.pSubpasses = std::data(vk_sub_passes);
    }

    const auto &dependencies = description.subpass_dependencies();
    if (!std::empty(dependencies))
    {
        info.dependencyCount = static_cast<std::uint32_t>(std::size(dependencies));
        info.pDependencies = std::data(dependencies);
    }

    VkRenderPass render_pass{};
    checked_result(vkCreateRenderPass(vulkan::handle(device), &info, nullptr, &render_pass));
    return render_pass;
}

} // namespace internal

render_pass::render_pass() noexcept
    : device_{nullptr}
    , handle_{VK_NULL_HANDLE}
{
}

render_pass::render_pass(const vulkan::device &device, const render_pass_description &description)
    : device_{&device}
    , handle_{internal::create_render_pass(device, description)}
{
}

render_pass::~render_pass()
{
    destroy();
}

render_pass::render_pass(render_pass &&other) noexcept
    : device_{other.device_}
    , handle_{other.handle_}
{
    other.handle_ = VK_NULL_HANDLE;
}

auto render_pass::operator=(render_pass &&other) noexcept -> render_pass &
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

auto render_pass::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto render_pass::handle() const noexcept -> VkRenderPass
{
    return handle_;
}

void render_pass::destroy() const noexcept
{
    if (handle_)
        vkDestroyRenderPass(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan

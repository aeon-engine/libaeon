// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/render_pass_description.h>

namespace aeon::vulkan
{

auto render_pass_description::add_attachment(const vulkan::format format, const image_layout final_layout)
    -> attachment &
{
    return attachments_.emplace_back(format, final_layout);
}

auto render_pass_description::add_attachment(const VkFormat format, const image_layout final_layout) -> attachment &
{
    return attachments_.emplace_back(format, final_layout);
}

auto render_pass_description::add_attachment(const vulkan::format format, const sample_count samples,
                                             const attachment_load_op load_op, const attachment_store_op store_op,
                                             const attachment_load_op stencil_load_op,
                                             const attachment_store_op stencil_store_op,
                                             const image_layout initial_layout, const image_layout final_layout,
                                             const common::flags<attachment_description_flag> flags) -> attachment &
{
    return attachments_.emplace_back(format, samples, load_op, store_op, stencil_load_op, stencil_store_op,
                                     initial_layout, final_layout, flags);
}

auto render_pass_description::add_attachment(const VkFormat format, const sample_count samples,
                                             const attachment_load_op load_op, const attachment_store_op store_op,
                                             const attachment_load_op stencil_load_op,
                                             const attachment_store_op stencil_store_op,
                                             const image_layout initial_layout, const image_layout final_layout,
                                             const common::flags<attachment_description_flag> flags) -> attachment &
{
    return attachments_.emplace_back(format, samples, load_op, store_op, stencil_load_op, stencil_store_op,
                                     initial_layout, final_layout, flags);
}

auto render_pass_description::add_attachment(const VkFormat format, const VkSampleCountFlagBits samples,
                                             const VkAttachmentLoadOp load_op, const VkAttachmentStoreOp store_op,
                                             const VkAttachmentLoadOp stencil_load_op,
                                             const VkAttachmentStoreOp stencil_store_op,
                                             const VkImageLayout initial_layout, const VkImageLayout final_layout,
                                             const VkAttachmentDescriptionFlags flags) -> attachment &
{
    return attachments_.emplace_back(format, samples, load_op, store_op, stencil_load_op, stencil_store_op,
                                     initial_layout, final_layout, flags);
}

auto render_pass_description::add_subpass(const pipeline_bind_point bind_point,
                                          const common::flags<subpass_description_flag> flags) -> subpass &
{
    return subpasses_.emplace_back(bind_point, flags);
}

auto render_pass_description::add_subpass(std::vector<attachment_reference> color_attachments,
                                          const attachment_reference depth_stencil_attachment,
                                          std::vector<attachment_reference> input_attachments,
                                          std::vector<attachment_reference> resolve_attachments,
                                          std::vector<std::uint32_t> preserve_attachments,
                                          const pipeline_bind_point bind_point,
                                          const common::flags<subpass_description_flag> flags) -> subpass &
{
    return subpasses_.emplace_back(color_attachments, depth_stencil_attachment, input_attachments, resolve_attachments,
                                   preserve_attachments, bind_point, flags);
}

auto render_pass_description::add_subpass_dependency() -> subpass_dependency &
{
    return subpass_dependencies_.emplace_back();
}

auto render_pass_description::add_subpass_dependency(const std::uint32_t source_subpass,
                                                     const std::uint32_t destination_subpass,
                                                     const common::flags<pipeline_stage_flag> source_stage_mask,
                                                     const common::flags<pipeline_stage_flag> destination_stage_mask,
                                                     const common::flags<access_flag> source_access_mask,
                                                     const common::flags<access_flag> destination_access_mask,
                                                     const common::flags<dependency_flag> dependency_flags)
    -> subpass_dependency &
{
    return subpass_dependencies_.emplace_back(source_subpass, destination_subpass, source_stage_mask,
                                              destination_stage_mask, source_access_mask, destination_access_mask,
                                              dependency_flags);
}

auto render_pass_description::add_subpass_dependency(const std::uint32_t source_subpass,
                                                     const std::uint32_t destination_subpass,
                                                     const VkPipelineStageFlags source_stage_mask,
                                                     const VkPipelineStageFlags destination_stage_mask,
                                                     const VkAccessFlags source_access_mask,
                                                     const VkAccessFlags destination_access_mask,
                                                     const VkDependencyFlags dependency_flags) -> subpass_dependency &
{
    return subpass_dependencies_.emplace_back(source_subpass, destination_subpass, source_stage_mask,
                                              destination_stage_mask, source_access_mask, destination_access_mask,
                                              dependency_flags);
}

auto render_pass_description::attachments() const noexcept -> const std::vector<attachment> &
{
    return attachments_;
}

auto render_pass_description::subpasses() const noexcept -> const std::vector<subpass> &
{
    return subpasses_;
}

auto render_pass_description::subpass_dependencies() const noexcept -> const std::vector<subpass_dependency> &
{
    return subpass_dependencies_;
}

} // namespace aeon::vulkan

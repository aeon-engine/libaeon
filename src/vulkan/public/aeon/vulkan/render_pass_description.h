// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/attachment.h>
#include <aeon/vulkan/subpass.h>
#include <aeon/vulkan/subpass_dependency.h>
#include <vector>

namespace aeon::vulkan
{

class render_pass_description final
{
public:
    render_pass_description() noexcept = default;
    ~render_pass_description() = default;

    render_pass_description(const render_pass_description &) = default;
    auto operator=(const render_pass_description &) -> render_pass_description & = default;

    render_pass_description(render_pass_description &&) noexcept = default;
    auto operator=(render_pass_description &&) noexcept -> render_pass_description & = default;

    auto add_attachment(const vulkan::format format, const image_layout final_layout = image_layout::undefined)
        -> attachment &;
    auto add_attachment(const VkFormat format, const image_layout final_layout = image_layout::undefined)
        -> attachment &;

    auto add_attachment(const vulkan::format format, const sample_count samples, const attachment_load_op load_op,
                        const attachment_store_op store_op, const attachment_load_op stencil_load_op,
                        const attachment_store_op stencil_store_op, const image_layout initial_layout,
                        const image_layout final_layout,
                        const common::flags<attachment_description_flag> flags = attachment_description_flag::none)
        -> attachment &;

    auto add_attachment(const VkFormat format, const sample_count samples, const attachment_load_op load_op,
                        const attachment_store_op store_op, const attachment_load_op stencil_load_op,
                        const attachment_store_op stencil_store_op, const image_layout initial_layout,
                        const image_layout final_layout,
                        const common::flags<attachment_description_flag> flags = attachment_description_flag::none)
        -> attachment &;

    auto add_attachment(const VkFormat format, const VkSampleCountFlagBits samples, const VkAttachmentLoadOp load_op,
                        const VkAttachmentStoreOp store_op, const VkAttachmentLoadOp stencil_load_op,
                        const VkAttachmentStoreOp stencil_store_op, const VkImageLayout initial_layout,
                        const VkImageLayout final_layout, const VkAttachmentDescriptionFlags flags = 0) -> attachment &;

    auto add_subpass(const pipeline_bind_point bind_point = pipeline_bind_point::graphics,
                     const common::flags<subpass_description_flag> flags = {}) -> subpass &;

    auto add_subpass(std::vector<attachment_reference> color_attachments,
                     const attachment_reference depth_stencil_attachment = unused_attachment_reference,
                     std::vector<attachment_reference> input_attachments = {},
                     std::vector<attachment_reference> resolve_attachments = {},
                     std::vector<std::uint32_t> preserve_attachments = {},
                     const pipeline_bind_point bind_point = pipeline_bind_point::graphics,
                     const common::flags<subpass_description_flag> flags = {}) -> subpass &;

    auto add_subpass_dependency() -> subpass_dependency &;

    auto add_subpass_dependency(const std::uint32_t source_subpass, const std::uint32_t destination_subpass,
                                const common::flags<pipeline_stage_flag> source_stage_mask,
                                const common::flags<pipeline_stage_flag> destination_stage_mask,
                                const common::flags<access_flag> source_access_mask,
                                const common::flags<access_flag> destination_access_mask,
                                const common::flags<dependency_flag> dependency_flags = dependency_flag::by_region)
        -> subpass_dependency &;

    auto add_subpass_dependency(const std::uint32_t source_subpass, const std::uint32_t destination_subpass,
                                const VkPipelineStageFlags source_stage_mask,
                                const VkPipelineStageFlags destination_stage_mask,
                                const VkAccessFlags source_access_mask, const VkAccessFlags destination_access_mask,
                                const VkDependencyFlags dependency_flags) -> subpass_dependency &;

    [[nodiscard]] auto attachments() const noexcept -> const std::vector<attachment> &;

    [[nodiscard]] auto subpasses() const noexcept -> const std::vector<subpass> &;

    [[nodiscard]] auto subpass_dependencies() const noexcept -> const std::vector<subpass_dependency> &;

private:
    std::vector<attachment> attachments_;
    std::vector<subpass> subpasses_;
    std::vector<subpass_dependency> subpass_dependencies_;
};

} // namespace aeon::vulkan

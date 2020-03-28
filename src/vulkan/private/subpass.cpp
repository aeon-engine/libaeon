// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/subpass.h>
#include <aeon/common/assert.h>

namespace aeon::vulkan
{

subpass::subpass(const pipeline_bind_point bind_point, const common::flags<subpass_description_flag> flags) noexcept
    : bind_point_{bind_point}
    , flags_{flags}
    , color_attachments_{}
    , depth_stencil_attachment_{unused_attachment_reference}
    , input_attachments_{}
    , resolve_attachments_{}
    , preserve_attachments_{}
{
}

subpass::subpass(std::vector<attachment_reference> color_attachments,
                 const attachment_reference depth_stencil_attachment,
                 std::vector<attachment_reference> input_attachments,
                 std::vector<attachment_reference> resolve_attachments, std::vector<std::uint32_t> preserve_attachments,
                 const pipeline_bind_point bind_point, const common::flags<subpass_description_flag> flags) noexcept
    : bind_point_{static_cast<VkPipelineBindPoint>(bind_point)}
    , flags_{flags}
    , color_attachments_{std::move(color_attachments)}
    , depth_stencil_attachment_{depth_stencil_attachment}
    , input_attachments_{std::move(input_attachments)}
    , resolve_attachments_{std::move(resolve_attachments)}
    , preserve_attachments_{std::move(preserve_attachments)}
{
    aeon_assert(std::size(color_attachments_) == std::size(resolve_attachments_),
                "The amount of color attachments must match the amount of resolve attachments.");
}

auto subpass::bind_point() const noexcept -> pipeline_bind_point
{
    return bind_point_;
}

auto subpass::flags() const noexcept -> common::flags<subpass_description_flag>
{
    return flags_;
}

auto subpass::set_flags(const common::flags<subpass_description_flag> flags) noexcept -> subpass &
{
    flags_ = flags;
    return *this;
}

auto subpass::add_color_attachment(const attachment_reference reference) -> subpass &
{
    aeon_assert(!is_unused(reference), "A color attachment reference can not be unused.");
    color_attachments_.push_back(reference);
    return *this;
}

auto subpass::add_color_attachment(const std::uint32_t attachment, const image_layout layout) -> subpass &
{
    return add_color_attachment(attachment_reference{attachment, layout});
}

auto subpass::add_color_attachment(const std::uint32_t attachment, const VkImageLayout layout) -> subpass &
{
    return add_color_attachment(attachment_reference{attachment, layout});
}

auto subpass::add_color_attachments(const std::vector<attachment_reference> &references) -> subpass &
{
    for (const auto &reference : references)
        add_color_attachment(reference);

    return *this;
}

auto subpass::add_color_attachment(const attachment_reference reference, const attachment_reference resolve_reference)
    -> subpass &
{
    add_color_attachment(reference);
    add_resolve_attachment(resolve_reference);
    return *this;
}

auto subpass::add_color_attachment(const std::uint32_t attachment, const image_layout layout,
                                   const std::uint32_t resolve_attachment, const image_layout resolve_layout)
    -> subpass &
{
    return add_color_attachment(attachment_reference{attachment, layout},
                                attachment_reference{resolve_attachment, resolve_layout});
}

auto subpass::add_color_attachment(const std::uint32_t attachment, const VkImageLayout layout,
                                   const std::uint32_t resolve_attachment, const VkImageLayout resolve_layout)
    -> subpass &
{
    return add_color_attachment(attachment_reference{attachment, layout},
                                attachment_reference{resolve_attachment, resolve_layout});
}

auto subpass::has_color_attachments() const noexcept -> bool
{
    return !std::empty(color_attachments_);
}

auto subpass::color_attachments() const noexcept -> const std::vector<attachment_reference> &
{
    return color_attachments_;
}

auto subpass::set_depth_stencil_attachment(const attachment_reference reference) -> subpass &
{
    depth_stencil_attachment_ = reference;
    return *this;
}

auto subpass::set_depth_stencil_attachment(const std::uint32_t attachment, const image_layout layout) -> subpass &
{
    return set_depth_stencil_attachment(attachment_reference{attachment, layout});
}

auto subpass::set_depth_stencil_attachment(const std::uint32_t attachment, const VkImageLayout layout) -> subpass &
{
    return set_depth_stencil_attachment(attachment_reference{attachment, layout});
}

auto subpass::has_depth_stencil_attachment() const noexcept -> bool
{
    return !is_unused(depth_stencil_attachment_);
}

auto subpass::depth_stencil_attachment() const noexcept -> const attachment_reference &
{
    return depth_stencil_attachment_;
}

auto subpass::depth_stencil_attachment_ptr() const noexcept -> const attachment_reference *
{
    return &depth_stencil_attachment_;
}

auto subpass::add_input_attachment(const attachment_reference reference) -> subpass &
{
    aeon_assert(!is_unused(reference), "An input attachment reference can not be unused.");
    input_attachments_.push_back(reference);
    return *this;
}

auto subpass::add_input_attachment(const std::uint32_t attachment, const image_layout layout) -> subpass &
{
    return add_input_attachment(attachment_reference{attachment, layout});
}

auto subpass::add_input_attachment(const std::uint32_t attachment, const VkImageLayout layout) -> subpass &
{
    return add_input_attachment(attachment_reference{attachment, layout});
}

auto subpass::add_input_attachments(const std::vector<attachment_reference> &references) -> subpass &
{
    for (const auto &reference : references)
        add_input_attachment(reference);

    return *this;
}

auto subpass::has_input_attachments() const noexcept -> bool
{
    return !std::empty(input_attachments_);
}

auto subpass::input_attachments() const noexcept -> const std::vector<attachment_reference> &
{
    return input_attachments_;
}

auto subpass::has_resolve_attachments() const noexcept -> bool
{
    return !std::empty(resolve_attachments_);
}

auto subpass::resolve_attachments() const noexcept -> const std::vector<attachment_reference> &
{
    return resolve_attachments_;
}

auto subpass::add_preserve_attachment(const std::uint32_t attachment) -> subpass &
{
    preserve_attachments_.push_back(attachment);
    return *this;
}

auto subpass::add_preserve_attachments(const std::vector<std::uint32_t> &attachments) -> subpass &
{
    for (const auto &attachment : attachments)
        add_preserve_attachment(attachment);

    return *this;
}

auto subpass::has_preserve_attachments() const noexcept -> bool
{
    return !std::empty(preserve_attachments_);
}

auto subpass::preserve_attachments() const noexcept -> const std::vector<std::uint32_t> &
{
    return preserve_attachments_;
}

void subpass::add_resolve_attachment(const attachment_reference reference)
{
    aeon_assert(!is_unused(reference), "A resolve attachment reference can not be unused.");
    aeon_assert(std::size(color_attachments_) == std::size(resolve_attachments_),
                "The amount of color attachments must match the amount of resolve attachments.");
    resolve_attachments_.push_back(reference);
}

} // namespace aeon::vulkan

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/format.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class attachment final : public VkAttachmentDescription
{
public:
    constexpr explicit attachment(const vulkan::format format,
                                  const image_layout final_layout = image_layout::undefined) noexcept;
    constexpr explicit attachment(const VkFormat format,
                                  const image_layout final_layout = image_layout::undefined) noexcept;

    constexpr explicit attachment(
        const vulkan::format format, const sample_count samples, const attachment_load_op load_op,
        const attachment_store_op store_op, const attachment_load_op stencil_load_op,
        const attachment_store_op stencil_store_op, const image_layout initial_layout, const image_layout final_layout,
        const common::flags<attachment_description_flag> flags = attachment_description_flag::none) noexcept;

    constexpr explicit attachment(
        const VkFormat format, const sample_count samples, const attachment_load_op load_op,
        const attachment_store_op store_op, const attachment_load_op stencil_load_op,
        const attachment_store_op stencil_store_op, const image_layout initial_layout, const image_layout final_layout,
        const common::flags<attachment_description_flag> flags = attachment_description_flag::none) noexcept;

    constexpr explicit attachment(const VkFormat format, const VkSampleCountFlagBits samples,
                                  const VkAttachmentLoadOp load_op, const VkAttachmentStoreOp store_op,
                                  const VkAttachmentLoadOp stencil_load_op, const VkAttachmentStoreOp stencil_store_op,
                                  const VkImageLayout initial_layout, const VkImageLayout final_layout,
                                  const VkAttachmentDescriptionFlags flags = 0) noexcept;

    ~attachment() = default;

    constexpr attachment(const attachment &) noexcept = default;
    constexpr auto operator=(const attachment &) noexcept -> attachment & = default;

    constexpr attachment(attachment &&) noexcept = default;
    constexpr auto operator=(attachment &&) noexcept -> attachment & = default;

    constexpr auto samples(const sample_count samples) noexcept -> attachment &;
    constexpr auto load_op(const attachment_load_op load_op) noexcept -> attachment &;
    constexpr auto store_op(const attachment_store_op store_op) noexcept -> attachment &;
    constexpr auto stencil_load_op(const attachment_load_op load_op) noexcept -> attachment &;
    constexpr auto stencil_store_op(const attachment_store_op store_op) noexcept -> attachment &;
    constexpr auto initial_layout(const image_layout layout) noexcept -> attachment &;
    constexpr auto final_layout(const image_layout layout) noexcept -> attachment &;
    constexpr auto flags(const common::flags<attachment_description_flag> flags) noexcept -> attachment &;
};

inline constexpr attachment::attachment(const vulkan::format format, const image_layout final_layout) noexcept
    : attachment{static_cast<VkFormat>(format), final_layout}
{
}

inline constexpr attachment::attachment(const VkFormat format, const image_layout final_layout) noexcept
    : attachment{format,
                 sample_count::count_1,
                 attachment_load_op::clear,
                 attachment_store_op::dont_care,
                 attachment_load_op::dont_care,
                 attachment_store_op::dont_care,
                 image_layout::undefined,
                 final_layout}
{
}

inline constexpr attachment::attachment(const vulkan::format format, const sample_count samples,
                                        const attachment_load_op load_op, const attachment_store_op store_op,
                                        const attachment_load_op stencil_load_op,
                                        const attachment_store_op stencil_store_op, const image_layout initial_layout,
                                        const image_layout final_layout,
                                        const common::flags<attachment_description_flag> flags) noexcept
    : attachment{static_cast<VkFormat>(format),
                 static_cast<VkSampleCountFlagBits>(samples),
                 static_cast<VkAttachmentLoadOp>(load_op),
                 static_cast<VkAttachmentStoreOp>(store_op),
                 static_cast<VkAttachmentLoadOp>(stencil_load_op),
                 static_cast<VkAttachmentStoreOp>(stencil_store_op),
                 static_cast<VkImageLayout>(initial_layout),
                 static_cast<VkImageLayout>(final_layout),
                 flags}
{
}

constexpr attachment::attachment(const VkFormat format, const sample_count samples, const attachment_load_op load_op,
                                 const attachment_store_op store_op, const attachment_load_op stencil_load_op,
                                 const attachment_store_op stencil_store_op, const image_layout initial_layout,
                                 const image_layout final_layout,
                                 const common::flags<attachment_description_flag> flags) noexcept
    : attachment{format,
                 static_cast<VkSampleCountFlagBits>(samples),
                 static_cast<VkAttachmentLoadOp>(load_op),
                 static_cast<VkAttachmentStoreOp>(store_op),
                 static_cast<VkAttachmentLoadOp>(stencil_load_op),
                 static_cast<VkAttachmentStoreOp>(stencil_store_op),
                 static_cast<VkImageLayout>(initial_layout),
                 static_cast<VkImageLayout>(final_layout),
                 flags}
{
}

inline constexpr attachment::attachment(const VkFormat format, const VkSampleCountFlagBits samples,
                                        const VkAttachmentLoadOp load_op, const VkAttachmentStoreOp store_op,
                                        const VkAttachmentLoadOp stencil_load_op,
                                        const VkAttachmentStoreOp stencil_store_op, const VkImageLayout initial_layout,
                                        const VkImageLayout final_layout,
                                        const VkAttachmentDescriptionFlags flags) noexcept
    : VkAttachmentDescription{flags,           format,           samples,        load_op,     store_op,
                              stencil_load_op, stencil_store_op, initial_layout, final_layout}
{
}

constexpr auto attachment::samples(const sample_count samples) noexcept -> attachment &
{
    VkAttachmentDescription::samples = static_cast<VkSampleCountFlagBits>(samples);
    return *this;
}

constexpr auto attachment::load_op(const attachment_load_op load_op) noexcept -> attachment &
{
    VkAttachmentDescription::loadOp = static_cast<VkAttachmentLoadOp>(load_op);
    return *this;
}

constexpr auto attachment::store_op(const attachment_store_op store_op) noexcept -> attachment &
{
    VkAttachmentDescription::storeOp = static_cast<VkAttachmentStoreOp>(store_op);
    return *this;
}

constexpr auto attachment::stencil_load_op(const attachment_load_op load_op) noexcept -> attachment &
{
    VkAttachmentDescription::stencilLoadOp = static_cast<VkAttachmentLoadOp>(load_op);
    return *this;
}

constexpr auto attachment::stencil_store_op(const attachment_store_op store_op) noexcept -> attachment &
{
    VkAttachmentDescription::stencilStoreOp = static_cast<VkAttachmentStoreOp>(store_op);
    return *this;
}

constexpr auto attachment::initial_layout(const image_layout layout) noexcept -> attachment &
{
    VkAttachmentDescription::initialLayout = static_cast<VkImageLayout>(layout);
    return *this;
}

constexpr auto attachment::final_layout(const image_layout layout) noexcept -> attachment &
{
    VkAttachmentDescription::finalLayout = static_cast<VkImageLayout>(layout);
    return *this;
}

constexpr auto attachment::flags(const common::flags<attachment_description_flag> flags) noexcept -> attachment &
{
    VkAttachmentDescription::flags = flags;
    return *this;
}

static_assert(sizeof(attachment) == sizeof(VkAttachmentDescription));

} // namespace aeon::vulkan

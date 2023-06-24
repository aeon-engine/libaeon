// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <vulkan/vulkan_core.h>
#include <cstdint>
#include <limits>

namespace aeon::vulkan
{

class attachment_reference final : public VkAttachmentReference
{
public:
    constexpr explicit attachment_reference(const std::uint32_t attachment, const image_layout layout) noexcept;

    constexpr explicit attachment_reference(const std::uint32_t attachment, const VkImageLayout layout) noexcept;

    ~attachment_reference() = default;

    constexpr attachment_reference(const attachment_reference &) noexcept = default;
    constexpr auto operator=(const attachment_reference &) noexcept -> attachment_reference & = default;

    constexpr attachment_reference(attachment_reference &&) noexcept = default;
    constexpr auto operator=(attachment_reference &&) noexcept -> attachment_reference & = default;
};

inline constexpr attachment_reference::attachment_reference(const std::uint32_t attachment,
                                                            const image_layout layout) noexcept
    : attachment_reference{attachment, static_cast<VkImageLayout>(layout)}
{
}

inline constexpr attachment_reference::attachment_reference(const std::uint32_t attachment,
                                                            const VkImageLayout layout) noexcept
    : VkAttachmentReference{attachment, layout}
{
}

static constexpr auto unused_attachment_reference =
    attachment_reference{std::numeric_limits<std::uint32_t>::max(), image_layout::undefined};

[[nodiscard]] constexpr auto is_unused(const attachment_reference &a) noexcept
{
    return a.attachment == std::numeric_limits<std::uint32_t>::max() && a.layout == VK_IMAGE_LAYOUT_UNDEFINED;
}

static_assert(sizeof(attachment_reference) == sizeof(VkAttachmentReference));

} // namespace aeon::vulkan

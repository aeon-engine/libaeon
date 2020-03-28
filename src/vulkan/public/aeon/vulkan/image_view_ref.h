// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class device;

class image_view_ref
{
public:
    image_view_ref() noexcept;
    explicit image_view_ref(const device &device, const VkImageView handle) noexcept;
    ~image_view_ref() noexcept = default;

    image_view_ref(const image_view_ref &) noexcept = default;
    auto operator=(const image_view_ref &) noexcept -> image_view_ref & = default;

    image_view_ref(image_view_ref &&) noexcept = default;
    auto operator=(image_view_ref &&) noexcept -> image_view_ref & = default;

    [[nodiscard]] auto handle() const noexcept -> VkImageView;

    void destroy() noexcept;

protected:
    const device *device_;
    VkImageView handle_;
};

[[nodiscard]] inline auto handle(const image_view_ref &i) noexcept
{
    return i.handle();
}

} // namespace aeon::vulkan

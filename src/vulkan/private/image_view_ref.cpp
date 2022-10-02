// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/image_view_ref.h>
#include <aeon/vulkan/device.h>

namespace aeon::vulkan
{

image_view_ref::image_view_ref() noexcept
    : device_{nullptr}
    , handle_{nullptr}
{
}

image_view_ref::image_view_ref(const device &device, const VkImageView handle) noexcept
    : device_{&device}
    , handle_{handle}
{
}

auto image_view_ref::handle() const noexcept -> VkImageView
{
    return handle_;
}

void image_view_ref::destroy() noexcept
{
    if (handle_)
        vkDestroyImageView(vulkan::handle(*device_), handle_, nullptr);

    handle_ = nullptr;
}

} // namespace aeon::vulkan

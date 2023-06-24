// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/sampler.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_sampler(const device &device, const sampler_create_info &info)
{
    VkSampler handle = VK_NULL_HANDLE;
    checked_result{vkCreateSampler(vulkan::handle(device), &info, nullptr, &handle)};
    return handle;
}

} // namespace internal

sampler::sampler() noexcept
    : handle_{VK_NULL_HANDLE}
    , device_{nullptr}
{
}

sampler::sampler(const device &device, const sampler_create_info &info)
    : handle_{internal::create_sampler(device, info)}
    , device_{vulkan::handle(device)}
{
}

sampler::~sampler()
{
    destroy();
}

sampler::sampler(sampler &&other) noexcept
    : handle_{other.handle_}
    , device_{other.device_}
{
    other.handle_ = VK_NULL_HANDLE;
}

auto sampler::operator=(sampler &&other) noexcept -> sampler &
{
    if (this != &other) [[likely]]
    {
        destroy();

        handle_ = other.handle_;
        device_ = other.device_;

        other.handle_ = VK_NULL_HANDLE;
    }

    return *this;
}

auto sampler::handle() const noexcept -> VkSampler
{
    return handle_;
}

void sampler::destroy() const noexcept
{
    if (handle_)
        vkDestroySampler(device_, handle_, nullptr);
}

} // namespace aeon::vulkan

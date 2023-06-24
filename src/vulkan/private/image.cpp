// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/image.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/initializers.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto to_extent3d(const math::size3d<std::uint32_t> extent)
{
    VkExtent3D vkextent{};
    vkextent.width = extent.width;
    vkextent.height = extent.height;
    vkextent.depth = extent.depth;
    return vkextent;
}

[[nodiscard]] auto create_image(VmaAllocation &out_allocation, const device &device, const image_type type,
                                const VkExtent3D extent, const VkFormat format,
                                const common::flags<image_usage_flag> usage_flags, const sample_count samples,
                                const std::uint32_t mip_levels, const std::uint32_t array_layers,
                                const image_tiling tiling, const common::flags<image_create_flag> create_flags,
                                const memory_allocation_usage allocation_usage)
{
    const auto info = initializers::image_create_info(type, extent, format, mip_levels, array_layers, samples, tiling,
                                                      usage_flags, create_flags);

    VmaAllocationCreateInfo alloc_info{};
    alloc_info.usage = static_cast<VmaMemoryUsage>(allocation_usage);

    VkImage image;
    vmaCreateImage(device.allocator_handle(), &info, &alloc_info, &image, &out_allocation, nullptr);
    return image;
}

} // namespace internal

image::image() noexcept
    : device_memory{}
    , handle_{VK_NULL_HANDLE}
{
}

image::image(const vulkan::device &device, const image_type type, const math::size2d<std::uint32_t> size,
             const format format, const common::flags<image_usage_flag> usage_flags,
             const memory_allocation_usage allocation_usage, const sample_count samples, const std::uint32_t mip_levels,
             const std::uint32_t array_layers, const image_tiling tiling,
             const common::flags<image_create_flag> create_flags)
    : image{device,  type,        math::size3d<std::uint32_t>{size, 1},
            format,  usage_flags, allocation_usage,
            samples, mip_levels,  array_layers,
            tiling,  create_flags}
{
}

image::image(const vulkan::device &device, const image_type type, const math::size3d<std::uint32_t> extent,
             const format format, const common::flags<image_usage_flag> usage_flags,
             const memory_allocation_usage allocation_usage, const sample_count samples, const std::uint32_t mip_levels,
             const std::uint32_t array_layers, const image_tiling tiling,
             const common::flags<image_create_flag> create_flags)
    : image{device,
            type,
            internal::to_extent3d(extent),
            static_cast<VkFormat>(format),
            usage_flags,
            allocation_usage,
            samples,
            mip_levels,
            array_layers,
            tiling,
            create_flags}
{
}

image::image(const vulkan::device &device, const image_type type, const VkExtent3D extent, const VkFormat format,
             const common::flags<image_usage_flag> usage_flags, const memory_allocation_usage allocation_usage,
             const sample_count samples, const std::uint32_t mip_levels, const std::uint32_t array_layers,
             const image_tiling tiling, const common::flags<image_create_flag> create_flags)
    : device_memory{device, 0}
    , handle_{internal::create_image(allocation_, device, type, extent, format, usage_flags, samples, mip_levels,
                                     array_layers, tiling, create_flags, allocation_usage)}
{
}

image::~image() noexcept
{
    destroy();
}

image::image(image &&other) noexcept
    : device_memory{std::move(other)}
    , handle_{other.handle_}
{
    other.handle_ = VK_NULL_HANDLE;
    other.allocation_ = nullptr;
}

auto image::operator=(image &&other) noexcept -> image &
{
    if (this != &other) [[likely]]
    {
        destroy();

        allocation_ = other.allocation_;
        device_ = other.device_;
        size_ = other.size_;
        handle_ = other.handle_;

        other.handle_ = VK_NULL_HANDLE;
        other.allocation_ = nullptr;
    }

    return *this;
}

auto image::handle() const noexcept -> VkImage
{
    return handle_;
}

void image::destroy() const noexcept
{
    if (handle_)
        vmaDestroyImage(device_->allocator_handle(), handle_, allocation_);
}

} // namespace aeon::vulkan

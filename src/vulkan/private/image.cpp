// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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

[[nodiscard]] auto create_image(const device &device, const image_type type, const VkExtent3D extent,
                                const VkFormat format, const common::flags<image_usage_flag> usage_flags,
                                const sample_count samples, const std::uint32_t mip_levels,
                                const std::uint32_t array_layers, const image_tiling tiling,
                                const common::flags<image_create_flag> create_flags)
{
    const auto info = initializers::image_create_info(type, extent, format, mip_levels, array_layers, samples, tiling,
                                                      usage_flags, create_flags);

    VkImage image;
    checked_result{vkCreateImage(handle(device), &info, nullptr, &image)};
    return image;
}

[[nodiscard]] auto get_image_memory_requirements(const VkDevice device, const VkImage image) noexcept
{
    VkMemoryRequirements requirements{};
    vkGetImageMemoryRequirements(device, image, &requirements);
    return requirements;
}

} // namespace internal

image::image() noexcept
    : device_{nullptr}
    , handle_{nullptr}
    , requirements_{}
{
}

image::image(const vulkan::device &device, const image_type type, const math::size2d<std::uint32_t> size,
             const format format, const common::flags<image_usage_flag> usage_flags, const sample_count samples,
             const std::uint32_t mip_levels, const std::uint32_t array_layers, const image_tiling tiling,
             const common::flags<image_create_flag> create_flags)
    : image{device,      type,         math::size3d<std::uint32_t>{size, 1},
            format,      usage_flags,  samples,
            mip_levels,  array_layers, tiling,
            create_flags}
{
}

image::image(const vulkan::device &device, const image_type type, const math::size3d<std::uint32_t> extent,
             const format format, const common::flags<image_usage_flag> usage_flags, const sample_count samples,
             const std::uint32_t mip_levels, const std::uint32_t array_layers, const image_tiling tiling,
             const common::flags<image_create_flag> create_flags)
    : image{device,
            type,
            internal::to_extent3d(extent),
            static_cast<VkFormat>(format),
            usage_flags,
            samples,
            mip_levels,
            array_layers,
            tiling,
            create_flags}
{
}

image::image(const vulkan::device &device, const image_type type, const VkExtent3D extent, const VkFormat format,
             const common::flags<image_usage_flag> usage_flags, const sample_count samples,
             const std::uint32_t mip_levels, const std::uint32_t array_layers, const image_tiling tiling,
             const common::flags<image_create_flag> create_flags)
    : device_{&device}
    , handle_{internal::create_image(device, type, extent, format, usage_flags, samples, mip_levels, array_layers,
                                     tiling, create_flags)}
    , requirements_{internal::get_image_memory_requirements(vulkan::handle(device), handle_)}
{
}

image::~image() noexcept
{
    destroy();
}

image::image(image &&other) noexcept
    : device_{other.device_}
    , handle_{other.handle_}
    , requirements_{other.requirements_}
{
    other.handle_ = nullptr;
}

auto image::operator=(image &&other) noexcept -> image &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        handle_ = other.handle_;
        requirements_ = other.requirements_;

        other.handle_ = nullptr;
    }

    return *this;
}

auto image::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto image::handle() const noexcept -> VkImage
{
    return handle_;
}

auto image::memory_requirements() const noexcept -> VkMemoryRequirements
{
    return requirements_;
}

auto image::required_size() const noexcept -> std::size_t
{
    return requirements_.size;
}

auto image::required_alignment() const noexcept -> std::size_t
{
    return requirements_.alignment;
}

auto image::required_memory_type_bits() const noexcept -> std::uint32_t
{
    return requirements_.memoryTypeBits;
}

void image::bind_memory(const device_memory &memory, const VkDeviceSize offset) const
{
    checked_result{vkBindImageMemory(vulkan::handle(device_), handle_, vulkan::handle(memory), offset)};
}

void image::destroy() const noexcept
{
    if (handle_)
        vkDestroyImage(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan

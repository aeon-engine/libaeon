// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/device_memory.h>
#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <aeon/math/size2d.h>
#include <aeon/math/size3d.h>
#include <vulkan/vulkan_core.h>
#include <cstddef>

namespace aeon::vulkan
{

enum class format;
class device;

class image final : public device_memory
{
public:
    image() noexcept;

    explicit image(const vulkan::device &device, const image_type type, const math::size2d<std::uint32_t> size,
                   const format format, const common::flags<image_usage_flag> usage_flags,
                   const memory_allocation_usage allocation_usage, const sample_count samples = sample_count::count_1,
                   const std::uint32_t mip_levels = 1, const std::uint32_t array_layers = 1,
                   const image_tiling tiling = image_tiling::optimal,
                   const common::flags<image_create_flag> create_flags = {});

    explicit image(const vulkan::device &device, const image_type type, const math::size3d<std::uint32_t> extent,
                   const format format, const common::flags<image_usage_flag> usage_flags,
                   const memory_allocation_usage allocation_usage, const sample_count samples = sample_count::count_1,
                   const std::uint32_t mip_levels = 1, const std::uint32_t array_layers = 1,
                   const image_tiling tiling = image_tiling::optimal,
                   const common::flags<image_create_flag> create_flags = {});

    explicit image(const vulkan::device &device, const image_type type, const VkExtent3D extent, const VkFormat format,
                   const common::flags<image_usage_flag> usage_flags, const memory_allocation_usage allocation_usage,
                   const sample_count samples = sample_count::count_1, const std::uint32_t mip_levels = 1,
                   const std::uint32_t array_layers = 1, const image_tiling tiling = image_tiling::optimal,
                   const common::flags<image_create_flag> create_flags = {});

    ~image() noexcept;

    image(const image &) noexcept = delete;
    auto operator=(const image &) noexcept -> image & = delete;

    image(image &&other) noexcept;
    auto operator=(image &&other) noexcept -> image &;

    [[nodiscard]] auto handle() const noexcept -> VkImage;

private:
    void destroy() const noexcept;

    VkImage handle_;
};

[[nodiscard]] inline auto handle(const image &img) noexcept
{
    return img.handle();
}

} // namespace aeon::vulkan

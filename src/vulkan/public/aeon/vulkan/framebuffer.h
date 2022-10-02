// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/math/size2d.h>
#include <aeon/math/size3d.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class device;
class image_view_ref;
class render_pass;
class swap_chain;

class framebuffer final
{
public:
    framebuffer() noexcept;
    explicit framebuffer(const device &device, const std::vector<image_view_ref> &attachments,
                         const render_pass &render_pass, const math::size2d<std::uint32_t> size,
                         const std::uint32_t layers = 1,
                         const common::flags<framebuffer_create_flag> flags = framebuffer_create_flag::none) noexcept;

    explicit framebuffer(const device &device, const std::vector<image_view_ref> &attachments,
                         const render_pass &render_pass, const math::size3d<std::uint32_t> size,
                         const common::flags<framebuffer_create_flag> flags = framebuffer_create_flag::none) noexcept;

    ~framebuffer() noexcept;

    framebuffer(const framebuffer &) noexcept = delete;
    auto operator=(const framebuffer &) noexcept -> framebuffer & = delete;

    framebuffer(framebuffer &&other) noexcept;
    auto operator=(framebuffer &&other) noexcept -> framebuffer &;

    [[nodiscard]] auto handle() const noexcept -> VkFramebuffer;

protected:
    void destroy() const noexcept;

    const device *device_;
    VkFramebuffer handle_;
};

[[nodiscard]] inline auto handle(const framebuffer &f) noexcept
{
    return f.handle();
}

} // namespace aeon::vulkan

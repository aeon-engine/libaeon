// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class device;
class render_pass_description;

class render_pass final
{
public:
    render_pass() noexcept;
    explicit render_pass(const vulkan::device &device, const render_pass_description &description);
    ~render_pass();

    render_pass(const render_pass &) noexcept = delete;
    auto operator=(const render_pass &) noexcept -> render_pass & = delete;

    render_pass(render_pass &&other) noexcept;
    auto operator=(render_pass &&other) noexcept -> render_pass &;

    [[nodiscard]] auto device() const noexcept -> const device &;

    [[nodiscard]] auto handle() const noexcept -> VkRenderPass;

private:
    void destroy() const noexcept;

    const vulkan::device *device_;
    VkRenderPass handle_;
};

[[nodiscard]] inline auto handle(const render_pass &rp) noexcept
{
    return rp.handle();
}

} // namespace aeon::vulkan

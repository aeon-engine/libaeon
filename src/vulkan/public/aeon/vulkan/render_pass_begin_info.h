// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/render_pass.h>
#include <aeon/vulkan/framebuffer.h>
#include <aeon/vulkan/rectangle.h>
#include <vulkan/vulkan_core.h>
#include <array>
#include <vector>

namespace aeon::vulkan
{

class render_pass_begin_info final : public VkRenderPassBeginInfo
{
public:
    explicit render_pass_begin_info(const vulkan::render_pass &render_pass) noexcept;
    explicit render_pass_begin_info(const vulkan::render_pass &render_pass,
                                    const vulkan::framebuffer &framebuffer) noexcept;
    explicit render_pass_begin_info(const vulkan::render_pass &render_pass, const vulkan::framebuffer &framebuffer,
                                    const vulkan::rectangle render_area) noexcept;
    ~render_pass_begin_info() = default;

    render_pass_begin_info(const render_pass_begin_info &other);
    auto operator=(const render_pass_begin_info &other) -> render_pass_begin_info &;

    render_pass_begin_info(render_pass_begin_info &&) noexcept = default;
    auto operator=(render_pass_begin_info &&) noexcept -> render_pass_begin_info & = default;

    auto add_clear_color(VkClearColorValue clear_color) -> render_pass_begin_info &;
    auto add_clear_color(const float color1, const float color2, const float color3, const float color4)
        -> render_pass_begin_info &;
    auto add_clear_color(const std::int32_t color1, const std::int32_t color2, const std::int32_t color3,
                         const std::int32_t color4) -> render_pass_begin_info &;
    auto add_clear_color(const std::uint32_t color1, const std::uint32_t color2, const std::uint32_t color3,
                         const std::uint32_t color4) -> render_pass_begin_info &;

    auto add_clear_depth_stencil(VkClearDepthStencilValue depth_stencil_clear_value) -> render_pass_begin_info &;
    auto add_clear_depth_stencil(const float depth, const std::uint32_t stencil = 0) -> render_pass_begin_info &;

    auto framebuffer(const vulkan::framebuffer &framebuffer) -> render_pass_begin_info &;
    auto framebuffer() const noexcept -> const vulkan::framebuffer &;

private:
    std::vector<VkClearValue> clear_values_;
    const vulkan::framebuffer *framebuffer_;
};

inline render_pass_begin_info::render_pass_begin_info(const vulkan::render_pass &render_pass) noexcept
    : VkRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                            nullptr,
                            handle(render_pass),
                            VK_NULL_HANDLE,
                            {},
                            0,
                            nullptr}
    , clear_values_{}
    , framebuffer_{nullptr}
{
}

inline render_pass_begin_info::render_pass_begin_info(const vulkan::render_pass &render_pass,
                                                      const vulkan::framebuffer &framebuffer) noexcept
    : VkRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                            nullptr,
                            handle(render_pass),
                            handle(framebuffer),
                            {},
                            0,
                            nullptr}
    , clear_values_{}
    , framebuffer_{&framebuffer}
{
}

inline render_pass_begin_info::render_pass_begin_info(const vulkan::render_pass &render_pass,
                                                      const vulkan::framebuffer &framebuffer,
                                                      const vulkan::rectangle render_area) noexcept
    : VkRenderPassBeginInfo{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
                            nullptr,
                            handle(render_pass),
                            handle(framebuffer),
                            render_area,
                            0,
                            nullptr}
    , clear_values_{}
    , framebuffer_{&framebuffer}
{
}

inline render_pass_begin_info::render_pass_begin_info(const render_pass_begin_info &other)
    : VkRenderPassBeginInfo{other}
    , clear_values_{other.clear_values_}
    , framebuffer_{other.framebuffer_}
{
    if (!std::empty(clear_values_))
    {
        VkRenderPassBeginInfo::clearValueCount = static_cast<std::uint32_t>(std::size(clear_values_));
        VkRenderPassBeginInfo::pClearValues = std::data(clear_values_);
    }
}

inline auto render_pass_begin_info::operator=(const render_pass_begin_info &other) -> render_pass_begin_info &
{
    if (this == &other) [[unlikely]]
        return *this;

    VkRenderPassBeginInfo::sType = other.sType;
    VkRenderPassBeginInfo::pNext = other.pNext;
    VkRenderPassBeginInfo::renderPass = other.renderPass;
    VkRenderPassBeginInfo::framebuffer = other.VkRenderPassBeginInfo::framebuffer;
    VkRenderPassBeginInfo::renderArea = other.renderArea;

    clear_values_ = other.clear_values_;

    if (!std::empty(clear_values_))
    {
        VkRenderPassBeginInfo::clearValueCount = static_cast<std::uint32_t>(std::size(clear_values_));
        VkRenderPassBeginInfo::pClearValues = std::data(clear_values_);
    }
    else
    {
        VkRenderPassBeginInfo::clearValueCount = 0;
        VkRenderPassBeginInfo::pClearValues = nullptr;
    }

    framebuffer_ = other.framebuffer_;

    return *this;
}

inline auto render_pass_begin_info::add_clear_color(VkClearColorValue clear_color) -> render_pass_begin_info &
{
    VkClearValue value;
    value.color = clear_color;

    clear_values_.push_back(value);
    VkRenderPassBeginInfo::clearValueCount = static_cast<std::uint32_t>(std::size(clear_values_));
    VkRenderPassBeginInfo::pClearValues = std::data(clear_values_);

    return *this;
}

inline auto render_pass_begin_info::add_clear_color(const float color1, const float color2, const float color3,
                                                    const float color4) -> render_pass_begin_info &
{
    VkClearColorValue value;
    value.float32[0] = color1;
    value.float32[1] = color2;
    value.float32[2] = color3;
    value.float32[3] = color4;
    return add_clear_color(value);
}

inline auto render_pass_begin_info::add_clear_color(const std::int32_t color1, const std::int32_t color2,
                                                    const std::int32_t color3, const std::int32_t color4)
    -> render_pass_begin_info &
{
    VkClearColorValue value;
    value.int32[0] = color1;
    value.int32[1] = color2;
    value.int32[2] = color3;
    value.int32[3] = color4;
    return add_clear_color(value);
}

inline auto render_pass_begin_info::add_clear_color(const std::uint32_t color1, const std::uint32_t color2,
                                                    const std::uint32_t color3, const std::uint32_t color4)
    -> render_pass_begin_info &
{
    VkClearColorValue value;
    value.uint32[0] = color1;
    value.uint32[1] = color2;
    value.uint32[2] = color3;
    value.uint32[3] = color4;
    return add_clear_color(value);
}

inline auto render_pass_begin_info::add_clear_depth_stencil(VkClearDepthStencilValue depth_stencil_clear_value)
    -> render_pass_begin_info &
{
    VkClearValue value;
    value.depthStencil = depth_stencil_clear_value;

    clear_values_.push_back(value);
    VkRenderPassBeginInfo::clearValueCount = static_cast<std::uint32_t>(std::size(clear_values_));
    VkRenderPassBeginInfo::pClearValues = std::data(clear_values_);

    return *this;
}

inline auto render_pass_begin_info::add_clear_depth_stencil(const float depth, const std::uint32_t stencil)
    -> render_pass_begin_info &
{
    return add_clear_depth_stencil(VkClearDepthStencilValue{depth, stencil});
}

inline auto render_pass_begin_info::framebuffer(const vulkan::framebuffer &framebuffer) -> render_pass_begin_info &
{
    VkRenderPassBeginInfo::framebuffer = handle(framebuffer);
    framebuffer_ = &framebuffer;
    return *this;
}

inline auto render_pass_begin_info::framebuffer() const noexcept -> const vulkan::framebuffer &
{
    return *framebuffer_;
}

static_assert(sizeof(render_pass_begin_info) >= sizeof(VkRenderPassBeginInfo));

} // namespace aeon::vulkan

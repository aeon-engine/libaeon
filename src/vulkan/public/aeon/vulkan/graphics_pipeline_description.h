// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/pipeline_shader_stage.h>
#include <aeon/vulkan/pipeline_vertex_input_state_description.h>
#include <aeon/vulkan/pipeline_input_assembly_state_description.h>
#include <aeon/vulkan/pipeline_tesselation_state_description.h>
#include <aeon/vulkan/pipeline_viewport_state_description.h>
#include <aeon/vulkan/pipeline_rasterization_state_description.h>
#include <aeon/vulkan/pipeline_multisample_state_description.h>
#include <aeon/vulkan/pipeline_depth_stencil_state_description.h>
#include <aeon/vulkan/pipeline_color_blend_state_description.h>
#include <aeon/vulkan/pipeline_dynamic_state_description.h>
#include <aeon/vulkan/pipeline_layout.h>
#include <aeon/vulkan/render_pass.h>
#include <aeon/vulkan/flags.h>
#include <vector>

namespace aeon::vulkan
{

class graphics_pipeline_description final
{
public:
    explicit graphics_pipeline_description(
        const vulkan::pipeline_layout &layout, const vulkan::render_pass &render_pass, const std::uint32_t subpass = 0,
        const common::flags<pipeline_create_flag> flags = pipeline_create_flag::none) noexcept;
    ~graphics_pipeline_description() = default;

    graphics_pipeline_description(const graphics_pipeline_description &) = default;
    auto operator=(const graphics_pipeline_description &) -> graphics_pipeline_description & = default;

    graphics_pipeline_description(graphics_pipeline_description &&) noexcept = default;
    auto operator=(graphics_pipeline_description &&) noexcept -> graphics_pipeline_description & = default;

    auto set_flags(const common::flags<pipeline_create_flag> flags) noexcept -> graphics_pipeline_description &;
    [[nodiscard]] auto flags() const noexcept -> common::flags<pipeline_create_flag>;

    auto add_shader_stage(const shader_stage stage, const shader_module &module,
                          const char *const entry_point_name = pipeline_shader_stage::default_entry_point_name)
        -> graphics_pipeline_description &;
    [[nodiscard]] auto shader_stages() const noexcept -> const std::vector<pipeline_shader_stage> &;

    [[nodiscard]] auto vertex_input_state() noexcept -> pipeline_vertex_input_state_description &;
    [[nodiscard]] auto vertex_input_state() const noexcept -> const pipeline_vertex_input_state_description &;

    [[nodiscard]] auto input_assembly_state() noexcept -> pipeline_input_assembly_state_description &;
    [[nodiscard]] auto input_assembly_state() const noexcept -> const pipeline_input_assembly_state_description &;

    [[nodiscard]] auto tesselation_state() noexcept -> pipeline_tesselation_state_description &;
    [[nodiscard]] auto tesselation_state() const noexcept -> const pipeline_tesselation_state_description &;

    [[nodiscard]] auto viewport_state() noexcept -> pipeline_viewport_state_description &;
    [[nodiscard]] auto viewport_state() const noexcept -> const pipeline_viewport_state_description &;

    [[nodiscard]] auto rasterization_state() noexcept -> pipeline_rasterization_state_description &;
    [[nodiscard]] auto rasterization_state() const noexcept -> const pipeline_rasterization_state_description &;

    [[nodiscard]] auto multisample_state() noexcept -> pipeline_multisample_state_description &;
    [[nodiscard]] auto multisample_state() const noexcept -> const pipeline_multisample_state_description &;

    [[nodiscard]] auto depth_stencil_state() noexcept -> pipeline_depth_stencil_state_description &;
    [[nodiscard]] auto depth_stencil_state() const noexcept -> const pipeline_depth_stencil_state_description &;

    [[nodiscard]] auto color_blend_state() noexcept -> pipeline_color_blend_state_description &;
    [[nodiscard]] auto color_blend_state() const noexcept -> const pipeline_color_blend_state_description &;

    [[nodiscard]] auto dynamic_state() noexcept -> pipeline_dynamic_state_description &;
    [[nodiscard]] auto dynamic_state() const noexcept -> const pipeline_dynamic_state_description &;

    [[nodiscard]] auto pipeline_layout() const noexcept -> const pipeline_layout &;
    [[nodiscard]] auto render_pass() const noexcept -> const render_pass &;
    [[nodiscard]] auto subpass() const noexcept -> std::uint32_t;

private:
    common::flags<pipeline_create_flag> flags_;
    std::vector<pipeline_shader_stage> shader_stages_;
    pipeline_vertex_input_state_description vertex_input_state_;
    pipeline_input_assembly_state_description input_assembly_state_;
    pipeline_tesselation_state_description tesselation_state_;
    pipeline_viewport_state_description viewport_state_;
    pipeline_rasterization_state_description rasterization_state_;
    pipeline_multisample_state_description multisample_state_;
    pipeline_depth_stencil_state_description depth_stencil_state_;
    pipeline_color_blend_state_description color_blend_state_;
    pipeline_dynamic_state_description dynamic_state_;
    const vulkan::pipeline_layout *layout_;
    const vulkan::render_pass *render_pass_;
    std::uint32_t subpass_;
};

inline graphics_pipeline_description::graphics_pipeline_description(
    const vulkan::pipeline_layout &layout, const vulkan::render_pass &render_pass, const std::uint32_t subpass,
    const common::flags<pipeline_create_flag> flags) noexcept
    : flags_{flags}
    , layout_{&layout}
    , render_pass_{&render_pass}
    , subpass_{subpass}
{
}

inline auto graphics_pipeline_description::set_flags(const common::flags<pipeline_create_flag> flags) noexcept
    -> graphics_pipeline_description &
{
    flags_ = flags;
    return *this;
}

inline auto graphics_pipeline_description::flags() const noexcept -> common::flags<pipeline_create_flag>
{
    return flags_;
}

inline auto graphics_pipeline_description::add_shader_stage(const shader_stage stage, const shader_module &module,
                                                            const char *const entry_point_name)
    -> graphics_pipeline_description &
{
    shader_stages_.emplace_back(stage, module, entry_point_name);
    return *this;
}

inline auto graphics_pipeline_description::shader_stages() const noexcept -> const std::vector<pipeline_shader_stage> &
{
    return shader_stages_;
}

inline auto graphics_pipeline_description::vertex_input_state() noexcept -> pipeline_vertex_input_state_description &
{
    return vertex_input_state_;
}

inline auto graphics_pipeline_description::vertex_input_state() const noexcept
    -> const pipeline_vertex_input_state_description &
{
    return vertex_input_state_;
}

inline auto graphics_pipeline_description::input_assembly_state() noexcept
    -> pipeline_input_assembly_state_description &
{
    return input_assembly_state_;
}

inline auto graphics_pipeline_description::input_assembly_state() const noexcept
    -> const pipeline_input_assembly_state_description &
{
    return input_assembly_state_;
}

inline auto graphics_pipeline_description::tesselation_state() noexcept -> pipeline_tesselation_state_description &
{
    return tesselation_state_;
}

inline auto graphics_pipeline_description::tesselation_state() const noexcept
    -> const pipeline_tesselation_state_description &
{
    return tesselation_state_;
}

inline auto graphics_pipeline_description::viewport_state() noexcept -> pipeline_viewport_state_description &
{
    return viewport_state_;
}

inline auto graphics_pipeline_description::viewport_state() const noexcept
    -> const pipeline_viewport_state_description &
{
    return viewport_state_;
}

inline auto graphics_pipeline_description::rasterization_state() noexcept -> pipeline_rasterization_state_description &
{
    return rasterization_state_;
}

inline auto graphics_pipeline_description::rasterization_state() const noexcept
    -> const pipeline_rasterization_state_description &
{
    return rasterization_state_;
}

inline auto graphics_pipeline_description::multisample_state() noexcept -> pipeline_multisample_state_description &
{
    return multisample_state_;
}

inline auto graphics_pipeline_description::multisample_state() const noexcept
    -> const pipeline_multisample_state_description &
{
    return multisample_state_;
}

inline auto graphics_pipeline_description::depth_stencil_state() noexcept -> pipeline_depth_stencil_state_description &
{
    return depth_stencil_state_;
}

inline auto graphics_pipeline_description::depth_stencil_state() const noexcept
    -> const pipeline_depth_stencil_state_description &
{
    return depth_stencil_state_;
}

inline auto graphics_pipeline_description::color_blend_state() noexcept -> pipeline_color_blend_state_description &
{
    return color_blend_state_;
}

inline auto graphics_pipeline_description::color_blend_state() const noexcept
    -> const pipeline_color_blend_state_description &
{
    return color_blend_state_;
}

inline auto graphics_pipeline_description::dynamic_state() noexcept -> pipeline_dynamic_state_description &
{
    return dynamic_state_;
}

inline auto graphics_pipeline_description::dynamic_state() const noexcept -> const pipeline_dynamic_state_description &
{
    return dynamic_state_;
}

inline auto graphics_pipeline_description::pipeline_layout() const noexcept -> const vulkan::pipeline_layout &
{
    return *layout_;
}

inline auto graphics_pipeline_description::render_pass() const noexcept -> const vulkan::render_pass &
{
    return *render_pass_;
}

inline auto graphics_pipeline_description::subpass() const noexcept -> std::uint32_t
{
    return subpass_;
}

} // namespace aeon::vulkan

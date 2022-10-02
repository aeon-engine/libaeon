// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/shader_module.h>

namespace aeon::vulkan
{

class shader_module;

class pipeline_shader_stage final : public VkPipelineShaderStageCreateInfo
{
public:
    static constexpr auto default_entry_point_name = "main";

    explicit pipeline_shader_stage(const shader_stage stage, const shader_module &module,
                                   const char *const entry_point_name = default_entry_point_name) noexcept;
    ~pipeline_shader_stage() noexcept = default;

    pipeline_shader_stage(const pipeline_shader_stage &) noexcept = default;
    auto operator=(const pipeline_shader_stage &) noexcept -> pipeline_shader_stage & = default;

    pipeline_shader_stage(pipeline_shader_stage &&) noexcept = default;
    auto operator=(pipeline_shader_stage &&) noexcept -> pipeline_shader_stage & = default;
};

static_assert(sizeof(pipeline_shader_stage) == sizeof(VkPipelineShaderStageCreateInfo));

inline pipeline_shader_stage::pipeline_shader_stage(const shader_stage stage, const shader_module &module,
                                                    const char *const entry_point_name) noexcept
    : VkPipelineShaderStageCreateInfo{VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                                      nullptr,
                                      0,
                                      static_cast<VkShaderStageFlagBits>(stage),
                                      vulkan::handle(module),
                                      entry_point_name,
                                      nullptr}
{
}

} // namespace aeon::vulkan

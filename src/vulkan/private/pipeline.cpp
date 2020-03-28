// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/pipeline.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/checked_result.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_graphics_pipeline(const vulkan::device &device,
                                            const graphics_pipeline_description &description)
{
    VkGraphicsPipelineCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

    const auto &stages = description.shader_stages();

    if (!std::empty(stages))
    {
        info.stageCount = static_cast<std::uint32_t>(std::size(stages));
        info.pStages = std::data(stages);
    }

    info.pVertexInputState = &description.vertex_input_state();
    info.pInputAssemblyState = &description.input_assembly_state();
    info.pTessellationState = &description.tesselation_state();
    info.pViewportState = &description.viewport_state();
    info.pRasterizationState = &description.rasterization_state();
    info.pMultisampleState = &description.multisample_state();
    info.pDepthStencilState = &description.depth_stencil_state();
    info.pColorBlendState = &description.color_blend_state();
    info.pDynamicState = &description.dynamic_state();
    info.layout = handle(description.pipeline_layout());
    info.renderPass = handle(description.render_pass());
    info.subpass = description.subpass();

    VkPipeline handle{};
    checked_result{vkCreateGraphicsPipelines(vulkan::handle(device), nullptr, 1, &info, nullptr, &handle)};
    return handle;
}

} // namespace internal

pipeline::pipeline() noexcept
    : device_{nullptr}
    , handle_{nullptr}
{
}

pipeline::pipeline(const vulkan::device &device, const graphics_pipeline_description &description)
    : device_{&device}
    , handle_{internal::create_graphics_pipeline(device, description)}
{
}

pipeline::~pipeline() noexcept
{
    destroy();
}

pipeline::pipeline(pipeline &&other) noexcept
    : device_{other.device_}
    , handle_{other.handle_}
{
    other.handle_ = nullptr;
}

auto pipeline::operator=(pipeline &&other) noexcept -> pipeline &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        handle_ = other.handle_;

        other.handle_ = nullptr;
    }

    return *this;
}

auto pipeline::device() const noexcept -> const vulkan::device &
{
    return *device_;
}

auto pipeline::handle() const noexcept -> VkPipeline
{
    return handle_;
}

void pipeline::destroy() const noexcept
{
    if (handle_)
        vkDestroyPipeline(vulkan::handle(device_), handle_, nullptr);
}

} // namespace aeon::vulkan

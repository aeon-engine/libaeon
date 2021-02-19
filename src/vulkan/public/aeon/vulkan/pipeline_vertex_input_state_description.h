// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/format.h>
#include <aeon/vulkan/enums.h>
#include <vector>

namespace aeon::vulkan
{

class pipeline_vertex_input_state_description final : public VkPipelineVertexInputStateCreateInfo
{
public:
    pipeline_vertex_input_state_description() noexcept;
    ~pipeline_vertex_input_state_description() noexcept = default;

    pipeline_vertex_input_state_description(const pipeline_vertex_input_state_description &other);
    auto operator=(const pipeline_vertex_input_state_description &other) -> pipeline_vertex_input_state_description &;

    pipeline_vertex_input_state_description(pipeline_vertex_input_state_description &&) noexcept = default;
    auto operator=(pipeline_vertex_input_state_description &&) noexcept
        -> pipeline_vertex_input_state_description & = default;

    auto add_binding(const std::uint32_t binding, const std::uint32_t stride,
                     const vertex_input_rate input_rate = vertex_input_rate::vertex)
        -> pipeline_vertex_input_state_description &;
    auto add_binding(const VkVertexInputBindingDescription binding_description)
        -> pipeline_vertex_input_state_description &;

    auto add_attribute(const std::uint32_t location, const std::uint32_t binding, const format format,
                       const std::uint32_t offset) -> pipeline_vertex_input_state_description &;
    auto add_attribute(const std::uint32_t location, const std::uint32_t binding, const VkFormat format,
                       const std::uint32_t offset) -> pipeline_vertex_input_state_description &;
    auto add_attribute(const VkVertexInputAttributeDescription attribute) -> pipeline_vertex_input_state_description &;

private:
    std::vector<VkVertexInputBindingDescription> bindings_;
    std::vector<VkVertexInputAttributeDescription> attributes_;
};

static_assert(sizeof(pipeline_vertex_input_state_description) >= sizeof(VkPipelineVertexInputStateCreateInfo));

inline pipeline_vertex_input_state_description::pipeline_vertex_input_state_description() noexcept
    : VkPipelineVertexInputStateCreateInfo{
          VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, nullptr, 0, 0, nullptr, 0, nullptr}
{
}

inline pipeline_vertex_input_state_description::pipeline_vertex_input_state_description(
    const pipeline_vertex_input_state_description &other)
    : VkPipelineVertexInputStateCreateInfo{other}
    , bindings_{other.bindings_}
    , attributes_{other.attributes_}
{
    if (!std::empty(bindings_))
    {
        vertexBindingDescriptionCount = static_cast<std::uint32_t>(std::size(bindings_));
        pVertexBindingDescriptions = std::data(bindings_);
    }

    if (!std::empty(attributes_))
    {
        vertexAttributeDescriptionCount = static_cast<std::uint32_t>(std::size(attributes_));
        pVertexAttributeDescriptions = std::data(attributes_);
    }
}

inline auto pipeline_vertex_input_state_description::operator=(const pipeline_vertex_input_state_description &other)
    -> pipeline_vertex_input_state_description &
{
    if (this == &other) [[unlikely]]
        return *this;

    sType = other.sType;
    pNext = other.pNext;
    flags = other.flags;

    bindings_ = other.bindings_;
    if (!std::empty(bindings_))
    {
        vertexBindingDescriptionCount = static_cast<std::uint32_t>(std::size(bindings_));
        pVertexBindingDescriptions = std::data(bindings_);
    }
    else
    {
        vertexBindingDescriptionCount = 0;
        pVertexBindingDescriptions = nullptr;
    }

    attributes_ = other.attributes_;
    if (!std::empty(attributes_))
    {
        vertexAttributeDescriptionCount = static_cast<std::uint32_t>(std::size(attributes_));
        pVertexAttributeDescriptions = std::data(attributes_);
    }
    else
    {
        vertexAttributeDescriptionCount = 0;
        pVertexAttributeDescriptions = nullptr;
    }

    return *this;
}

inline auto pipeline_vertex_input_state_description::add_binding(const std::uint32_t binding,
                                                                 const std::uint32_t stride,
                                                                 const vertex_input_rate input_rate)
    -> pipeline_vertex_input_state_description &
{
    return add_binding(VkVertexInputBindingDescription{binding, stride, static_cast<VkVertexInputRate>(input_rate)});
}

inline auto
    pipeline_vertex_input_state_description::add_binding(const VkVertexInputBindingDescription binding_description)
        -> pipeline_vertex_input_state_description &
{
    bindings_.push_back(binding_description);
    vertexBindingDescriptionCount = static_cast<std::uint32_t>(std::size(bindings_));
    pVertexBindingDescriptions = std::data(bindings_);
    return *this;
}

inline auto pipeline_vertex_input_state_description::add_attribute(const std::uint32_t location,
                                                                   const std::uint32_t binding, const format format,
                                                                   const std::uint32_t offset)
    -> pipeline_vertex_input_state_description &
{
    return add_attribute(location, binding, static_cast<VkFormat>(format), offset);
}

inline auto pipeline_vertex_input_state_description::add_attribute(const std::uint32_t location,
                                                                   const std::uint32_t binding, const VkFormat format,
                                                                   const std::uint32_t offset)
    -> pipeline_vertex_input_state_description &
{
    return add_attribute(VkVertexInputAttributeDescription{location, binding, format, offset});
}

inline auto pipeline_vertex_input_state_description::add_attribute(const VkVertexInputAttributeDescription attribute)
    -> pipeline_vertex_input_state_description &
{
    attributes_.push_back(attribute);
    vertexAttributeDescriptionCount = static_cast<std::uint32_t>(std::size(attributes_));
    pVertexAttributeDescriptions = std::data(attributes_);
    return *this;
}

} // namespace aeon::vulkan

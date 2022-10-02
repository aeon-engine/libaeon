// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/descriptor_set_layout_ref.h>
#include <aeon/vulkan/flags.h>
#include <vector>

namespace aeon::vulkan
{

class pipeline_layout_description final
{
public:
    pipeline_layout_description() noexcept;
    explicit pipeline_layout_description(std::vector<VkDescriptorSetLayout> set_layouts) noexcept;
    explicit pipeline_layout_description(std::vector<VkDescriptorSetLayout> set_layouts,
                                         std::vector<VkPushConstantRange> push_constant_ranges) noexcept;
    ~pipeline_layout_description() noexcept = default;

    pipeline_layout_description(const pipeline_layout_description &) = default;
    auto operator=(const pipeline_layout_description &) -> pipeline_layout_description & = default;

    pipeline_layout_description(pipeline_layout_description &&) noexcept = default;
    auto operator=(pipeline_layout_description &&) noexcept -> pipeline_layout_description & = default;

    auto add_set_layout(const descriptor_set_layout_ref &layout) -> pipeline_layout_description &;
    [[nodiscard]] auto has_set_layouts() const noexcept -> bool;
    [[nodiscard]] auto set_layout_count() const noexcept -> std::uint32_t;
    [[nodiscard]] auto set_layouts() const noexcept -> const std::vector<VkDescriptorSetLayout> &;

    auto add_push_constant_range(const common::flags<shader_stage_flag> stage_flags, const std::uint32_t offset,
                                 const std::uint32_t size) -> pipeline_layout_description &;
    auto add_push_constant_range(const VkPushConstantRange range) -> pipeline_layout_description &;

    [[nodiscard]] auto has_push_constant_ranges() const noexcept -> bool;
    [[nodiscard]] auto push_constant_range_count() const noexcept -> std::uint32_t;
    [[nodiscard]] auto push_constant_ranges() const noexcept -> const std::vector<VkPushConstantRange> &;

private:
    std::vector<VkDescriptorSetLayout> set_layouts_;
    std::vector<VkPushConstantRange> push_constant_ranges_;
};

inline pipeline_layout_description::pipeline_layout_description() noexcept
    : set_layouts_{}
    , push_constant_ranges_{}
{
}

inline pipeline_layout_description::pipeline_layout_description(std::vector<VkDescriptorSetLayout> set_layouts) noexcept
    : set_layouts_{std::move(set_layouts)}
    , push_constant_ranges_{}
{
}

inline pipeline_layout_description::pipeline_layout_description(
    std::vector<VkDescriptorSetLayout> set_layouts, std::vector<VkPushConstantRange> push_constant_ranges) noexcept
    : set_layouts_{std::move(set_layouts)}
    , push_constant_ranges_{std::move(push_constant_ranges)}
{
}

inline auto pipeline_layout_description::add_set_layout(const descriptor_set_layout_ref &layout)
    -> pipeline_layout_description &
{
    set_layouts_.push_back(handle(layout));
    return *this;
}

inline auto pipeline_layout_description::has_set_layouts() const noexcept -> bool
{
    return !std::empty(set_layouts_);
}

inline auto pipeline_layout_description::set_layout_count() const noexcept -> std::uint32_t
{
    return static_cast<std::uint32_t>(std::size(set_layouts_));
}

inline auto pipeline_layout_description::set_layouts() const noexcept -> const std::vector<VkDescriptorSetLayout> &
{
    return set_layouts_;
}

inline auto pipeline_layout_description::add_push_constant_range(const common::flags<shader_stage_flag> stage_flags,
                                                                 const std::uint32_t offset, const std::uint32_t size)
    -> pipeline_layout_description &
{
    add_push_constant_range(VkPushConstantRange{stage_flags, offset, size});
    return *this;
}

inline auto pipeline_layout_description::add_push_constant_range(const VkPushConstantRange range)
    -> pipeline_layout_description &
{
    push_constant_ranges_.push_back(range);
    return *this;
}

inline auto pipeline_layout_description::has_push_constant_ranges() const noexcept -> bool
{
    return !std::empty(push_constant_ranges_);
}

inline auto pipeline_layout_description::push_constant_range_count() const noexcept -> std::uint32_t
{
    return static_cast<std::uint32_t>(std::size(push_constant_ranges_));
}

inline auto pipeline_layout_description::push_constant_ranges() const noexcept
    -> const std::vector<VkPushConstantRange> &
{
    return push_constant_ranges_;
}

} // namespace aeon::vulkan

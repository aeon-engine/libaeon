// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/enums.h>
#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/attachment_reference.h>
#include <vector>
#include <cstdint>

namespace aeon::vulkan
{

class subpass final
{
public:
    explicit subpass(const pipeline_bind_point bind_point = pipeline_bind_point::graphics,
                     const common::flags<subpass_description_flag> flags = {}) noexcept;
    explicit subpass(std::vector<attachment_reference> color_attachments,
                     const attachment_reference depth_stencil_attachment = unused_attachment_reference,
                     std::vector<attachment_reference> input_attachments = {},
                     std::vector<attachment_reference> resolve_attachments = {},
                     std::vector<std::uint32_t> preserve_attachments = {},
                     const pipeline_bind_point bind_point = pipeline_bind_point::graphics,
                     const common::flags<subpass_description_flag> flags = {}) noexcept;

    ~subpass() = default;

    subpass(const subpass &) = default;
    auto operator=(const subpass &) -> subpass & = default;

    subpass(subpass &&) noexcept = default;
    auto operator=(subpass &&) noexcept -> subpass & = default;

    [[nodiscard]] auto bind_point() const noexcept -> pipeline_bind_point;
    [[nodiscard]] auto flags() const noexcept -> common::flags<subpass_description_flag>;

    auto set_flags(const common::flags<subpass_description_flag> flags) noexcept -> subpass &;

    auto add_color_attachment(const attachment_reference reference) -> subpass &;
    auto add_color_attachment(const std::uint32_t attachment, const image_layout layout) -> subpass &;
    auto add_color_attachment(const std::uint32_t attachment, const VkImageLayout layout) -> subpass &;
    auto add_color_attachments(const std::vector<attachment_reference> &references) -> subpass &;

    auto add_color_attachment(const attachment_reference reference, const attachment_reference resolve_reference)
        -> subpass &;
    auto add_color_attachment(const std::uint32_t attachment, const image_layout layout,
                              const std::uint32_t resolve_attachment, const image_layout resolve_layout) -> subpass &;
    auto add_color_attachment(const std::uint32_t attachment, const VkImageLayout layout,
                              const std::uint32_t resolve_attachment, const VkImageLayout resolve_layout) -> subpass &;

    [[nodiscard]] auto has_color_attachments() const noexcept -> bool;
    [[nodiscard]] auto color_attachments() const noexcept -> const std::vector<attachment_reference> &;

    auto set_depth_stencil_attachment(const attachment_reference reference) -> subpass &;
    auto set_depth_stencil_attachment(const std::uint32_t attachment, const image_layout layout) -> subpass &;
    auto set_depth_stencil_attachment(const std::uint32_t attachment, const VkImageLayout layout) -> subpass &;
    [[nodiscard]] auto has_depth_stencil_attachment() const noexcept -> bool;
    [[nodiscard]] auto depth_stencil_attachment() const noexcept -> const attachment_reference &;
    [[nodiscard]] auto depth_stencil_attachment_ptr() const noexcept -> const attachment_reference *;

    auto add_input_attachment(const attachment_reference reference) -> subpass &;
    auto add_input_attachment(const std::uint32_t attachment, const image_layout layout) -> subpass &;
    auto add_input_attachment(const std::uint32_t attachment, const VkImageLayout layout) -> subpass &;
    auto add_input_attachments(const std::vector<attachment_reference> &references) -> subpass &;
    [[nodiscard]] auto has_input_attachments() const noexcept -> bool;
    [[nodiscard]] auto input_attachments() const noexcept -> const std::vector<attachment_reference> &;

    [[nodiscard]] auto has_resolve_attachments() const noexcept -> bool;
    [[nodiscard]] auto resolve_attachments() const noexcept -> const std::vector<attachment_reference> &;

    auto add_preserve_attachment(const std::uint32_t attachment) -> subpass &;
    auto add_preserve_attachments(const std::vector<std::uint32_t> &attachments) -> subpass &;
    [[nodiscard]] auto has_preserve_attachments() const noexcept -> bool;
    [[nodiscard]] auto preserve_attachments() const noexcept -> const std::vector<std::uint32_t> &;

private:
    void add_resolve_attachment(const attachment_reference reference);

    pipeline_bind_point bind_point_;
    common::flags<subpass_description_flag> flags_;
    std::vector<attachment_reference> color_attachments_;
    attachment_reference depth_stencil_attachment_;
    std::vector<attachment_reference> input_attachments_;
    std::vector<attachment_reference> resolve_attachments_;
    std::vector<std::uint32_t> preserve_attachments_;
};

} // namespace aeon::vulkan

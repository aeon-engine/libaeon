// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/enums.h>
#include <vector>

namespace aeon::vulkan
{

class descriptor_set_layout_binding final : public VkDescriptorSetLayoutBinding
{
public:
    explicit descriptor_set_layout_binding(const descriptor_type type,
                                           const common::flags<shader_stage_flag> stage_flags,
                                           const std::uint32_t binding, const std::uint32_t count = 1);
    ~descriptor_set_layout_binding() = default;

    descriptor_set_layout_binding(const descriptor_set_layout_binding &) noexcept = default;
    auto operator=(const descriptor_set_layout_binding &) noexcept -> descriptor_set_layout_binding & = default;

    descriptor_set_layout_binding(descriptor_set_layout_binding &&) noexcept = default;
    auto operator=(descriptor_set_layout_binding &&) noexcept -> descriptor_set_layout_binding & = default;
};

inline descriptor_set_layout_binding::descriptor_set_layout_binding(const descriptor_type type,
                                                                    const common::flags<shader_stage_flag> stage_flags,
                                                                    const std::uint32_t binding,
                                                                    const std::uint32_t count)
    : VkDescriptorSetLayoutBinding{binding, static_cast<VkDescriptorType>(type), count, stage_flags, nullptr}
{
}

static_assert(sizeof(descriptor_set_layout_binding) == sizeof(VkDescriptorSetLayoutBinding));

class descriptor_set_layout_description final
{
public:
    explicit descriptor_set_layout_description(const common::flags<descriptor_set_layout_create_flag> flags =
                                                   descriptor_set_layout_create_flag::none) noexcept;

    explicit descriptor_set_layout_description(std::vector<descriptor_set_layout_binding> bindings,
                                               const common::flags<descriptor_set_layout_create_flag> flags =
                                                   descriptor_set_layout_create_flag::none) noexcept;

    ~descriptor_set_layout_description() = default;

    descriptor_set_layout_description(const descriptor_set_layout_description &) = default;
    auto operator=(const descriptor_set_layout_description &) -> descriptor_set_layout_description & = default;

    descriptor_set_layout_description(descriptor_set_layout_description &&) noexcept = default;
    auto operator=(descriptor_set_layout_description &&) noexcept -> descriptor_set_layout_description & = default;

    void add_binding(const descriptor_type type, const common::flags<shader_stage_flag> stage_flags,
                     const std::uint32_t binding, const std::uint32_t count = 1);

    [[nodiscard]] auto has_bindings() const noexcept -> bool;
    [[nodiscard]] auto binding_count() const noexcept -> std::uint32_t;
    [[nodiscard]] auto bindings() const noexcept -> const std::vector<descriptor_set_layout_binding> &;
    [[nodiscard]] auto flags() const noexcept -> common::flags<descriptor_set_layout_create_flag>;

private:
    std::vector<descriptor_set_layout_binding> bindings_;
    common::flags<descriptor_set_layout_create_flag> flags_;
};

inline descriptor_set_layout_description::descriptor_set_layout_description(
    const common::flags<descriptor_set_layout_create_flag> flags) noexcept
    : bindings_{}
    , flags_{flags}
{
}

inline descriptor_set_layout_description::descriptor_set_layout_description(
    std::vector<descriptor_set_layout_binding> bindings,
    const common::flags<descriptor_set_layout_create_flag> flags) noexcept
    : bindings_{std::move(bindings)}
    , flags_{flags}
{
}

inline void descriptor_set_layout_description::add_binding(const descriptor_type type,
                                                           const common::flags<shader_stage_flag> stage_flags,
                                                           const std::uint32_t binding, const std::uint32_t count)
{
    bindings_.emplace_back(type, stage_flags, binding, count);
}

inline auto descriptor_set_layout_description::has_bindings() const noexcept -> bool
{
    return !std::empty(bindings_);
}

inline auto descriptor_set_layout_description::binding_count() const noexcept -> std::uint32_t
{
    return static_cast<std::uint32_t>(std::size(bindings_));
}

inline auto descriptor_set_layout_description::bindings() const noexcept
    -> const std::vector<descriptor_set_layout_binding> &
{
    return bindings_;
}

inline auto descriptor_set_layout_description::flags() const noexcept
    -> common::flags<descriptor_set_layout_create_flag>
{
    return flags_;
}

} // namespace aeon::vulkan

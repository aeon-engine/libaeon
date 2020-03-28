// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/descriptor_set_layout_ref.h>

namespace aeon::vulkan
{

class descriptor_set_layout_description;

class descriptor_set_layout final : public descriptor_set_layout_ref
{
public:
    descriptor_set_layout() noexcept;
    explicit descriptor_set_layout(const device &device, const descriptor_set_layout_description &description);
    ~descriptor_set_layout();

    descriptor_set_layout(const descriptor_set_layout &) noexcept = delete;
    auto operator=(const descriptor_set_layout &) noexcept -> descriptor_set_layout & = delete;

    descriptor_set_layout(descriptor_set_layout &&other) noexcept;
    auto operator=(descriptor_set_layout &&other) noexcept -> descriptor_set_layout &;
};

} // namespace aeon::vulkan

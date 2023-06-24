// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/vulkan/application_info.h>
#include <aeon/vulkan/exception.h>
#include <aeon/vulkan/extension.h>
#include <aeon/vulkan/layer.h>
#include <aeon/vulkan/physical_device.h>
#include <aeon/common/string.h>
#include <vulkan/vulkan_core.h>
#include <vector>

namespace aeon::vulkan
{

class surface;

class instance final
{
public:
    instance() noexcept;
    explicit instance(const application_info &info);
    explicit instance(const application_info &info, const std::vector<common::string> &required_layers,
                      const std::vector<common::string> &required_extensions);
    ~instance();

    instance(const instance &) noexcept = delete;
    auto operator=(const instance &) noexcept -> instance & = delete;

    instance(instance &&other) noexcept;
    auto operator=(instance &&other) noexcept -> instance &;

    [[nodiscard]] auto handle() const noexcept -> VkInstance;

    [[nodiscard]] auto physical_devices() const noexcept -> const std::vector<physical_device> &;

    [[nodiscard]] static auto available_layers() -> std::vector<layer>;
    [[nodiscard]] static auto available_extensions() -> std::vector<extension>;

private:
    void destroy() const noexcept;

    VkInstance instance_;
    std::vector<physical_device> physical_devices_;
};

[[nodiscard]] inline auto handle(const instance &i) noexcept
{
    return i.handle();
}

[[nodiscard]] inline auto handle(const instance *i) noexcept
{
    return i->handle();
}

[[nodiscard]] inline auto find_best_device_for_gfx(const instance &i, const surface &s) -> const physical_device &
{
    const auto &physical_devices = i.physical_devices();

    if (std::empty(physical_devices))
        throw vulkan_exception{"No physical devices found."};

    const auto *best_device = &*std::begin(physical_devices);
    auto best_score = score_for_gfx(*best_device, s);

    for (const auto &device : physical_devices)
    {
        const auto score = score_for_gfx(device, s);
        if (score > best_score)
        {
            best_device = &device;
            best_score = score;
        }
    }

    if (best_score == 0)
        throw vulkan_exception{"Could not find any suitable physical device."};

    return *best_device;
}

[[nodiscard]] inline auto is_available(const std::vector<layer> &layers, const common::string &layer_name) noexcept
    -> bool
{
    for (const auto &layer : layers)
    {
        if (layer.name() == layer_name)
            return true;
    }

    return false;
}

[[nodiscard]] inline auto are_available(const std::vector<layer> &layers,
                                        const std::vector<common::string> &layer_names) noexcept -> bool
{
    for (const auto &layer_name : layer_names)
    {
        if (!is_available(layers, layer_name))
            return false;
    }

    return true;
}

[[nodiscard]] inline auto is_available(const std::vector<extension> &extensions,
                                       const common::string &extension_name) noexcept -> bool
{
    for (const auto &extension : extensions)
    {
        if (extension.name() == extension_name)
            return true;
    }

    return false;
}

[[nodiscard]] inline auto are_available(const std::vector<extension> &extensions,
                                        const std::vector<common::string> &extension_names) noexcept -> bool
{
    for (const auto &extension_name : extension_names)
    {
        if (!is_available(extensions, extension_name))
            return false;
    }

    return true;
}

} // namespace aeon::vulkan

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/streams/idynamic_stream_fwd.h>
#include <vulkan/vulkan_core.h>
#include <filesystem>
#include <vector>
#include <cstdint>

namespace aeon::vulkan
{

class device;

class shader_module final
{
public:
    shader_module() noexcept;
    explicit shader_module(const device &device, const std::filesystem::path &path);
    explicit shader_module(const device &device, streams::idynamic_stream &stream);
    explicit shader_module(const device &device, const std::vector<std::byte> &data);
    ~shader_module();

    shader_module(const shader_module &) = delete;
    auto operator=(const shader_module &) -> shader_module & = delete;

    shader_module(shader_module &&other) noexcept;
    auto operator=(shader_module &&other) noexcept -> shader_module &;

    [[nodiscard]] auto handle() const noexcept -> VkShaderModule;

private:
    void destroy() const noexcept;

    const device *device_;
    VkShaderModule shader_module_;
};

[[nodiscard]] inline auto handle(const shader_module &s) noexcept
{
    return s.handle();
}

} // namespace aeon::vulkan

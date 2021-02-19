// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/vulkan/shader_module.h>
#include <aeon/vulkan/device.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/streams/dynamic_stream.h>
#include <aeon/streams/stream_reader.h>
#include <aeon/streams/devices/file_device.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_shader_module(const device &device, const std::vector<std::byte> &data)
{
    const auto create_info = initializers::shader_module_create_info(data);

    VkShaderModule shader_module;
    checked_result{vkCreateShaderModule(handle(device), &create_info, nullptr, &shader_module)};
    return shader_module;
}

[[nodiscard]] auto create_shader_module(const device &device, streams::idynamic_stream &stream)
{
    const streams::stream_reader reader{stream};
    return create_shader_module(device, reader.read_to_vector<std::byte>());
}

[[nodiscard]] auto create_shader_module(const device &device, const std::filesystem::path &path)
{
    auto stream = streams::make_dynamic_stream(streams::file_source_device{path});
    const streams::stream_reader reader{stream};
    return create_shader_module(device, reader.read_to_vector<std::byte>());
}

} // namespace internal

shader_module::shader_module() noexcept
    : device_{nullptr}
    , shader_module_{nullptr}
{
}

shader_module::shader_module(const device &device, const std::filesystem::path &path)
    : device_{&device}
    , shader_module_{internal::create_shader_module(device, path)}
{
}

shader_module::shader_module(const device &device, streams::idynamic_stream &stream)
    : device_{&device}
    , shader_module_{internal::create_shader_module(device, stream)}
{
}

shader_module::shader_module(const device &device, const std::vector<std::byte> &data)
    : device_{&device}
    , shader_module_{internal::create_shader_module(device, data)}
{
}

shader_module::~shader_module()
{
    destroy();
}

shader_module::shader_module(shader_module &&other) noexcept
    : device_{other.device_}
    , shader_module_{other.shader_module_}
{
    other.device_ = nullptr;
    other.shader_module_ = nullptr;
}

auto shader_module::operator=(shader_module &&other) noexcept -> shader_module &
{
    if (this != &other) [[likely]]
    {
        destroy();

        device_ = other.device_;
        shader_module_ = other.shader_module_;
        other.device_ = nullptr;
        other.shader_module_ = nullptr;
    }

    return *this;
}

auto shader_module::handle() const noexcept -> VkShaderModule
{
    return shader_module_;
}

void shader_module::destroy() const noexcept
{
    if (shader_module_)
        vkDestroyShaderModule(vulkan::handle(*device_), shader_module_, nullptr);
}

} // namespace aeon::vulkan

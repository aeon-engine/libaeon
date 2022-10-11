// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/instance.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/common/container.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto enumerate_extension_properties() -> std::vector<VkExtensionProperties>
{
    std::uint32_t extension_count = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
    std::vector<VkExtensionProperties> extensions(extension_count);
    vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
    return extensions;
}

[[nodiscard]] auto enumerate_layer_properties() -> std::vector<VkLayerProperties>
{
    std::uint32_t layer_count = 0;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
    std::vector<VkLayerProperties> layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, layers.data());
    return layers;
}

[[nodiscard]] auto create_instance(const application_info &info, const std::vector<common::string> &required_layers,
                                   const std::vector<common::string> &required_extensions) -> VkInstance
{
    const auto available_extensions = instance::available_extensions();
    if (!are_available(available_extensions, required_extensions))
        throw vulkan_exception{"One or more requested extensions is not available."};

    const auto available_layers = instance::available_layers();
    if (!are_available(available_layers, required_layers))
        throw vulkan_exception{"One of more requested layers is not available."};

    const auto application_info = initializers::application_info(info.name(), info.application_version(),
                                                                 info.engine_name(), info.engine_version());

    const auto required_extensions_str =
        common::container::transform<const char *>(required_extensions, [](const auto &str) { return str.c_str(); });

    const auto required_layers_str =
        common::container::transform<const char *>(required_layers, [](const auto &str) { return str.c_str(); });

    const auto create_info =
        initializers::instance_create_info(application_info, required_extensions_str, required_layers_str);

    VkInstance instance;
    checked_result{vkCreateInstance(&create_info, nullptr, &instance)};
    return instance;
}

[[nodiscard]] auto enumerate_physical_devices(const VkInstance instance)
{
    std::uint32_t count;
    checked_result{vkEnumeratePhysicalDevices(instance, &count, nullptr)};
    std::vector<VkPhysicalDevice> physical_devices(count);
    checked_result{vkEnumeratePhysicalDevices(instance, &count, physical_devices.data())};

    return physical_devices;
}

} // namespace internal

instance::instance() noexcept
    : instance_{nullptr}
    , physical_devices_{}
{
}

instance::instance(const application_info &info)
    : instance{info, {}, {}}
{
}

instance::instance(const application_info &info, const std::vector<common::string> &required_layers,
                   const std::vector<common::string> &required_extensions)
    : instance_{internal::create_instance(info, required_layers, required_extensions)}
    , physical_devices_{common::container::transform<physical_device>(internal::enumerate_physical_devices(instance_),
                                                                      [this](const auto &device) {
                                                                          return physical_device{instance_, device};
                                                                      })}
{
}

instance::~instance()
{
    destroy();
}

instance::instance(instance &&other) noexcept
    : instance_{other.instance_}
    , physical_devices_{std::move(other.physical_devices_)}
{
    other.instance_ = nullptr;
}

auto instance::operator=(instance &&other) noexcept -> instance &
{
    if (this != &other) [[likely]]
    {
        destroy();

        instance_ = other.instance_;
        physical_devices_ = std::move(other.physical_devices_);
        other.instance_ = nullptr;
    }

    return *this;
}

auto instance::handle() const noexcept -> VkInstance
{
    return instance_;
}

auto instance::physical_devices() const noexcept -> const std::vector<physical_device> &
{
    return physical_devices_;
}

auto instance::available_layers() -> std::vector<layer>
{
    return common::container::auto_transform<layer>(internal::enumerate_layer_properties());
}

auto instance::available_extensions() -> std::vector<extension>
{
    return common::container::auto_transform<extension>(internal::enumerate_extension_properties());
}

void instance::destroy() const noexcept
{
    if (instance_)
        vkDestroyInstance(instance_, nullptr);
}

} // namespace aeon::vulkan

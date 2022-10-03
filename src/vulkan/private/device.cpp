// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#include <aeon/vulkan/device.h>
#include <aeon/vulkan/physical_device.h>
#include <aeon/vulkan/surface.h>
#include <aeon/vulkan/debug.h>
#include <aeon/vulkan/initializers.h>
#include <aeon/vulkan/checked_result.h>
#include <aeon/vulkan/instance.h>
#include <aeon/common/container.h>
#include <aeon/common/assert.h>

namespace aeon::vulkan
{

namespace internal
{

[[nodiscard]] auto create_device(const physical_device &device, const std::vector<std::string> &enabled_layers,
                                 const std::vector<std::string> &required_extensions,
                                 const VkPhysicalDeviceFeatures &required_features, const queue_indices &indices)
{
    const auto available_extensions = device.extensions();
    const auto required_extensions_str =
        common::container::transform<const char *>(required_extensions, [](const auto &str) { return str.c_str(); });

    // TODO: Check extension availability.
    (void)available_extensions;

    const auto enabled_layers_str =
        common::container::transform<const char *>(enabled_layers, [](const auto &str) { return str.c_str(); });

    auto priority = 0.0f;
    const auto queue_create_info_collection = indices.get_queue_create_info_collection(priority);
    const auto create_info = initializers::device_create_info(enabled_layers_str, required_extensions_str,
                                                              queue_create_info_collection, required_features);

    VkDevice handle = nullptr;
    checked_result{vkCreateDevice(vulkan::handle(device), &create_info, nullptr, &handle)};
    return handle;
}

[[nodiscard]] auto create_allocator(const physical_device &physical_device, const VkDevice device)
{
    VmaAllocatorCreateInfo info{};
    info.physicalDevice = vulkan::handle(physical_device);
    info.device = device;
    info.instance = physical_device.instance_handle();
    info.vulkanApiVersion = AEON_VULKAN_API_VERSION;

    const auto &extensions = physical_device.extensions();

    for (const auto &extension : extensions)
    {
        if constexpr (AEON_VULKAN_API_VERSION == VK_API_VERSION_1_0)
        {
            if (extension.name() == VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME)
                info.flags |= VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT;

            if (extension.name() == VK_KHR_BIND_MEMORY_2_EXTENSION_NAME)
                info.flags |= VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT;
        }

        if constexpr (AEON_VULKAN_API_VERSION < VK_API_VERSION_1_2)
        {
            if (extension.name() == VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME)
                info.flags |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;
        }

        if (extension.name() == VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME)
            info.flags |= VMA_ALLOCATOR_CREATE_AMD_DEVICE_COHERENT_MEMORY_BIT;
    }

    if constexpr (AEON_VULKAN_API_VERSION >= VK_API_VERSION_1_2)
        info.flags |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;

    VmaAllocator allocator = nullptr;
    checked_result{vmaCreateAllocator(&info, &allocator)};
    return allocator;
}

} // namespace internal

device::device() noexcept
    : physical_device_{nullptr}
    , queue_indices_{}
    , device_{nullptr}
    , allocator_{nullptr}
{
}

device::device(const vulkan::physical_device &d, const surface &surface, const std::vector<std::string> &layers,
               const std::vector<std::string> &extensions, const VkPhysicalDeviceFeatures &features)
    : physical_device_{&d}
    , queue_indices_{d, surface}
    , device_{internal::create_device(d, layers, extensions, features, queue_indices_)}
    , allocator_{internal::create_allocator(d, device_)}
    , graphics_queue_{*this, queue_indices_.graphics_queue_index()}
    , present_queue_{*this, queue_indices_.present_queue_index()}
    , transfer_queue_{*this, queue_indices_.transfer_queue_index()}
{
}

device::~device()
{
    destroy();
}

device::device(device &&other) noexcept
    : physical_device_{other.physical_device_}
    , queue_indices_{other.queue_indices_}
    , device_{other.device_}
    , allocator_{other.allocator_}
    , graphics_queue_{other.graphics_queue_}
    , present_queue_{other.present_queue_}
    , transfer_queue_{other.transfer_queue_}

{
    other.device_ = nullptr;
    other.allocator_ = nullptr;
}

auto device::operator=(device &&other) noexcept -> device &
{
    if (this != &other) [[likely]]
    {
        destroy();

        physical_device_ = other.physical_device_;
        queue_indices_ = other.queue_indices_;
        device_ = other.device_;
        allocator_ = other.allocator_;
        graphics_queue_ = other.graphics_queue_;
        present_queue_ = other.present_queue_;
        transfer_queue_ = other.transfer_queue_;
        other.device_ = nullptr;
        other.allocator_ = nullptr;
    }

    return *this;
}

auto device::handle() const noexcept -> VkDevice
{
    aeon_assert(device_, "Device is null");
    return device_;
}

auto device::physical_device() const noexcept -> const vulkan::physical_device &
{
    aeon_assert(physical_device_, "Physical device is null");
    return *physical_device_;
}

auto device::get_queue_indices() const noexcept -> const queue_indices &
{
    return queue_indices_;
}

auto device::allocator_handle() const noexcept -> VmaAllocator
{
    return allocator_;
}

void device::wait_idle() const
{
    checked_result{vkDeviceWaitIdle(device_)};
}

void device::destroy() const noexcept
{
    if (allocator_)
        vmaDestroyAllocator(allocator_);

    if (device_)
        vkDestroyDevice(device_, nullptr);
}

} // namespace aeon::vulkan

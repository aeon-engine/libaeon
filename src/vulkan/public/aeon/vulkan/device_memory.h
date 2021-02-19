// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <vulkan/vulkan_core.h>
#include <vector>
#include <cstring>
#include <cstdint>

namespace aeon::vulkan
{

class device;
class scoped_memory_map;

class device_memory
{
public:
    device_memory() noexcept;
    explicit device_memory(const device &dev, const VkMemoryRequirements &requirements,
                           const common::flags<memory_flag> flags);
    explicit device_memory(const device &dev, const VkDeviceSize size, const std::uint32_t required_memory_type_bits,
                           const common::flags<memory_flag> flags);
    explicit device_memory(const device &dev, const VkDeviceSize size, const std::uint32_t type_index);
    ~device_memory() noexcept;

    device_memory(const device_memory &) noexcept = delete;
    auto operator=(const device_memory &) noexcept -> device_memory & = delete;

    device_memory(device_memory &&other) noexcept;
    auto operator=(device_memory &&other) noexcept -> device_memory &;

    [[nodiscard]] auto handle() const noexcept -> VkDeviceMemory;
    [[nodiscard]] auto size() const noexcept -> VkDeviceSize;
    [[nodiscard]] auto type_index() const noexcept -> std::uint32_t;

    [[nodiscard]] auto scope_map(const VkDeviceSize offset = 0) const -> scoped_memory_map;
    [[nodiscard]] auto scope_map(const VkDeviceSize offset, const VkDeviceSize size) const -> scoped_memory_map;

    void map(const VkDeviceSize offset, const VkDeviceSize size, void **data) const;
    void unmap() const;

private:
    VkDevice device_;

    std::uint32_t type_index_;
    VkDeviceSize size_;

    VkDeviceMemory handle_;
};

class scoped_memory_map final
{
public:
    explicit scoped_memory_map(const device_memory &memory, const VkDeviceSize offset, const VkDeviceSize size)
        : memory_{memory}
        , mapped_{nullptr}
    {
        memory_.map(offset, size, &mapped_);
    }

    ~scoped_memory_map()
    {
        memory_.unmap();
    }

    scoped_memory_map(const scoped_memory_map &) noexcept = delete;
    auto operator=(const scoped_memory_map &) noexcept -> scoped_memory_map & = delete;

    scoped_memory_map(scoped_memory_map &&other) noexcept = delete;
    auto operator=(scoped_memory_map &&other) noexcept -> scoped_memory_map & = delete;

    [[nodiscard]] auto data() const noexcept
    {
        return mapped_;
    }

    void copy(const std::byte *data, const VkDeviceSize size) const
    {
        std::memcpy(mapped_, data, static_cast<std::size_t>(size));
    }

private:
    const device_memory &memory_;
    void *mapped_;
};

[[nodiscard]] inline auto handle(const device_memory &m) noexcept
{
    return m.handle();
}

[[nodiscard]] inline auto make_staging_memory(const device &dev, const VkDeviceSize size,
                                              const std::uint32_t required_memory_type_bits)
{
    return device_memory{dev, size, required_memory_type_bits,
                         vulkan::memory_flag::host_visible | vulkan::memory_flag::host_coherent};
}

[[nodiscard]] inline auto make_staging_memory(const device &dev, const VkMemoryRequirements &requirements)
{
    return make_staging_memory(dev, requirements.size, requirements.memoryTypeBits);
}

inline void copy(const device_memory &destination, const std::byte *data, const std::size_t size)
{
    const auto mapped = destination.scope_map();
    mapped.copy(data, size);
}

template <typename T>
inline void copy(const device_memory &destination, const std::vector<T> &data)
{
    copy(destination, reinterpret_cast<const std::byte *>(std::data(data)), std::size(data) * sizeof(T));
}

} // namespace aeon::vulkan

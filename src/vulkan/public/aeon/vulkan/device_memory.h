// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/flags.h>
#include <aeon/vulkan/vma/vma.h>
#include <aeon/imaging/image_view.h>
#include <vulkan/vulkan_core.h>
#include <span>
#include <vector>
#include <cstring>

namespace aeon::vulkan
{

class device;
class scoped_memory_map;

class device_memory
{
public:
    device_memory(const device_memory &) noexcept = delete;
    auto operator=(const device_memory &) noexcept -> device_memory & = delete;

    device_memory(device_memory &&) noexcept = default;
    auto operator=(device_memory &&) noexcept -> device_memory & = default;

    [[nodiscard]] auto device() const noexcept -> const device &;
    [[nodiscard]] auto size() const noexcept -> VkDeviceSize;

    [[nodiscard]] auto scope_map() const -> scoped_memory_map;

    void map(void **data) const;
    void unmap() const;

protected:
    device_memory() noexcept;
    explicit device_memory(const vulkan::device &dev) noexcept;
    explicit device_memory(const vulkan::device &dev, const VkDeviceSize size) noexcept;
    ~device_memory() noexcept = default;

    VmaAllocation allocation_;
    const vulkan::device *device_;
    VkDeviceSize size_;
};

class scoped_memory_map final
{
public:
    explicit scoped_memory_map(const device_memory &memory)
        : memory_{memory}
        , mapped_{nullptr}
    {
        memory_.map(&mapped_);
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

inline void copy(const device_memory &destination, const std::byte *data, const std::size_t size)
{
    const auto mapped = destination.scope_map();
    mapped.copy(data, size);
}

template <typename T>
inline void copy(const device_memory &destination, const std::span<const T> &data)
{
    copy(destination, reinterpret_cast<const std::byte *>(std::data(data)), std::size(data) * sizeof(T));
}

template <typename T>
inline void copy(const device_memory &destination, const std::vector<T> &data)
{
    copy(destination, std::span<const T>{data});
}

inline void copy(const device_memory &destination, const imaging::image_view &image)
{
    copy(destination, std::data(image), std::size(image));
}

} // namespace aeon::vulkan

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <vulkan/vulkan_core.h>
#include <limits>
#include <vector>
#include <cstdint>

namespace aeon::vulkan
{

class surface;
class physical_device;

class queue_indices final
{
public:
    static constexpr auto invalid_queue_index = std::numeric_limits<std::uint32_t>::max();

    queue_indices() noexcept
        : graphics_queue_index_{invalid_queue_index}
        , present_queue_index_{invalid_queue_index}
        , transfer_queue_index_{invalid_queue_index}
    {
    }

    explicit queue_indices(const physical_device &device, const surface &surface);

    ~queue_indices() noexcept = default;

    queue_indices(const queue_indices &) noexcept = default;
    auto operator=(const queue_indices &) noexcept -> queue_indices & = default;

    queue_indices(queue_indices &&) noexcept = default;
    auto operator=(queue_indices &&) noexcept -> queue_indices & = default;

    void set_graphics_queue_index(const std::uint32_t index) noexcept
    {
        graphics_queue_index_ = index;
    }

    [[nodiscard]] auto has_graphics_queue_index() const noexcept
    {
        return graphics_queue_index_ != invalid_queue_index;
    }

    [[nodiscard]] auto graphics_queue_index() const noexcept
    {
        aeon_assert(has_graphics_queue_index(), "Device does not have a graphics queue.");
        return graphics_queue_index_;
    }

    void set_present_queue_index(const std::uint32_t index) noexcept
    {
        present_queue_index_ = index;
    }

    [[nodiscard]] auto has_present_queue_index() const noexcept
    {
        return present_queue_index_ != invalid_queue_index;
    }

    [[nodiscard]] auto present_queue_index() const noexcept
    {
        aeon_assert(has_present_queue_index(), "Device does not have a present queue.");
        return present_queue_index_;
    }

    /*!
     * Returns true if the graphics and present queue are separate.
     */
    [[nodiscard]] auto has_dedicated_present_queue_index() const noexcept
    {
        return graphics_queue_index() != present_queue_index();
    }

    void set_transfer_queue_index(const std::uint32_t index) noexcept
    {
        transfer_queue_index_ = index;
    }

    /*!
     * Returns true if the device has a dedicated transfer queue
     */
    [[nodiscard]] auto has_dedicated_transfer_queue_index() const noexcept
    {
        return transfer_queue_index_ != invalid_queue_index;
    }

    /*!
     * Returns true if the device has any queue suitable for transfer
     */
    [[nodiscard]] auto has_transfer_queue_index() const noexcept
    {
        return has_dedicated_transfer_queue_index() || has_graphics_queue_index();
    }

    [[nodiscard]] auto transfer_queue_index() const noexcept
    {
        aeon_assert(has_transfer_queue_index(), "Device does not have a transfer queue.");

        if (has_dedicated_transfer_queue_index())
            return transfer_queue_index_;

        // If there isn't a dedicated transfer queue, use the graphics queue instead
        return graphics_queue_index();
    }

    /*!
     * Get a collection of VkDeviceQueueCreateInfo based on the found queue indices for use with VkDeviceCreateInfo.
     */
    [[nodiscard]] auto get_queue_create_info_collection(float &priority) const -> std::vector<VkDeviceQueueCreateInfo>;

    /*!
     * Get a collection of queue indices for the swap chain
     */
    [[nodiscard]] auto get_swap_chain_queue_indices() const -> std::vector<std::uint32_t>;

private:
    std::uint32_t graphics_queue_index_;
    std::uint32_t present_queue_index_;
    std::uint32_t transfer_queue_index_;
};

} // namespace aeon::vulkan

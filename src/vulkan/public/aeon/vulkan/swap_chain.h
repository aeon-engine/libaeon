// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/vulkan/image_view.h>
#include <aeon/math/size2d.h>
#include <vulkan/vulkan_core.h>
#include <chrono>
#include <vector>

namespace aeon::vulkan
{

class device;
class framebuffer;
class physical_device;
class queue;
class render_pass;
class semaphore_ref;
class surface;

class swap_chain final
{
public:
    swap_chain() noexcept;
    explicit swap_chain(const vulkan::device &device, const surface &surface,
                        const VkSurfaceFormatKHR preferred_surface_format,
                        const math::size2d<std::uint32_t> preferred_extent);
    ~swap_chain();

    swap_chain(const swap_chain &) = delete;
    auto operator=(const swap_chain &) -> swap_chain & = delete;

    swap_chain(swap_chain &&other) noexcept;
    auto operator=(swap_chain &&other) noexcept -> swap_chain &;

    [[nodiscard]] auto handle() const noexcept -> VkSwapchainKHR;
    [[nodiscard]] auto handle_ptr() const noexcept -> const VkSwapchainKHR *;

    [[nodiscard]] auto format() const noexcept -> VkFormat;

    [[nodiscard]] auto surface_format() const noexcept -> VkSurfaceFormatKHR;

    [[nodiscard]] auto image_count() const noexcept -> std::uint32_t;

    [[nodiscard]] auto images() const noexcept -> const std::vector<VkImage> &;

    [[nodiscard]] auto image_views() const -> const std::vector<image_view> &;

    [[nodiscard]] auto extent() const noexcept -> math::size2d<std::uint32_t>;

    [[nodiscard]] auto device() const noexcept -> const device &;

    /*!
     * Acquire the next image in the swap chain. This is a blocking call that waits for the present complete semaphore.
     * \returns The index of the next image index
     */
    [[nodiscard]] auto acquire_next_image(const semaphore_ref &present_complete_semaphore) -> std::uint32_t;

    [[nodiscard]] auto acquire_next_image(const semaphore_ref &present_complete_semaphore,
                                          const std::chrono::nanoseconds timeout) -> std::uint32_t;

    [[nodiscard]] auto acquire_next_image(const semaphore_ref &present_complete_semaphore, const std::uint64_t timeout)
        -> std::uint32_t;

    /*!
     * The current active image index. This will return the same value as acquire_next_image did.
     */
    [[nodiscard]] auto current_index() const noexcept -> std::uint32_t;

    void queue_present(const queue &queue, const semaphore_ref &render_complete_semaphore) const;

private:
    void destroy() const noexcept;

    const vulkan::device *device_;
    const surface *surface_;
    VkPresentModeKHR present_mode_;
    math::size2d<std::uint32_t> extent_;
    VkSurfaceFormatKHR surface_format_;
    VkSwapchainKHR swapchain_;
    std::vector<VkImage> images_;
    std::vector<image_view> image_views_;
    std::uint32_t current_index_;
};

[[nodiscard]] inline auto handle(const swap_chain &s) noexcept
{
    return s.handle();
}

[[nodiscard]] inline auto handle_ptr(const swap_chain &s) noexcept
{
    return s.handle_ptr();
}

/*!
 * Create framebuffers for a given swap chain.
 */
[[nodiscard]] auto create_swap_chain_framebuffers(const swap_chain &swap_chain, const render_pass &render_pass)
    -> std::vector<framebuffer>;

/*!
 * Create framebuffers for a given swap chain. The depth stencil image view will be shared
 * across all frame buffers.
 */
[[nodiscard]] auto create_swap_chain_framebuffers(const swap_chain &swap_chain, const render_pass &render_pass,
                                                  const image_view_ref &depth_stencil) -> std::vector<framebuffer>;

} // namespace aeon::vulkan

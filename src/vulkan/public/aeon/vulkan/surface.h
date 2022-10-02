// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/platform/window.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class instance;

class surface final
{
public:
    surface() noexcept;
    explicit surface(const instance &instance, const platform::window &window);
    explicit surface(const instance &instance, VkSurfaceKHR surface);
    ~surface();

    surface(const surface &) = delete;
    auto operator=(const surface &) -> surface & = delete;

    surface(surface &&other) noexcept;
    auto operator=(surface &&other) noexcept -> surface &;

    [[nodiscard]] auto handle() const noexcept -> VkSurfaceKHR;

private:
    void destroy() const noexcept;

    const instance *instance_;
    VkSurfaceKHR surface_;
};

[[nodiscard]] inline auto handle(const surface &s) noexcept
{
    return s.handle();
}

[[nodiscard]] inline auto handle(const surface *s) noexcept
{
    return s->handle();
}

} // namespace aeon::vulkan

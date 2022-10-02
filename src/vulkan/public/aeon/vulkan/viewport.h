// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/size2d.h>
#include <aeon/math/rectangle.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class viewport final : public VkViewport
{
public:
    constexpr viewport() noexcept;

    constexpr explicit viewport(const float x, const float y, const float width, const float height,
                                const float min_depth, const float max_depth) noexcept;
    constexpr explicit viewport(const math::vector2<float> position, const math::size2d<float> size,
                                const float min_depth, const float max_depth) noexcept;
    constexpr explicit viewport(const math::rectangle<float> rect, const float min_depth,
                                const float max_depth) noexcept;

    template <typename T>
    constexpr explicit viewport(const math::size2d<T> size, const float min_depth, const float max_depth) noexcept;

    template <typename T, typename U>
    constexpr explicit viewport(const math::vector2<T> position, const math::size2d<U> size, const float min_depth,
                                const float max_depth) noexcept;

    ~viewport() noexcept = default;

    constexpr viewport(const viewport &) = default;
    constexpr auto operator=(const viewport &) -> viewport & = default;

    constexpr viewport(viewport &&) noexcept = default;
    constexpr auto operator=(viewport &&) noexcept -> viewport & = default;

    constexpr viewport(const VkViewport &other);

    [[nodiscard]] constexpr auto position() const noexcept -> math::vector2<float>;
    constexpr void position(const math::vector2<float> position) noexcept;

    [[nodiscard]] constexpr auto size() const noexcept -> math::size2d<float>;
    constexpr void size(const math::size2d<float> size) noexcept;

    [[nodiscard]] constexpr auto rect() const noexcept -> math::rectangle<float>;
    constexpr void rect(const math::rectangle<float> rect) noexcept;
};

constexpr inline viewport::viewport(const VkViewport &other)
    : VkViewport{other}
{
}

static_assert(sizeof(viewport) == sizeof(VkViewport));

constexpr inline viewport::viewport() noexcept
    : VkViewport{}
{
}

constexpr viewport::viewport(const float x, const float y, const float width, const float height, const float min_depth,
                             const float max_depth) noexcept
    : VkViewport{x, y, width, height, min_depth, max_depth}
{
}

constexpr inline viewport::viewport(const math::vector2<float> position, const math::size2d<float> size,
                                    const float min_depth, const float max_depth) noexcept
    : VkViewport{position.x, position.y, size.width, size.height, min_depth, max_depth}
{
}

constexpr inline viewport::viewport(const math::rectangle<float> rect, const float min_depth,
                                    const float max_depth) noexcept
    : VkViewport{math::left(rect), math::top(rect), math::width(rect), math::height(rect), min_depth, max_depth}
{
}

template <typename T>
constexpr viewport::viewport(const math::size2d<T> size, const float min_depth, const float max_depth) noexcept
    : VkViewport{0, 0, static_cast<float>(size.width), static_cast<float>(size.height), min_depth, max_depth}
{
}

template <typename T, typename U>
constexpr viewport::viewport(const math::vector2<T> position, const math::size2d<U> size, const float min_depth,
                             const float max_depth) noexcept
    : VkViewport{static_cast<float>(position.x),
                 static_cast<float>(position.y),
                 static_cast<float>(size.width),
                 static_cast<float>(size.height),
                 min_depth,
                 max_depth}
{
}

[[nodiscard]] constexpr inline auto viewport::position() const noexcept -> math::vector2<float>
{
    return {x, y};
}

constexpr inline void viewport::position(const math::vector2<float> position) noexcept
{
    x = position.x;
    y = position.y;
}

[[nodiscard]] constexpr inline auto viewport::size() const noexcept -> math::size2d<float>
{
    return {width, height};
}

constexpr inline void viewport::size(const math::size2d<float> size) noexcept
{
    width = size.width;
    height = size.height;
}

[[nodiscard]] constexpr inline auto viewport::rect() const noexcept -> math::rectangle<float>
{
    return {position(), size()};
}

constexpr inline void viewport::rect(const math::rectangle<float> rect) noexcept
{
    x = math::left(rect);
    y = math::top(rect);
    width = math::width(rect);
    height = math::height(rect);
}

} // namespace aeon::vulkan

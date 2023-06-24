// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/rectangle.h>
#include <vulkan/vulkan_core.h>

namespace aeon::vulkan
{

class rectangle final : public VkRect2D
{
public:
    constexpr rectangle() noexcept;
    constexpr explicit rectangle(const std::int32_t x, const std::int32_t y, const std::uint32_t width,
                                 const std::uint32_t height) noexcept;
    constexpr explicit rectangle(const math::vector2<std::int32_t> position,
                                 const math::size2d<std::uint32_t> size) noexcept;
    constexpr explicit rectangle(const math::rectangle<std::int32_t> rect) noexcept;
    ~rectangle() noexcept = default;

    constexpr rectangle(const rectangle &) = default;
    constexpr auto operator=(const rectangle &) -> rectangle & = default;

    constexpr rectangle(rectangle &&) noexcept = default;
    constexpr auto operator=(rectangle &&) noexcept -> rectangle & = default;

    constexpr rectangle(const VkRect2D &other) noexcept;

    [[nodiscard]] constexpr auto position() const noexcept -> math::vector2<std::int32_t>;
    constexpr void position(const math::vector2<std::int32_t> position) noexcept;

    [[nodiscard]] constexpr auto size() const noexcept -> math::size2d<std::uint32_t>;
    constexpr void size(const math::size2d<std::uint32_t> size) noexcept;

    [[nodiscard]] constexpr auto rect() const noexcept -> math::rectangle<std::int32_t>;
    constexpr void rect(const math::rectangle<std::int32_t> rect) noexcept;
};

static_assert(sizeof(rectangle) == sizeof(VkRect2D));

constexpr inline rectangle::rectangle() noexcept
    : VkRect2D{}
{
}

constexpr rectangle::rectangle(const std::int32_t x, const std::int32_t y, const std::uint32_t width,
                               const std::uint32_t height) noexcept
    : VkRect2D{{x, y}, {width, height}}
{
}

constexpr rectangle::rectangle(const math::vector2<std::int32_t> position,
                               const math::size2d<std::uint32_t> size) noexcept
    : VkRect2D{{position.x, position.y}, {size.width, size.height}}
{
}

constexpr rectangle::rectangle(const math::rectangle<std::int32_t> rect) noexcept
    : VkRect2D{{math::left(rect), math::top(rect)},
               {static_cast<std::uint32_t>(math::width(rect)), static_cast<std::uint32_t>(math::height(rect))}}
{
}

constexpr rectangle::rectangle(const VkRect2D &other) noexcept
    : VkRect2D{other}
{
}

constexpr auto rectangle::position() const noexcept -> math::vector2<std::int32_t>
{
    return {offset.x, offset.y};
}

constexpr void rectangle::position(const math::vector2<std::int32_t> position) noexcept
{
    offset.x = position.x;
    offset.y = position.y;
}

constexpr auto rectangle::size() const noexcept -> math::size2d<std::uint32_t>
{
    return {extent.width, extent.height};
}

constexpr void rectangle::size(const math::size2d<std::uint32_t> size) noexcept
{
    extent.width = size.width;
    extent.height = size.height;
}

constexpr auto rectangle::rect() const noexcept -> math::rectangle<std::int32_t>
{
    return {position(), math::size2d<std::int32_t>{size()}};
}

constexpr void rectangle::rect(const math::rectangle<std::int32_t> rect) noexcept
{
    offset = {math::left(rect), math::top(rect)};
    extent = {static_cast<std::uint32_t>(math::width(rect)), static_cast<std::uint32_t>(math::height(rect))};
}

} // namespace aeon::vulkan

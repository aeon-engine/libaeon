// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <algorithm>

namespace aeon::imaging
{

inline auto operator*(const rgb24 lhs, const float rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f))};
}

inline auto operator*=(rgb24 &lhs, const float rhs) noexcept -> rgb24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255))};
}

inline auto operator*=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255))};
}

inline auto operator+=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const rgb24 lhs, const rgb24 rhs) noexcept -> rgb24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255))};
}

inline auto operator-=(rgb24 &lhs, const rgb24 rhs) noexcept -> rgb24
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator==(const rgb24 lhs, const rgb24 rhs) noexcept -> bool
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
}

inline auto operator!=(const rgb24 lhs, const rgb24 rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

inline auto operator*(const rgba32 lhs, const float rhs) noexcept -> rgba32
{
    return {
        static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.a * rhs, 0.0f, 255.0f)),
    };
}

inline auto operator*=(rgba32 &lhs, const float rhs) noexcept -> rgba32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a * rhs.a, 0, 255))};
}

inline auto operator*=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a + rhs.a, 0, 255))};
}

inline auto operator+=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const rgba32 lhs, const rgba32 rhs) noexcept -> rgba32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a - rhs.a, 0, 255))};
}

inline auto operator-=(rgba32 &lhs, const rgba32 rhs) noexcept -> rgba32
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator==(const rgba32 lhs, const rgba32 rhs) noexcept -> bool
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

inline auto operator!=(const rgba32 lhs, const rgba32 rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

inline auto operator*(const bgr24 lhs, const float rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
            static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f))};
}

inline auto operator*=(bgr24 &lhs, const float rhs) noexcept -> bgr24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255))};
}

inline auto operator*=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255))};
}

inline auto operator+=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const bgr24 lhs, const bgr24 rhs) noexcept -> bgr24
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255))};
}

inline auto operator-=(bgr24 &lhs, const bgr24 rhs) noexcept -> bgr24
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator==(const bgr24 lhs, const bgr24 rhs) noexcept -> bool
{
    return lhs.b == rhs.b && lhs.g == rhs.g && lhs.r == rhs.r;
}

inline auto operator!=(const bgr24 lhs, const bgr24 rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

inline auto operator*(const bgra32 lhs, const float rhs) noexcept -> bgra32
{
    return {
        static_cast<std::uint8_t>(std::clamp(lhs.b * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.g * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.r * rhs, 0.0f, 255.0f)),
        static_cast<std::uint8_t>(std::clamp(lhs.a * rhs, 0.0f, 255.0f)),
    };
}

inline auto operator*=(bgra32 &lhs, const float rhs) noexcept -> bgra32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator*(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b * rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g * rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r * rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a * rhs.a, 0, 255))};
}

inline auto operator*=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32
{
    lhs = lhs * rhs;
    return lhs;
}

inline auto operator+(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b + rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g + rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r + rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a + rhs.a, 0, 255))};
}

inline auto operator+=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32
{
    lhs = lhs + rhs;
    return lhs;
}

inline auto operator-(const bgra32 lhs, const bgra32 rhs) noexcept -> bgra32
{
    return {static_cast<std::uint8_t>(std::clamp(lhs.b - rhs.b, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.g - rhs.g, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.r - rhs.r, 0, 255)),
            static_cast<std::uint8_t>(std::clamp(lhs.a - rhs.a, 0, 255))};
}

inline auto operator-=(bgra32 &lhs, const bgra32 rhs) noexcept -> bgra32
{
    lhs = lhs - rhs;
    return lhs;
}

inline auto operator==(const bgra32 lhs, const bgra32 rhs) noexcept -> bool
{
    return lhs.b == rhs.b && lhs.g == rhs.g && lhs.r == rhs.r && lhs.a == rhs.a;
}

inline auto operator!=(const bgra32 lhs, const bgra32 rhs) noexcept -> bool
{
    return !(lhs == rhs);
}

} // namespace aeon::imaging

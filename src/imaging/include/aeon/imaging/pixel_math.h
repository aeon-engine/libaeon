// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/imaging/pixel_encoding.h>

namespace aeon::imaging
{

template <typename T>
struct pixel_math
{
    static constexpr auto min() noexcept -> T
    {
        return std::numeric_limits<T>::min();
    }

    static constexpr auto max() noexcept -> T
    {
        return std::numeric_limits<T>::max();
    }

    static constexpr auto clamp(const int value) noexcept -> T
    {
        return static_cast<T>(std::clamp(value, static_cast<int>(min()), static_cast<int>(max())));
    }

    static constexpr auto clamp(const unsigned int value) noexcept -> T
    {
        return static_cast<T>(std::clamp(static_cast<int>(value), static_cast<int>(min()), static_cast<int>(max())));
    }

    static constexpr auto clamp(const float value) noexcept -> T
    {
        return static_cast<T>(std::clamp(static_cast<int>(value), static_cast<int>(min()), static_cast<int>(max())));
    }

    static constexpr auto alpha(const T value) noexcept -> T
    {
        return value;
    }

    static constexpr auto alpha_ratio(const T value) noexcept -> float
    {
        return static_cast<float>(value) / static_cast<float>(max());
    }
};

template <>
struct pixel_math<float>
{
    static constexpr auto min() noexcept -> float
    {
        return 0.0f;
    }

    static constexpr auto max() noexcept -> float
    {
        return 1.0f;
    }

    static constexpr auto clamp(const float value) noexcept -> float
    {
        return std::clamp(value, min(), max());
    }

    static constexpr auto alpha(const float value) noexcept -> float
    {
        return value;
    }

    static constexpr auto alpha_ratio(const float value) noexcept -> float
    {
        return value / max();
    }
};

template <>
struct pixel_math<rgb24>
{
    static constexpr auto min() noexcept -> std::uint8_t
    {
        return 0;
    }

    static constexpr auto max() noexcept -> std::uint8_t
    {
        return 255;
    }

    static constexpr auto clamp(const rgb24 value) noexcept -> rgb24
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255))};
    }

    static constexpr auto alpha(const rgb24 value) noexcept -> std::uint8_t
    {
        return 255;
    }

    static constexpr auto alpha_ratio(const rgb24 value) noexcept -> float
    {
        return 1.0f;
    }
};

template <>
struct pixel_math<rgba32>
{
    static constexpr auto min() noexcept -> std::uint8_t
    {
        return 0;
    }

    static constexpr auto max() noexcept -> std::uint8_t
    {
        return 255;
    }

    static constexpr auto clamp(const rgba32 value) noexcept -> rgba32
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.a), 0, 255))};
    }

    static constexpr auto alpha(const rgba32 value) noexcept -> std::uint8_t
    {
        return value.a;
    }

    static constexpr auto alpha_ratio(const rgba32 value) noexcept -> float
    {
        return static_cast<float>(alpha(value)) / static_cast<float>(max());
    }
};

template <>
struct pixel_math<bgr24>
{
    static constexpr auto min() noexcept -> std::uint8_t
    {
        return 0;
    }

    static constexpr auto max() noexcept -> std::uint8_t
    {
        return 255;
    }

    static constexpr auto clamp(const bgr24 value) noexcept -> bgr24
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255))};
    }

    static constexpr auto alpha(const bgr24 value) noexcept -> std::uint8_t
    {
        return 255;
    }

    static constexpr auto alpha_ratio(const bgr24 value) noexcept -> float
    {
        return 1.0f;
    }
};

template <>
struct pixel_math<bgra32>
{
    static constexpr auto min() noexcept -> std::uint8_t
    {
        return 0;
    }

    static constexpr auto max() noexcept -> std::uint8_t
    {
        return 255;
    }

    static constexpr auto clamp(const bgra32 value) noexcept -> bgra32
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.a), 0, 255))};
    }

    static constexpr auto alpha(const bgra32 value) noexcept -> std::uint8_t
    {
        return value.a;
    }

    static constexpr auto alpha_ratio(const bgra32 value) noexcept -> float
    {
        return static_cast<float>(alpha(value)) / static_cast<float>(max());
    }
};

} // namespace aeon::imaging

/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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
};

template <>
struct pixel_math<rgb24>
{
    static constexpr auto min() noexcept -> rgb24
    {
        return {0, 0, 0};
    }

    static constexpr auto max() noexcept -> rgb24
    {
        return {255, 255, 255};
    }

    static constexpr auto clamp(const rgb24 value) noexcept -> rgb24
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255))};
    }
};

template <>
struct pixel_math<rgba32>
{
    static constexpr auto min() noexcept -> rgba32
    {
        return {0, 0, 0, 0};
    }

    static constexpr auto max() noexcept -> rgba32
    {
        return {255, 255, 255, 255};
    }

    static constexpr auto clamp(const rgba32 value) noexcept -> rgba32
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.a), 0, 255))};
    }
};

template <>
struct pixel_math<bgr24>
{
    static constexpr auto min() noexcept -> bgr24
    {
        return {0, 0, 0};
    }

    static constexpr auto max() noexcept -> bgr24
    {
        return {255, 255, 255};
    }

    static constexpr auto clamp(const bgr24 value) noexcept -> bgr24
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255))};
    }
};

template <>
struct pixel_math<bgra32>
{
    static constexpr auto min() noexcept -> bgra32
    {
        return {0, 0, 0, 0};
    }

    static constexpr auto max() noexcept -> bgra32
    {
        return {255, 255, 255, 255};
    }

    static constexpr auto clamp(const bgra32 value) noexcept -> bgra32
    {
        return {static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.b), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.g), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.r), 0, 255)),
                static_cast<std::uint8_t>(std::clamp(static_cast<int>(value.a), 0, 255))};
    }
};

} // namespace aeon::imaging

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

#include <aeon/imaging/dimension.h>
#include <aeon/common/compilers.h>
#include <cstddef>
#include <algorithm>

namespace aeon::imaging
{

AEON_PACK_STRUCT_PUSH(1)
struct rgb24
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(rgb24) == 3, "Alignment problem: rgb24 must be 3 bytes in size.");

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
    lhs = lhs + rhs;
    return lhs;
}

AEON_PACK_STRUCT_PUSH(1)
struct rgba32
{
    std::uint8_t r = 0;
    std::uint8_t g = 0;
    std::uint8_t b = 0;
    std::uint8_t a = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(rgba32) == 4, "Alignment problem: rgba32 must be 4 bytes in size.");

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

AEON_PACK_STRUCT_PUSH(1)
struct bgr24
{
    std::uint8_t b = 0;
    std::uint8_t g = 0;
    std::uint8_t r = 0;
} AEON_PACK_STRUCT_POP(1);

static_assert(sizeof(bgr24) == 3, "Alignment problem: bgr24 must be 3 bytes in size.");

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

enum class pixel_encoding
{
    unsigned8,
    unsigned16,
    unsigned32,
    float32,
    rgb24,
    rgba32,
    bgr24
};

template <typename T>
struct pixel_encoding_trait
{
};

template <>
struct pixel_encoding_trait<std::uint8_t>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned8;
    }
};

template <>
struct pixel_encoding_trait<std::uint16_t>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned16;
    }
};

template <>
struct pixel_encoding_trait<std::uint32_t>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::unsigned32;
    }
};

template <>
struct pixel_encoding_trait<float>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::float32;
    }
};

template <>
struct pixel_encoding_trait<rgb24>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::rgb24;
    }
};

template <>
struct pixel_encoding_trait<rgba32>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::rgba32;
    }
};

template <>
struct pixel_encoding_trait<bgr24>
{
    static constexpr auto encoding() noexcept
    {
        return pixel_encoding::bgr24;
    }
};

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

} // namespace aeon::imaging

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

#include <aeon/imaging/image.h>
#include <aeon/imaging/pixel_encoding.h>
#include <aeon/imaging/exceptions.h>
#include <memory>

namespace aeon::imaging
{

class dynamic_image
{
public:
    template <typename T>
    explicit dynamic_image(image<T> &&image);

    template <typename T>
    explicit dynamic_image(std::unique_ptr<image<T>> image);

    ~dynamic_image();

    dynamic_image(const dynamic_image &) = delete;
    auto operator=(const dynamic_image &) -> dynamic_image & = delete;

    dynamic_image(dynamic_image &&o) noexcept = default;
    auto operator=(dynamic_image &&other) noexcept -> dynamic_image & = default;

    template <typename T>
    operator image<T> &() noexcept;

    template <typename T>
    operator const image<T> &() const noexcept;

    auto encoding() const noexcept -> pixel_encoding;

    template <typename T>
    auto get_image() noexcept -> image<T> &;

    template <typename T>
    auto get_image() const noexcept -> const image<T> &;

private:
    std::unique_ptr<image_base> image_;
    pixel_encoding encoding_;
};

inline auto encoding(const dynamic_image &image) noexcept -> pixel_encoding;

template <typename T>
inline auto view(const dynamic_image &image) noexcept -> image_view<T>;

#define write_image(img, func, ...)                                                                                    \
    [&]() {                                                                                                            \
        switch (encoding(img))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                func<std::uint8_t>(view<std::uint8_t>(img), __VA_ARGS__);                                              \
                return;                                                                                                \
            case pixel_encoding::unsigned16:                                                                           \
                func<std::uint16_t>(view<std::uint16_t>(img), __VA_ARGS__);                                            \
                return;                                                                                                \
            case pixel_encoding::unsigned32:                                                                           \
                func<std::uint32_t>(view<std::uint32_t>(img), __VA_ARGS__);                                            \
                return;                                                                                                \
            case pixel_encoding::float32:                                                                              \
                func<float>(view<float>(img), __VA_ARGS__);                                                            \
                return;                                                                                                \
            case pixel_encoding::rgb24:                                                                                \
                func<rgb24>(view<rgb24>(img), __VA_ARGS__);                                                            \
                return;                                                                                                \
            case pixel_encoding::rgba32:                                                                               \
                func<rgba32>(view<rgba32>(img), __VA_ARGS__);                                                          \
                return;                                                                                                \
            case pixel_encoding::bgr24:                                                                                \
                func<bgr24>(view<bgr24>(img), __VA_ARGS__);                                                            \
                return;                                                                                                \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

#define process_image(img, func, ...)                                                                                  \
    [&]() -> dynamic_image {                                                                                           \
        switch (encoding(img))                                                                                         \
        {                                                                                                              \
            case pixel_encoding::unsigned8:                                                                            \
                return dynamic_image{func<std::uint8_t>(view<std::uint8_t>(img), __VA_ARGS__)};                        \
            case pixel_encoding::unsigned16:                                                                           \
                return dynamic_image{func<std::uint16_t>(view<std::uint16_t>(img), __VA_ARGS__)};                      \
            case pixel_encoding::unsigned32:                                                                           \
                return dynamic_image{func<std::uint32_t>(view<std::uint32_t>(img), __VA_ARGS__)};                      \
            case pixel_encoding::float32:                                                                              \
                return dynamic_image{func<float>(view<float>(img), __VA_ARGS__)};                                      \
            case pixel_encoding::rgb24:                                                                                \
                return dynamic_image{func<rgb24>(view<rgb24>(img), __VA_ARGS__)};                                      \
            case pixel_encoding::rgba32:                                                                               \
                return dynamic_image{func<rgba32>(view<rgba32>(img), __VA_ARGS__)};                                    \
            case pixel_encoding::bgr24:                                                                                \
                return dynamic_image{func<bgr24>(view<bgr24>(img), __VA_ARGS__)};                                      \
            default:                                                                                                   \
                throw imaging_exception();                                                                             \
        }                                                                                                              \
    }();

} // namespace aeon::imaging

#include <aeon/imaging/impl/dynamic_image_impl.h>

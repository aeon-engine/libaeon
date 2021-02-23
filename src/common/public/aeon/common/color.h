// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <cstdint>

namespace aeon::common
{

template <concepts::arithmetic T>
class color3
{
public:
    using type = T;

    color3() noexcept;
    explicit color3(const type r, const type g, const type b) noexcept;

    ~color3() = default;

    color3(const color3 &) noexcept = default;
    auto operator=(const color3 &) noexcept -> color3 & = default;

    color3(color3 &&) noexcept = default;
    auto operator=(color3 &&) noexcept -> color3 & = default;

    type r;
    type g;
    type b;
};

using color3u = color3<std::uint8_t>;
using color3f = color3<float>;
using color3d = color3<double>;

template <concepts::arithmetic T>
class color4
{
public:
    using type = T;

    color4() noexcept;

    explicit color4(const type r, const type g, const type b) noexcept;
    explicit color4(const type r, const type g, const type b, const type a) noexcept;

    explicit color4(const color3<type> c) noexcept;
    explicit color4(const color3<type> c, const type a) noexcept;

    ~color4() = default;

    color4(const color4 &) noexcept = default;
    auto operator=(const color4 &) noexcept -> color4 & = default;

    color4(color4 &&) noexcept = default;
    auto operator=(color4 &&) noexcept -> color4 & = default;

    type r;
    type g;
    type b;
    type a;
};

using color4u = color4<std::uint8_t>;
using color4f = color4<float>;
using color4d = color4<double>;

} // namespace aeon::common

#include <aeon/common/impl/color_impl.h>

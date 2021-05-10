// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

namespace aeon::math
{

enum class swizzle_component
{
    x,
    y,
    z,
    w,
    r = x,
    g = y,
    b = z,
    a = w
};

static constexpr auto swizzle_x = swizzle_component::x;
static constexpr auto swizzle_y = swizzle_component::y;
static constexpr auto swizzle_z = swizzle_component::z;
static constexpr auto swizzle_w = swizzle_component::w;

static constexpr auto swizzle_r = swizzle_component::r;
static constexpr auto swizzle_g = swizzle_component::g;
static constexpr auto swizzle_b = swizzle_component::b;
static constexpr auto swizzle_a = swizzle_component::a;

} // namespace aeon::math

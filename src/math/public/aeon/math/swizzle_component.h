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
    a = w,
    one,
    minus_one,
    zero,
    min,
    max,
};

static constexpr auto swizzle_x = swizzle_component::x;
static constexpr auto swizzle_y = swizzle_component::y;
static constexpr auto swizzle_z = swizzle_component::z;
static constexpr auto swizzle_w = swizzle_component::w;

static constexpr auto swizzle_r = swizzle_component::r;
static constexpr auto swizzle_g = swizzle_component::g;
static constexpr auto swizzle_b = swizzle_component::b;
static constexpr auto swizzle_a = swizzle_component::a;

static constexpr auto swizzle_one = swizzle_component::one;
static constexpr auto swizzle_minus_one = swizzle_component::minus_one;
static constexpr auto swizzle_zero = swizzle_component::zero;
static constexpr auto swizzle_min = swizzle_component::min;
static constexpr auto swizzle_max = swizzle_component::max;

} // namespace aeon::math

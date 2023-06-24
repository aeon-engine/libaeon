// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::math
{

enum class clipping_space
{
    zero_to_one,     // DirectX, Vulkan
    minus_one_to_one // OpenGL
};

constexpr auto default_clipping_space = clipping_space::zero_to_one;

} // namespace aeon::math

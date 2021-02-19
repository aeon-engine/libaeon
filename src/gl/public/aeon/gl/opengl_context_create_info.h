// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/version.h>

namespace aeon::gl
{

static inline constexpr auto default_opengl_version = common::version2<int>{3, 3};

struct opengl_context_create_info final
{
    common::version2<int> version = default_opengl_version;

    std::uint32_t color_bits = 32;
    std::uint32_t depth_bits = 32;
    std::uint32_t stencil_bits = 0;

    std::uint32_t core_profile : 1 = true;
    std::uint32_t compatibility_profile : 1 = false;
    std::uint32_t forward_compatible : 1 = false;
    std::uint32_t enable_debug : 1 = false;
    std::uint32_t double_buffer : 1 = true;
};

} // namespace aeon::gl

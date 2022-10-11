// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <aeon/math/vector2.h>
#include <aeon/common/string.h>
#include <optional>
#include <cstdint>

namespace aeon::platform
{

static inline constexpr auto default_window_title = "Aeon";
static inline constexpr auto default_window_size = math::size2d{1280, 720};

class window_events;

struct window_create_info final
{
    common::string title = default_window_title;

    /*!
     * The size of the window client area
     */
    math::size2d<std::int32_t> size = default_window_size;

    /*!
     * The desired window position. If set to nullopt, the positioning is left to the operating system.
     */
    std::optional<math::vector2<std::int32_t>> position = std::nullopt;

    std::uint32_t resizable : 1 = true;
    std::uint32_t visible : 1 = true;
};

} // namespace aeon::platform

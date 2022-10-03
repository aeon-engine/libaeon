// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

namespace aeon::platform
{

/*!
 * The state of a mouse button
 */
enum class mouse_button_state
{
    released, ///< A mouse button is released (up)
    pressed,  ///< A mouse button is pressed (down)
};

} // namespace aeon::platform

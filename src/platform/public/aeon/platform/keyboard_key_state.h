// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::platform
{

/*!
 * The state of a keyboard key
 */
enum class keyboard_key_state
{
    released, ///< A keyboard key is released (up)
    pressed,  ///< A keyboard key is pressed (down)
    repeated  ///< A keyboard key pressed and held down
};

} // namespace aeon::platform

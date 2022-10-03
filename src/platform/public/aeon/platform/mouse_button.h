// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

namespace aeon::platform
{

enum class mouse_button
{
    button1 = 0,
    button2 = 1,
    button3 = 2,
    button4 = 3,
    button5 = 4,
    button6 = 5,
    button7 = 6,
    button8 = 7,
    left = button1,
    right = button2,
    middle = button3,
    unknown = -1,
};

} // namespace aeon::platform

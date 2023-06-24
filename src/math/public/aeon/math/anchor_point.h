// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

namespace aeon::math
{

/*!
 * Anchor points to indicate where the given position should be in relation to the object being moved.
 *
 *\verbatim
 *       left_top     top_center     right_top
 *              ######################
 *              #                    #
 *  left_center #       center       # right_center
 *              #                    #
 *              ######################
 *   left_bottom    bottom_center    right_bottom
 *\endverbatim
 */
enum class anchor_point
{
    left_top,
    left_center,
    left_bottom,
    right_top,
    right_center,
    right_bottom,
    top_center,
    bottom_center,
    center
};

} // namespace aeon::math

// Copyright (c) 2012-2019 Robin Degen

#pragma once

namespace aeon::math
{

/*!
 * Placeholder type to indicate that the given argument must be converted
 * from an unknown type.
 *
 * For example an external library may have it's own size2d class with
 * width and height as member variables. Specifying this type in a constructor
 * will automatically convert that unknown external type to an aeon::math::size2d.
 */
struct convert_type
{
};

} // namespace aeon::math

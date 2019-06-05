// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/math/quaternion.h>
#include <ostream>

namespace aeon::math
{

inline auto operator<<(std::ostream &os, const quaternion &q) -> std::ostream &
{
    return os << "quaternion(" << q.w << ", " << q.x << ", " << q.y << ", " << q.z << ")";
}

} // namespace aeon::math

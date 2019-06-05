// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/math/mat4.h>
#include <ostream>

namespace aeon::math
{

inline auto operator<<(std::ostream &os, const mat4 &m) -> std::ostream &
{
    return os << "mat4({" << m[0][0] << ", " << m[1][0] << ", " << m[2][0] << ", " << m[3][0] << "}, {" << m[0][1]
              << ", " << m[1][1] << ", " << m[2][1] << ", " << m[3][1] << "}, {" << m[0][2] << ", " << m[1][2] << ", "
              << m[2][2] << ", " << m[3][2] << "}, {" << m[0][3] << ", " << m[1][3] << ", " << m[2][3] << ", "
              << m[3][3] << "})";
}

} // namespace aeon::math

// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/mat3.h>
#include <ostream>

namespace aeon::math
{

inline auto operator<<(std::ostream &os, const mat3 &m) -> std::ostream &
{
    return os << "mat3({" << m[0][0] << ", " << m[1][0] << ", " << m[2][0] << "}, {" << m[0][1] << ", " << m[1][1]
              << ", " << m[2][1] << "}, {" << m[0][2] << ", " << m[1][2] << ", " << m[2][2] << "})";
}

} // namespace aeon::math

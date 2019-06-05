// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/math/vector4.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const vector4<T> &v) -> std::ostream &
{
    return os << "vector4<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

} // namespace aeon::math

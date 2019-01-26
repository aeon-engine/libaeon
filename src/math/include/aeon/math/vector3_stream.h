// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/math/vector3.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const vector3<T> &v) -> std::ostream &
{
    return os << "vector3<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ", " << v.z << ")";
}

} // namespace aeon::math

// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const vector2<T> &v) -> std::ostream &
{
    return os << "vector2<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ")";
}

} // namespace aeon::math

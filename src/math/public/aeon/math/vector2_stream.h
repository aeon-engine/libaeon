// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <ostream>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline auto operator<<(std::ostream &os, const vector2<T> &v) -> std::ostream &
{
    return os << "vector2<" << typeid(T).name() << ">(" << v.x << ", " << v.y << ")";
}

} // namespace aeon::math

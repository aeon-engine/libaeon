// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/circle.h>
#include <ostream>
#include <typeinfo>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline auto operator<<(std::ostream &os, const circle<T> &c) -> std::ostream &
{
    const auto pos = position(c);
    return os << "circle<" << typeid(T).name() << ">({" << pos.x << ", " << pos.y << "}, r=" << radius(c) << ")";
}

} // namespace aeon::math

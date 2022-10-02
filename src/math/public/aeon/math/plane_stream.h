// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/plane.h>
#include <aeon/math/vector3_stream.h>
#include <ostream>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline auto operator<<(std::ostream &os, const plane<T> &p) -> std::ostream &
{
    return os << "plane<" << typeid(T).name() << ">(normal: " << normal(p) << ", distance: " << distance(p) << ")";
}

} // namespace aeon::math

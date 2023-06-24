// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/math/size3d.h>
#include <ostream>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline auto operator<<(std::ostream &os, const size3d<T> &s) -> std::ostream &
{
    return os << "size3d<" << typeid(T).name() << ">(" << width(s) << ", " << height(s) << ", " << depth(s) << ")";
}

} // namespace aeon::math

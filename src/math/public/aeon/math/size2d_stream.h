// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/size2d.h>
#include <ostream>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
inline auto operator<<(std::ostream &os, const size2d<T> &s) -> std::ostream &
{
    return os << "size2d<" << typeid(T).name() << ">(" << width(s) << ", " << height(s) << ")";
}

} // namespace aeon::math

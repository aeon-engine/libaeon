// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#pragma once

#include <aeon/math/rectangle.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const rectangle<T> &r) -> std::ostream &
{
    return os << "rectangle<" << typeid(T).name() << ">(" << left(r) << ", " << top(r) << ", " << right(r) << ", "
              << bottom(r) << ")";
}

} // namespace aeon::math

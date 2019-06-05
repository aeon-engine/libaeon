// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/math/range.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const range<T> &q) -> std::ostream &
{
    return os << "range<" << typeid(T).name() << ">(" << q.begin << ", " << q.end << ")";
}

} // namespace aeon::math

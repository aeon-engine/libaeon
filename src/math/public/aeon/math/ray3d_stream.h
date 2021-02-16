// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/math/ray3d.h>
#include <aeon/math/vector3_stream.h>
#include <ostream>

namespace aeon::math
{

template <typename T>
inline auto operator<<(std::ostream &os, const ray3d<T> &ray) -> std::ostream &
{
    return os << "ray3d<" << typeid(T).name() << ">(normal: " << normal(ray) << ", origin: " << origin(ray) << ")";
}

} // namespace aeon::math

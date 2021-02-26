// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <aeon/math/range.h>
#include <aeon/math/vector2.h>

namespace aeon::math
{

template <common::concepts::arithmetic_convertible T>
using line_segment = range<vector2<T>>;

} // namespace aeon::math

// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/common/concepts.h>

namespace aeon::math
{

class mat;

template <typename T>
class mat_view_base;

class mat3;

class mat4;

class quaternion;

template <common::concepts::arithmetic_convertible T>
class vector2;

template <common::concepts::arithmetic_convertible T>
class vector3;

template <common::concepts::arithmetic_convertible T>
class vector4;

template <common::concepts::arithmetic_convertible T>
class size2d;

template <common::concepts::arithmetic_convertible T>
class size3d;

template <typename T>
class range;

template <common::concepts::arithmetic_convertible T>
class rectangle;

} // namespace aeon::math

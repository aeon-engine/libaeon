// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

/*!
 * \file
 * \brief Provides simple hashing implementations for various math types so they can be used in set, map, or any other
 * hash based container.
 */

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/vector3.h>
#include <aeon/math/vector4.h>
#include <aeon/math/size2d.h>
#include <aeon/math/size3d.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/range.h>
#include <aeon/math/quaternion.h>
#include <aeon/common/hash.h>

template <typename T>
struct std::hash<aeon::math::vector2<T>>
{
    inline auto operator()(const aeon::math::vector2<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.x, val.y);
    }
};

template <typename T>
struct std::hash<aeon::math::vector3<T>>
{
    inline auto operator()(const aeon::math::vector3<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.x, val.y, val.z);
    }
};

template <typename T>
struct std::hash<aeon::math::vector4<T>>
{
    inline auto operator()(const aeon::math::vector4<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.x, val.y, val.z, val.w);
    }
};

template <typename T>
struct std::hash<aeon::math::size2d<T>>
{
    inline auto operator()(const aeon::math::size2d<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.width, val.height);
    }
};

template <typename T>
struct std::hash<aeon::math::size3d<T>>
{
    inline auto operator()(const aeon::math::size3d<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.width, val.height, val.depth);
    }
};

template <typename T>
struct std::hash<aeon::math::rectangle<T>>
{
    inline auto operator()(const aeon::math::rectangle<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.left, val.top, val.right, val.bottom);
    }
};

template <typename T>
struct std::hash<aeon::math::range<T>>
{
    inline auto operator()(const aeon::math::range<T> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.begin, val.end);
    }
};

template <>
struct std::hash<aeon::math::quaternion>
{
    inline auto operator()(const aeon::math::quaternion &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.w, val.x, val.y, val.z);
    }
};

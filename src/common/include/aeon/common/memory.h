// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <memory>
#include <stdexcept>

namespace aeon::common
{

/*!
 * Dynamic cast a unique_ptr to another type. If the cast fails, a nullptr will be returned.
 * Be aware that this means that the originally given unique_ptr gets deleted.
 */
template <typename T, typename U>
[[nodiscard]] inline auto dynamic_unique_ptr_cast(std::unique_ptr<U> &&ptr) -> std::unique_ptr<T>
{
    auto result = dynamic_cast<T *>(ptr.get());

    if (!result)
        return nullptr;

    auto retval = std::unique_ptr<T>{result};
    ptr.release();
    return retval;
}

/*!
 * Static cast a unique_ptr to another type.
 */
template <typename T, typename U>
[[nodiscard]] inline auto static_unique_ptr_cast(std::unique_ptr<U> &&ptr) noexcept -> std::unique_ptr<T>
{
    return std::unique_ptr<T>{static_cast<T *>(ptr.release())};
}

} // namespace aeon::common

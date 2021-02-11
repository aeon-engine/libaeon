// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <functional>
#include <cstdint>
#include <cstddef>

namespace aeon::common
{

/*!
 * Magic number used in the TEA algorithm (Tiny Encryption Algorithm)
 *
 * The value originals from the golden ratio:
 * phi = (1 + sqrt(5)) / 2 = 1,6180339887498948482045868343656.
 * (int)(2^32 / phi) = 2654435769 = 0x9e3779b97f4a7c16
 */
template <typename T>
struct hash_constants
{
};

template <>
struct hash_constants<std::size_t>
{
    static constexpr auto golden_ratio = 0x9e3779b97f4a7c16ull;
};

namespace internal
{
template <typename T>
void hash_combine_impl(std::size_t &seed, const T &v)
{
    seed ^= std::hash<T>{}(v) + hash_constants<std::size_t>::golden_ratio + (seed << 6) + (seed >> 2);
}
} // namespace internal

/*!
 * Helper function that can be used to combine multiple values into a single hash
 * Should be called for each value that needs to be hashed.
 */
template <typename... args_t>
void hash_combine(std::size_t &seed, args_t... args)
{
    (internal::hash_combine_impl(seed, args), ...);
}

/*!
 * Helper function that can be used to combine multiple values into a single hash
 * This version of the function returns the final hash instead of applying it to an existing value.
 */
template <typename... args_t>
[[nodiscard]] auto hash_combined(args_t... args)
{
    std::size_t seed = 0;
    (internal::hash_combine_impl(seed, args), ...);
    return seed;
}

} // namespace aeon::common

template <typename T, typename U>
struct std::hash<std::pair<T, U>>
{
    inline auto operator()(const std::pair<T, U> &val) const noexcept -> std::size_t
    {
        return aeon::common::hash_combined(val.first, val.second);
    }
};

template <typename... args_t>
struct std::hash<std::tuple<args_t...>>
{
    inline auto operator()(const std::tuple<args_t...> &val) const noexcept -> std::size_t
    {
        return std::apply([](auto &...arg) { return aeon::common::hash_combined(arg...); }, val);
    }
};

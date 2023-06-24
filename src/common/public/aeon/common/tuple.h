// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/common/concepts.h>
#include <tuple>

namespace aeon::common
{

/*!
 * Create a tuple from a struct. Due to technical limitations, the amount of values the struct can have is limited (much
 * like C++98-style variadic templates)
 *
 * Currently the member limit is 20. This may expand in the future should it be needed.
 */
template <typename T>
auto make_tuple(T &&object) noexcept
{
    if constexpr (concepts::is_brace_constructible_v<
                      std::decay_t<T>, concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                      concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                      concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                      concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                      concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                      concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                      concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19,
                               p20);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8, p9] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8, p9);
    }
    else if constexpr (concepts::is_brace_constructible_v<
                           std::decay_t<T>, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible,
                           concepts::any_convertible, concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7, p8] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7, p8);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6, p7] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6, p7);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5, p6] = object;
        return std::make_tuple(p1, p2, p3, p4, p5, p6);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4, p5] = object;
        return std::make_tuple(p1, p2, p3, p4, p5);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible,
                                                          concepts::any_convertible>)
    {
        auto &&[p1, p2, p3, p4] = object;
        return std::make_tuple(p1, p2, p3, p4);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible, concepts::any_convertible>)
    {
        auto &&[p1, p2, p3] = object;
        return std::make_tuple(p1, p2, p3);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible,
                                                          concepts::any_convertible>)
    {
        auto &&[p1, p2] = object;
        return std::make_tuple(p1, p2);
    }
    else if constexpr (concepts::is_brace_constructible_v<std::decay_t<T>, concepts::any_convertible>)
    {
        auto &&[p1] = object;
        return std::make_tuple(p1);
    }
    else
    {
        return std::make_tuple();
    }
}

/*!
 * Like std::visit, but for all values in a tuple.
 */
template <typename callable_t, concepts::tuple_like T>
inline void tuple_visit(callable_t &&callable, const T &tuple)
{
    std::apply([&callable](const auto &...args) { ((callable(args)), ...); }, tuple);
}

} // namespace aeon::common

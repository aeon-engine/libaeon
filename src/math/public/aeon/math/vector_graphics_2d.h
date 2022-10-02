// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/math/vector2.h>
#include <aeon/math/circle.h>
#include <aeon/math/rectangle.h>
#include <aeon/math/math.h>
#include <vector>
#include <concepts>

namespace aeon::math
{

template <std::floating_point T, std::integral U>
inline void path_arc(std::vector<vector2<T>> &steps, const vector2<T> &center, const T radius, const T min_angle,
                     const T max_angle, const U num_segments)
{
    if (approximately_zero(radius))
    {
        steps.push_back(center);
        return;
    }

    steps.reserve(std::size(steps) + num_segments);

    for (auto i = 0; i <= num_segments; ++i)
    {
        const auto a = min_angle + (static_cast<T>(i) / static_cast<T>(num_segments)) * (max_angle - min_angle);
        steps.emplace_back(center.x + std::cos(a) * radius, center.y + std::sin(a) * radius);
    }
}

template <std::floating_point T, std::integral U>
[[nodiscard]] inline auto path_arc(const vector2<T> &center, const T radius, const T min_angle, const T max_angle,
                                   const U num_segments)
{
    std::vector<vector2<T>> steps;
    path_arc(steps, center, radius, min_angle, max_angle, num_segments);
    return steps;
}

template <std::floating_point T, std::integral U>
inline void path_circle(std::vector<vector2<T>> &steps, const circle<T> &circle, const U num_segments)
{
    const auto max_angle = constants<T>::tau * (static_cast<T>(num_segments) - T(1.0)) / static_cast<T>(num_segments);
    path_arc(steps, center(circle), radius(circle), T(0.0), max_angle, num_segments - 1);
}

template <std::floating_point T, std::integral U>
inline void path_circle(std::vector<vector2<T>> &steps, const vector2<T> &center, const T radius, const U num_segments)
{
    path_circle(steps, circle{center, radius}, num_segments);
}

template <std::floating_point T, std::integral U>
[[nodiscard]] inline auto path_circle(const circle<T> &circle, const U num_segments)
{
    const auto max_angle = constants<T>::tau * (static_cast<T>(num_segments) - T(1.0)) / static_cast<T>(num_segments);
    return path_arc(center(circle), radius(circle), T(0.0), max_angle, num_segments - 1);
}

template <std::floating_point T, std::integral U>
[[nodiscard]] inline auto path_circle(const vector2<T> &center, const T radius, const U num_segments)
{
    return path_circle(circle{center, radius}, num_segments);
}

template <std::floating_point T>
inline void path_rectangle(std::vector<vector2<T>> &steps, const rectangle<T> &rectangle)
{
    steps.reserve(std::size(steps) + 4);
    steps.push_back(left_top(rectangle));
    steps.push_back(right_top(rectangle));
    steps.push_back(right_bottom(rectangle));
    steps.push_back(left_bottom(rectangle));
}

template <std::floating_point T>
[[nodiscard]] inline auto path_rectangle(const rectangle<T> &rectangle)
{
    std::vector<vector2<T>> steps;
    path_rectangle(steps, rectangle);
    return steps;
}

template <std::floating_point T>
inline void path_rounded_rectangle(std::vector<vector2<T>> &steps, const rectangle<T> &rectangle,
                                   const T left_top_radius, const T right_top_radius, const T right_bottom_radius,
                                   const T left_bottom_radius)
{
    if (approximately_zero(left_top_radius))
    {
        steps.push_back(left_top(rectangle));
    }
    else
    {
        path_arc(steps, math::vector2<T>{left_top(rectangle) + math::vector2<T>{left_top_radius, left_top_radius}},
                 left_top_radius, math::constants<float>::pi, math::constants<float>::pi + math::constants<float>::pi_2,
                 10);
    }

    if (approximately_zero(right_top_radius))
    {
        steps.push_back(right_top(rectangle));
    }
    else
    {
        path_arc(steps, math::vector2<T>{right_top(rectangle) + math::vector2<T>{-right_top_radius, right_top_radius}},
                 right_top_radius, math::constants<float>::pi + math::constants<float>::pi_2,
                 math::constants<float>::tau, 10);
    }

    if (approximately_zero(right_bottom_radius))
    {
        steps.push_back(right_bottom(rectangle));
    }
    else
    {
        path_arc(
            steps,
            math::vector2<T>{right_bottom(rectangle) + math::vector2<T>{-right_bottom_radius, -right_bottom_radius}},
            right_bottom_radius, 0.0f, math::constants<float>::pi_2, 10);
    }

    if (approximately_zero(left_bottom_radius))
    {
        steps.push_back(left_bottom(rectangle));
    }
    else
    {
        path_arc(steps,
                 math::vector2<T>{left_bottom(rectangle) + math::vector2<T>{left_bottom_radius, -left_bottom_radius}},
                 left_bottom_radius, math::constants<float>::pi_2, math::constants<float>::pi, 10);
    }
}

template <std::floating_point T>
[[nodiscard]] inline auto path_rounded_rectangle(const rectangle<T> &rectangle, const T left_top_radius,
                                                 const T right_top_radius = 0, const T right_bottom_radius = 0,
                                                 const T left_bottom_radius = 0)
{
    std::vector<vector2<T>> steps;
    path_rounded_rectangle(steps, rectangle, left_top_radius, right_top_radius, right_bottom_radius,
                           left_bottom_radius);
    return steps;
}

} // namespace aeon::math

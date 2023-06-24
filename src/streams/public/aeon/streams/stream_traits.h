// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/streams/filters/filter.h>
#include <aeon/streams/devices/device.h>
#include <aeon/streams/tags.h>
#include <type_traits>

namespace aeon::streams
{

namespace internal
{

template <typename T, typename U>
struct has_category_tag
{
    static constexpr auto value = std::is_base_of<U, typename std::remove_reference_t<T>::category>::value;
};

template <typename T, typename U>
inline constexpr auto has_category_tag_v = has_category_tag<T, U>::value;

} // namespace internal

template <typename T>
inline constexpr auto is_input_v = internal::has_category_tag_v<T, input_tag>;

template <typename T>
inline constexpr auto is_input_seekable_v = internal::has_category_tag_v<T, input_seekable_tag>;

template <typename T>
inline constexpr auto is_output_v = internal::has_category_tag_v<T, output_tag>;

template <typename T>
inline constexpr auto is_output_seekable_v = internal::has_category_tag_v<T, output_seekable_tag>;

template <typename T>
inline constexpr auto is_flushable_v = internal::has_category_tag_v<T, flushable_tag>;

template <typename T>
inline constexpr auto has_eof_v = internal::has_category_tag_v<T, has_eof_tag>;

template <typename T>
inline constexpr auto has_status_v = internal::has_category_tag_v<T, has_status_tag>;

template <typename T>
inline constexpr auto has_size_v = internal::has_category_tag_v<T, has_size_tag>;

template <typename T>
inline constexpr auto is_filter_v = std::is_base_of_v<filter, T>;

template <typename T>
inline constexpr auto is_device_v = std::is_base_of_v<device, T>;

template <typename... T>
inline constexpr auto is_any_input_v = std::disjunction_v<internal::has_category_tag<T, input_tag>...>;

template <typename... T>
inline constexpr auto is_any_input_seekable_v =
    std::disjunction_v<internal::has_category_tag<T, input_seekable_tag>...>;

template <typename... T>
inline constexpr auto is_any_output_v = std::disjunction_v<internal::has_category_tag<T, output_tag>...>;

template <typename... T>
inline constexpr auto is_any_output_seekable_v =
    std::disjunction_v<internal::has_category_tag<T, output_seekable_tag>...>;

template <typename... T>
inline constexpr auto is_any_flushable_v = std::disjunction_v<internal::has_category_tag<T, flushable_tag>...>;

template <typename... T>
inline constexpr auto has_any_eof_v = std::disjunction_v<internal::has_category_tag<T, has_eof_tag>...>;

template <typename... T>
inline constexpr auto has_any_size_v = std::disjunction_v<internal::has_category_tag<T, has_size_tag>...>;

template <typename... T>
inline constexpr auto has_any_status_v = std::disjunction_v<internal::has_category_tag<T, has_status_tag>...>;

} // namespace aeon::streams

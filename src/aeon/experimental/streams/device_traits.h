/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#pragma once

#include <type_traits>

namespace aeon
{
namespace experimental
{
namespace streams
{
namespace detail
{

template<typename T>
struct has_device_read_method
{
private:
    template<typename U> static auto test(int) ->
        decltype(
            std::declval<U>().read(
                std::declval<char*>(),
                std::declval<const std::streamsize>()
            ) == 1, std::true_type()
        );

    template<typename> static std::false_type test(...);

public:
    static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
struct has_device_write_method
{
private:
    template<typename U> static auto test(int) ->
        decltype(
            std::declval<U>().write(
                std::declval<const char*>(),
                std::declval<const std::streamsize>()
            ) == 1, std::true_type()
            );

    template<typename> static std::false_type test(...);

public:
    static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

} // namespace detail
} // namespace streams
} // namespace experimental
} // namespace aeon

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

#include <ios>
#include <iosfwd>
#include <type_traits>

namespace aeon
{
namespace experimental
{
namespace streams
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

struct device
{
    device() = default;
    virtual ~device() = default;

    virtual std::streamsize read(char *data, const std::streamsize size) = 0;
    virtual std::streamsize peek(char *data, const std::streamsize size) = 0;
    virtual std::streamsize write(const char *data, const std::streamsize size) = 0;

    virtual std::streamoff tell() = 0;
    virtual std::streamoff tellw() = 0;

    virtual std::streamoff seek(const std::streamoff offset, const std::ios_base::seekdir direction) = 0;
    virtual std::streamoff seekw(const std::streamoff offset, const std::ios_base::seekdir direction) = 0;
};

/*template <typename device_t>
struct stream
{
    auto read(char *data, const std::streamsize size) -> decltype(device_.read(data, size), std::streamsize())
    {
    }

    device_t device_;
};*/

} // namespace streams
} // namespace experimental
} // namespace aeon

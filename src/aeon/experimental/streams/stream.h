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

namespace aeon
{
namespace experimental
{
namespace streams
{

struct source
{
    source() = default;
    virtual ~source() = default;

    virtual std::streamsize read(char *data, std::streamsize size) = 0;
};

struct sink
{
    sink() = default;
    virtual ~sink() = default;

    virtual std::streamsize write(const char *data, std::streamsize size) = 0;
};

struct seekable
{
    seekable() = default;
    virtual ~seekable() = default;

    virtual std::streamoff seek(std::streamoff offset, std::ios_base::seekdir direction) = 0;
};

struct device : source, sink {};
struct seekable_device : device, seekable {};

template <typename device_t>
struct stream_traits
{
    using is_source = std::is_convertible<device_t*, source*>;
    using is_sink = std::is_convertible<device_t*, sink*>;
    using is_seekable = std::is_convertible<device_t*, seekable*>;

    using is_valid = std::conditional<
        is_seekable::value,
        std::conditional<
            is_source::value,
            std::integral_constant<bool, std::true_type::value>::type,
            std::conditional<
                is_sink::value,
                std::integral_constant<bool, std::true_type::value>::type,
                std::integral_constant<bool, std::false_type::value>::type>>,
        std::integral_constant<bool, std::true_type::value>::type>;
};

template <typename device_t>
class stream
{
};

} // namespace streams
} // namespace experimental
} // namespace aeon

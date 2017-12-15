/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace aeon::utility
{

/*!
 * UUID class based on boost::uuid.
 */
class uuid
{
public:
    using value_type = std::uint8_t;
    using data_type = std::array<value_type, 16>;

    enum class variant_type
    {
        variant_ncs,
        variant_rfc_4122,
        variant_microsoft,
        variant_future
    };

    enum class version_type
    {
        version_unknown = -1,
        version_time_based = 1,
        version_dce_security = 2,
        version_name_based_md5 = 3,
        version_random_number_based = 4,
        version_name_based_sha1 = 5
    };

    uuid();
    explicit uuid(const std::string &str);
    ~uuid();

    uuid(const uuid &) = default;
    auto operator=(const uuid &) -> uuid & = default;

    uuid(uuid &&) = default;
    auto operator=(uuid &&) -> uuid & = default;

    auto begin() -> data_type::iterator;
    auto begin() const -> data_type::const_iterator;
    auto end() -> data_type::iterator;
    auto end() const -> data_type::const_iterator;

    bool is_nil() const;

    auto variant() const -> variant_type;

    auto version() const -> version_type;

    auto str() const -> std::string;

    auto size() const -> std::size_t;

    static uuid generate();

    data_type data;
};

bool operator==(uuid const &lhs, uuid const &rhs);
bool operator<(uuid const &lhs, uuid const &rhs);

inline bool operator!=(uuid const &lhs, uuid const &rhs)
{
    return !(lhs == rhs);
}

inline bool operator>(uuid const &lhs, uuid const &rhs)
{
    return rhs < lhs;
}
inline bool operator<=(uuid const &lhs, uuid const &rhs)
{
    return !(rhs < lhs);
}

inline bool operator>=(uuid const &lhs, uuid const &rhs)
{
    return !(lhs < rhs);
}
} // namespace aeon::utility

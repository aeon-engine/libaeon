/*
 * Copyright (c) 2012-2018 Robin Degen
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

#include <aeon/types/uuid.h>
#include <aeon/common/literals.h>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <cstring>

namespace aeon::types
{

namespace detail
{

static auto to_char(const size_t i) noexcept
{
    if (i <= 9)
        return static_cast<char>('0' + i);

    return static_cast<char>('a' + (i - 10));
}

static auto get_next_char(std::string::const_iterator &begin, std::string::const_iterator &end)
{
    if (begin == end)
        throw std::out_of_range("get_next_char");

    return *begin++;
}

static auto is_open_brace(const char c) noexcept
{
    return (c == '{');
}

static auto is_dash(const char c) noexcept
{
    return c == '-';
}

static auto get_value(const char c) noexcept
{
    static char const *const digits_begin = "0123456789abcdefABCDEF";
    static char const *const digits_end = digits_begin + 22;

    static unsigned char const values[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15, static_cast<unsigned char>(-1)};

    char const *d = std::find(digits_begin, digits_end, c);
    return values[d - digits_begin];
}

static void check_close_brace(const char c, const char open_brace)
{
    if (!(open_brace == '{' && c == '}'))
        throw std::logic_error("Unexpected close brace.");
}
} // namespace detail

uuid::uuid() noexcept
    : data()
{
    std::fill(data.begin(), data.end(), 0_uint8_t);
}

uuid::uuid(const std::string &str)
    : data()
{
    auto begin = str.begin();
    auto end = str.end();

    // check open brace
    auto c = detail::get_next_char(begin, end);
    const bool has_open_brace = detail::is_open_brace(c);
    const auto open_brace_char = c;
    if (has_open_brace)
        c = detail::get_next_char(begin, end);

    bool has_dashes = false;

    int i = 0;
    for (auto &val : data)
    {
        if (i != 0)
        {
            c = detail::get_next_char(begin, end);
        }

        if (i == 4)
        {
            has_dashes = detail::is_dash(c);
            if (has_dashes)
            {
                c = detail::get_next_char(begin, end);
            }
        }

        if (has_dashes)
        {
            if (i == 6 || i == 8 || i == 10)
            {
                if (detail::is_dash(c))
                {
                    c = detail::get_next_char(begin, end);
                }
                else
                {
                    throw std::logic_error("Unexpected dash.");
                }
            }
        }

        val = detail::get_value(c);

        c = detail::get_next_char(begin, end);
        val <<= 4;
        val |= detail::get_value(c);
        ++i;
    }

    // check close brace
    if (has_open_brace)
    {
        c = detail::get_next_char(begin, end);
        detail::check_close_brace(c, open_brace_char);
    }
}

uuid::~uuid() noexcept = default;

auto uuid::begin() noexcept -> data_type::iterator
{
    return data.begin();
}

auto uuid::begin() const noexcept -> data_type::const_iterator
{
    return data.cbegin();
}

auto uuid::end() noexcept -> data_type::iterator
{
    return data.end();
}

auto uuid::end() const noexcept -> data_type::const_iterator
{
    return data.cend();
}

bool uuid::is_nil() const noexcept
{
    for (auto i : data)
    {
        if (i != 0)
            return false;
    }
    return true;
}

auto uuid::variant() const noexcept -> variant_type
{
    // variant is stored in octet 7
    // which is index 8, since indexes count backwards
    const auto octet7 = data[8]; // octet 7 is array index 8
    if ((octet7 & 0x80) == 0x00)
    { // 0b0xxxxxxx
        return variant_type::variant_ncs;
    }
    else if ((octet7 & 0xC0) == 0x80)
    { // 0b10xxxxxx
        return variant_type::variant_rfc_4122;
    }
    else if ((octet7 & 0xE0) == 0xC0)
    { // 0b110xxxxx
        return variant_type::variant_microsoft;
    }
    else
    {
        return variant_type::variant_future;
    }
}

auto uuid::version() const noexcept -> version_type
{
    // version is stored in octet 9
    // which is index 6, since indexes count backwards
    const auto octet9 = data[6];
    if ((octet9 & 0xF0) == 0x10)
    {
        return version_type::version_time_based;
    }
    else if ((octet9 & 0xF0) == 0x20)
    {
        return version_type::version_dce_security;
    }
    else if ((octet9 & 0xF0) == 0x30)
    {
        return version_type::version_name_based_md5;
    }
    else if ((octet9 & 0xF0) == 0x40)
    {
        return version_type::version_random_number_based;
    }
    else if ((octet9 & 0xF0) == 0x50)
    {
        return version_type::version_name_based_sha1;
    }
    else
    {
        return version_type::version_unknown;
    }
}

auto uuid::str() const -> std::string
{
    std::string result;
    result.reserve(36);

    auto i = 0_size_t;
    for (const auto val : data)
    {
        const size_t hi = (val >> 4) & 0x0F;
        result += detail::to_char(hi);

        const size_t lo = val & 0x0F;
        result += detail::to_char(lo);

        if (i == 3 || i == 5 || i == 7 || i == 9)
        {
            result += '-';
        }

        ++i;
    }
    return result;
}

auto uuid::size() const noexcept -> std::size_t
{
    return data.size();
}

auto uuid::generate() -> uuid
{
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<unsigned long> uniform_dist;

    uuid u;

    int i = 0;
    auto random_value = uniform_dist(e1);
    for (auto &val : u.data)
    {
        if (i == sizeof(unsigned long))
        {
            random_value = uniform_dist(e1);
            i = 0;
        }

        val = static_cast<uuid::value_type>((random_value >> (i * 8)) & 0xFF);
        ++i;
    }

    // set variant
    // must be 0b10xxxxxx
    *(u.begin() + 8) &= 0xBF;
    *(u.begin() + 8) |= 0x80;

    // set version
    // must be 0b0100xxxx
    *(u.begin() + 6) &= 0x4F; // 0b01001111
    *(u.begin() + 6) |= 0x40; // 0b01000000

    return u;
}

auto uuid::nil() noexcept -> uuid
{
    return {};
}

bool operator==(uuid const &lhs, uuid const &rhs) noexcept
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator<(uuid const &lhs, uuid const &rhs) noexcept
{
    return std::memcmp(lhs.data.data(), rhs.data.data(), lhs.data.size()) < 0;
}
} // namespace aeon::types

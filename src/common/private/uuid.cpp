// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/uuid.h>
#include <aeon/common/literals.h>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <cstring>

namespace aeon::common
{

namespace detail
{

[[nodiscard]] static auto to_char(const size_t i) noexcept
{
    if (i <= 9)
        return static_cast<char>('0' + i);

    return static_cast<char>('a' + (i - 10));
}

[[nodiscard]] static auto get_next_char(std::string_view::const_iterator &begin, std::string_view::const_iterator &end,
                                        char &c) noexcept
{
    if (begin == end)
        return false;

    c = *begin++;
    return true;
}

[[nodiscard]] static auto is_open_brace(const char c) noexcept
{
    return (c == '{');
}

[[nodiscard]] static auto is_dash(const char c) noexcept
{
    return c == '-';
}

[[nodiscard]] static auto get_value(const char c) noexcept
{
    static char const *const digits_begin = "0123456789abcdefABCDEF";
    static char const *const digits_end = digits_begin + 22;

    static unsigned char const values[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 10, 11, 12, 13, 14, 15, static_cast<unsigned char>(-1)};

    char const *d = std::find(digits_begin, digits_end, c);
    return values[d - digits_begin];
}

[[nodiscard]] static auto check_close_brace(const char c, const char open_brace) noexcept -> bool
{
    return open_brace == '{' && c == '}';
}

template <typename T>
[[nodiscard]] auto to_string(const uuid::data_type &data) -> T
{
    T result;
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

} // namespace detail

uuid::uuid() noexcept
    : data{}
{
    std::fill(data.begin(), data.end(), 0_uint8_t);
}

uuid::uuid(data_type data) noexcept
    : data{data}
{
}

uuid::~uuid() noexcept = default;

[[nodiscard]] auto uuid::begin() noexcept -> data_type::iterator
{
    return data.begin();
}

[[nodiscard]] auto uuid::begin() const noexcept -> data_type::const_iterator
{
    return data.cbegin();
}

[[nodiscard]] auto uuid::end() noexcept -> data_type::iterator
{
    return data.end();
}

[[nodiscard]] auto uuid::end() const noexcept -> data_type::const_iterator
{
    return data.cend();
}

[[nodiscard]] auto uuid::is_nil() const noexcept -> bool
{
    for (auto i : data)
    {
        if (i != 0)
            return false;
    }
    return true;
}

[[nodiscard]] auto uuid::variant() const noexcept -> variant_type
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

[[nodiscard]] auto uuid::version() const noexcept -> version_type
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

[[nodiscard]] auto uuid::str() const -> std::string
{
    return detail::to_string<std::string>(data);
}

auto uuid::u8str() const -> std::u8string
{
    return detail::to_string<std::u8string>(data);
}

[[nodiscard]] auto uuid::size() const noexcept -> std::size_t
{
    return data.size();
}

[[nodiscard]] auto uuid::generate() noexcept -> uuid
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

[[nodiscard]] auto uuid::nil() noexcept -> uuid
{
    return {};
}

auto uuid::parse(const std::string_view &str) -> uuid
{
    const auto result = try_parse(str);

    if (!result)
        throw uuid_parse_exception{};

    return *result;
}

auto uuid::try_parse(const std::string_view &str) noexcept -> std::optional<uuid>
{
    auto begin = str.begin();
    auto end = str.end();

    char c;

    // check open brace
    if (!detail::get_next_char(begin, end, c))
        return std::nullopt;

    const bool has_open_brace = detail::is_open_brace(c);
    const auto open_brace_char = c;

    if (has_open_brace)
    {
        if (!detail::get_next_char(begin, end, c))
            return std::nullopt;
    }

    bool has_dashes = false;

    int i = 0;
    data_type data;

    for (auto &val : data)
    {
        if (i != 0)
        {
            if (!detail::get_next_char(begin, end, c))
                return std::nullopt;
        }

        if (i == 4)
        {
            has_dashes = detail::is_dash(c);
            if (has_dashes)
            {
                if (!detail::get_next_char(begin, end, c))
                    return std::nullopt;
            }
        }

        if (has_dashes)
        {
            if (i == 6 || i == 8 || i == 10)
            {
                if (detail::is_dash(c))
                {
                    if (!detail::get_next_char(begin, end, c))
                        return std::nullopt;
                }
                else
                {
                    return std::nullopt;
                }
            }
        }

        val = detail::get_value(c);

        if (!detail::get_next_char(begin, end, c))
            return std::nullopt;

        val <<= 4;
        val |= detail::get_value(c);
        ++i;
    }

    // check close brace
    if (has_open_brace)
    {
        if (!detail::get_next_char(begin, end, c))
            return std::nullopt;

        if (!detail::check_close_brace(c, open_brace_char))
            return std::nullopt;
    }

    return uuid{data};
}

bool operator==(uuid const &lhs, uuid const &rhs) noexcept
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator<(uuid const &lhs, uuid const &rhs) noexcept
{
    return std::memcmp(lhs.data.data(), rhs.data.data(), lhs.data.size()) < 0;
}
} // namespace aeon::common

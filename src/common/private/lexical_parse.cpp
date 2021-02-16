// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/common/lexical_parse.h>
#include <aeon/common/from_chars.h>
#include <cctype>

namespace aeon::common::lexical_parse
{

namespace internal
{

template <typename T>
static auto is_possibly_double(const std::basic_string_view<T> &str) noexcept
{
    for (const auto c : str)
    {
        if (c == 'e' || c == 'E' || c == '.')
            return true;
    }

    return false;
}

template <typename T>
auto number(const std::basic_string_view<T> &str) -> lexical_parse_result
{
    if (internal::is_possibly_double(str))
    {
        auto value = 0.0;
        auto [ptr, ec] = from_chars(str, value);

        if (ec != std::errc{})
            throw lexical_parse_exception{};

        return {value, static_cast<std::size_t>(ptr - std::data(str))};
    }

    std::int64_t value = 0;
    auto [ptr, ec] = from_chars(str, value);

    if (ec != std::errc{})
        throw lexical_parse_exception{};

    return {value, static_cast<std::size_t>(ptr - std::data(str))};
}

template <typename T>
auto extract_number_string(const std::basic_string_view<T> &str) noexcept -> std::basic_string_view<T>
{
    std::size_t end_offset = 0;
    for (const auto c : str)
    {
        if (!std::isdigit(c) && c != 'e' && c != 'E' && c != '.')
            return str.substr(0, end_offset);

        ++end_offset;
    }

    return {};
}

} // namespace internal

auto number(const std::string_view &str) -> lexical_parse_result
{
    return internal::number(str);
}

auto number(const std::u8string_view &str) -> lexical_parse_result
{
    return internal::number(str);
}

auto extract_number_string(const std::string_view &str) noexcept -> std::string_view
{
    return internal::extract_number_string(str);
}

auto extract_number_string(const std::u8string_view &str) noexcept -> std::u8string_view
{
    return internal::extract_number_string(str);
}

} // namespace aeon::common::lexical_parse

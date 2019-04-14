// Copyright (c) 2012-2019 Robin Degen

#include <aeon/common/lexical_parse.h>
#include <charconv>
#include <cctype>

namespace aeon::common::lexical_parse
{

namespace internal
{

static auto is_possibly_double(const std::string_view &str) noexcept
{
    for (const auto c : str)
    {
        if (c == 'e' || c == 'E' || c == '.')
            return true;
    }

    return false;
}

} // namespace internal

auto number(const std::string_view &str) -> lexical_parse_result
{
    if (internal::is_possibly_double(str))
    {
        auto value = 0.0;
        const auto [ptr, ec] = std::from_chars(std::data(str), std::data(str) + std::size(str), value);

        if (ec != std::errc{})
            throw lexical_parse_exception{};

        return {value, static_cast<std::size_t>(ptr - std::data(str))};
    }

    std::int64_t value = 0;
    const auto [ptr, ec] = std::from_chars(std::data(str), std::data(str) + std::size(str), value);

    if (ec != std::errc{})
        throw lexical_parse_exception{};

    return {value, static_cast<std::size_t>(ptr - std::data(str))};
}

auto extract_number_string(const std::string_view &str) noexcept -> std::string_view
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

} // namespace aeon::common::lexical_parse
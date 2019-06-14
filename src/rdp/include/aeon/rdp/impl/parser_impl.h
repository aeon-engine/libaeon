// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/rdp/parse_result.h>
#include <aeon/common/compilers.h>
#include <aeon/common/string.h>

namespace aeon::rdp
{

template <typename iterator_t>
inline parser::parser(iterator_t begin, iterator_t end)
    : view_{common::string::make_string_view(begin, end)}
    , current_{std::begin(view_)}
{
    aeon_assert(!std::empty(view_), "Given string_view can not be empty.");
}

template <typename matcher_t>
inline auto parser::match(matcher_t pred) noexcept -> parse_result<std::string_view>
{
    if (AEON_UNLIKELY(eof()))
        return unmatched{};

    auto itr = current_;

    while (itr != std::end(view_) && pred(*itr))
        ++itr;

    if (itr == current_)
        return unmatched{};

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

template <typename matcher_t>
inline auto parser::match_indexed(matcher_t pred) noexcept -> parse_result<std::string_view>
{
    if (AEON_UNLIKELY(eof()))
        return unmatched{};

    auto itr = current_;

    while (itr != std::end(view_) && pred(*itr, std::distance(current_, itr)))
        ++itr;

    if (itr == current_)
        return unmatched{};

    const auto result = common::string::make_string_view(current_, itr);
    current_ = itr;
    return matched{result};
}

} // namespace aeon::rdp

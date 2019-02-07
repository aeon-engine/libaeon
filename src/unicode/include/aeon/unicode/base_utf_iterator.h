// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <string_view>
#include <iterator>
#include <cstdint>
#include <limits>

namespace aeon::unicode
{

template <typename string_view_type_t, typename char_type_t>
class base_utf_iterator
{
public:
    using value_type = const char32_t;
    using pointer = const char32_t *;
    using reference = const char32_t &;
    using difference_type = std::int32_t;
    using iterator_category = std::forward_iterator_tag;

    base_utf_iterator(const base_utf_iterator &) = default;
    auto operator=(const base_utf_iterator &) -> base_utf_iterator & = default;

    base_utf_iterator(base_utf_iterator &&) noexcept = default;
    auto operator=(base_utf_iterator &&) noexcept -> base_utf_iterator & = default;

    auto offset() const noexcept
    {
        return offset_;
    }

    auto pos() const noexcept
    {
        return cp_pos_;
    }

    auto character() const noexcept
    {
        return char_;
    }

    auto character_str() const noexcept
    {
        return string_view_type_t{reinterpret_cast<const typename string_view_type_t::value_type *>(str_ + offset_),
                                  static_cast<typename string_view_type_t::size_type>(next_offset_ - offset_)};
    }

    auto operator*() const noexcept
    {
        return char_;
    }

    auto operator-> () const noexcept
    {
        return &char_;
    }

protected:
    explicit base_utf_iterator(const string_view_type_t &str) noexcept
        : str_{reinterpret_cast<const char_type_t *>(std::data(str))}
        , len_{static_cast<std::int32_t>(std::size(str))}
        , offset_{0}
        , next_offset_{0}
        , cp_pos_{0}
        , char_{0}
    {
        aeon_assert(std::size(str) < std::numeric_limits<std::int32_t>::max(), "String too long.");
    }

    explicit base_utf_iterator(const string_view_type_t &str, const std::int32_t offset) noexcept
        : str_{reinterpret_cast<const char_type_t *>(std::data(str))}
        , len_{static_cast<std::int32_t>(std::size(str))}
        , offset_{offset}
        , next_offset_{0}
        , cp_pos_{0}
        , char_{0}
    {
        aeon_assert(std::size(str) < std::numeric_limits<std::int32_t>::max(), "String too long.");
    }

    ~base_utf_iterator() = default;

    const char_type_t *str_;
    std::int32_t len_;
    std::int32_t offset_;
    std::int32_t next_offset_;
    std::int32_t cp_pos_;
    char32_t char_;
};

} // namespace aeon::unicode

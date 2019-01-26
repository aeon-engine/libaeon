// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/common/assert.h>
#include <stdexcept>

namespace aeon::common::utf8
{

inline utf8_string_iterator::utf8_string_iterator(const char *begin, const char *end)
    : utf8_string_iterator{begin, end, begin}
{
}

inline utf8_string_iterator::utf8_string_iterator(const char *begin, const char *end, const char *offset)
    : begin_{begin}
    , end_{end}
    , offset_{offset}
    , current_{0}
{
    if (offset_ == end_)
        return;

    consume_bom();
}

inline auto utf8_string_iterator::operator*() noexcept -> reference
{
    read_codepoint(offset_, end_, current_);
    return current_;
}

inline auto utf8_string_iterator::operator-> () noexcept -> pointer
{
    return &(operator*());
}

inline auto utf8_string_iterator::operator++() -> utf8_string_iterator &
{
    advance_to_next_codepoint(offset_, end_);
    return *this;
}

inline auto utf8_string_iterator::operator++(int) -> utf8_string_iterator
{
    const auto temp(*this);
    ++*this;
    return temp;
}

inline auto utf8_string_iterator::operator==(const utf8_string_iterator &other) const noexcept -> bool
{
    aeon_assert(begin_ == other.begin_ && end_ == other.end_, "utf8_string_iterator range mismatch.");
    return offset_ == other.offset_;
}

inline auto utf8_string_iterator::operator!=(const utf8_string_iterator &other) const noexcept -> bool
{
    return !(*this == other);
}

inline void utf8_string_iterator::consume_bom()
{
    if (end_ - offset_ < 3)
        return;

    const auto data = reinterpret_cast<const unsigned char *>(offset_);

    if (data[0] == 0xEF && data[1] == 0xBB && data[2] == 0xBF)
        offset_ += 3;
}

inline utf8_string_view::utf8_string_view(const std::string_view view) noexcept
    : view_{view}
{
}

inline auto utf8_string_view::begin() const noexcept
{
    return utf8_string_iterator{&view_.front(), &view_.back() + 1};
}

inline auto utf8_string_view::end() const noexcept
{
    return utf8_string_iterator{&view_.front(), &view_.back() + 1, &view_.back() + 1};
}

} // namespace aeon::common::utf8

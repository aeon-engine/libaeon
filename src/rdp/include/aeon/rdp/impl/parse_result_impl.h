// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/rdp/parser.h>
#include <aeon/common/assert.h>

namespace aeon::rdp
{

template <typename T>
inline matched<T>::matched() noexcept
    : value_{}
{
    if constexpr (std::is_same_v<T, bool>)
        value_ = true;
}

template <typename T>
inline matched<T>::matched(T value) noexcept(std::is_nothrow_move_constructible_v<T>)
    : value_{std::move(value)}
{
}

template <typename T>
inline auto matched<T>::value() const noexcept -> const T &
{
    return value_;
}

inline parse_error::parse_error(const parser &parser, std::string message) noexcept
    : cursor_(parser.cursor())
    , message_(std::move(message))
{
}

inline auto parse_error::cursor() const noexcept -> const rdp::cursor &
{
    return cursor_;
}

inline auto parse_error::message() const noexcept -> const std::string &
{
    return message_;
}

template <typename T>
inline parse_result<T>::parse_result() noexcept
    : result_{unmatched{}}
{
}

template <typename T>
inline parse_result<T>::parse_result(unmatched result) noexcept
    : result_{std::move(result)}
{
}

template <typename T>
inline parse_result<T>::parse_result(matched<T> result) noexcept
    : result_{std::move(result)}
{
}

template <typename T>
inline parse_result<T>::parse_result(parse_error error)
    : result_{std::move(error)}
{
}

template <typename T>
inline auto parse_result<T>::result() const noexcept -> bool
{
    return result_.index() == 0;
}

template <typename T>
inline parse_result<T>::operator bool() const noexcept
{
    return result();
}

template <typename T>
inline auto parse_result<T>::value() const noexcept -> const T &
{
    aeon_assert(result(), "value should only be called if result() returns true.");
    return std::get<matched<T>>(result_).value();
}

template <typename T>
inline auto parse_result<T>::operator*() const noexcept -> const T &
{
    return value();
}

template <typename T>
inline auto parse_result<T>::is_error() const noexcept -> bool
{
    return result_.index() == 2;
}

template <typename T>
inline auto parse_result<T>::error() const noexcept -> const parse_error &
{
    aeon_assert(is_error(), "error should only be called if is_error() returns true.");
    return std::get<parse_error>(result_);
}

template <typename T>
inline auto parse_result<T>::is_unmatched() const noexcept -> bool
{
    return result_.index() == 1;
}

inline void print_parse_error(const parse_error &error)
{
    print_parse_error(error.cursor(), error.message());
}

inline void print_parse_error(const parse_error &error, std::ostream &stream)
{
    print_parse_error(error.cursor(), error.message(), stream);
}

template <typename T>
void print_parse_error(const parse_result<T> &result)
{
    aeon_assert(result.is_error(), "Can't print parse error for a result that doesn't contain a parse error.");
    print_parse_error(result.error());
}

template <typename T>
void print_parse_error(const parse_result<T> &result, std::ostream &stream)
{
    aeon_assert(result.is_error(), "Can't print parse error for a result that doesn't contain a parse error.");
    print_parse_error(result.error(), stream);
}

template <typename T>
inline auto operator==(const parse_result<T> &lhs, const unmatched) noexcept -> bool
{
    return lhs.is_unmatched();
}

template <typename T>
inline auto operator==(const unmatched, const parse_result<T> &rhs) noexcept -> bool
{
    return rhs.is_unmatched();
}

template <typename T>
inline auto operator==(const parse_result<T> &lhs, const T &rhs) noexcept -> bool
{
    if (!lhs.result())
        return false;

    return lhs.value() == rhs;
}

template <typename T>
inline auto operator==(const T &lhs, const parse_result<T> &rhs) noexcept -> bool
{
    if (!rhs.result())
        return false;

    return rhs.value() == lhs;
}

} // namespace aeon::rdp

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

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
    : value_(std::move(value))
{
}

template <typename T>
inline auto matched<T>::value() noexcept -> result_type &
{
    return value_;
}

template <typename T>
inline auto matched<T>::value() const noexcept -> const result_type &
{
    return value_;
}

template <common::concepts::string_view_like T>
inline parse_error<T>::parse_error(const parser<T> &parser, std::u8string message) noexcept
    : cursor_(parser.cursor())
    , message_(std::move(message))
{
}

template <common::concepts::string_view_like T>
inline auto parse_error<T>::cursor() const noexcept -> const rdp::cursor<T> &
{
    return cursor_;
}

template <common::concepts::string_view_like T>
inline auto parse_error<T>::message() const noexcept -> const std::u8string &
{
    return message_;
}

template <common::concepts::string_view_like T, typename ResultT>
inline parse_result<T, ResultT>::parse_result() noexcept
    : result_{unmatched{}}
{
}

template <common::concepts::string_view_like T, typename ResultT>
inline parse_result<T, ResultT>::parse_result(unmatched result) noexcept
    : result_{std::move(result)}
{
}

template <common::concepts::string_view_like T, typename ResultT>
inline parse_result<T, ResultT>::parse_result(matched<ResultT> result) noexcept
    : result_{std::move(result)}
{
}

template <common::concepts::string_view_like T, typename ResultT>
inline parse_result<T, ResultT>::parse_result(parse_error<T> error)
    : result_{std::move(error)}
{
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::result() const noexcept -> bool
{
    return result_.index() == 0;
}

template <common::concepts::string_view_like T, typename ResultT>
inline parse_result<T, ResultT>::operator bool() const noexcept
{
    return result();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::value() noexcept -> result_type &
{
    aeon_assert(result(), "value should only be called if result() returns true.");
    return std::get<matched<result_type>>(result_).value();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::value() const noexcept -> const result_type &
{
    aeon_assert(result(), "value should only be called if result() returns true.");
    return std::get<matched<result_type>>(result_).value();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::operator*() noexcept -> result_type &
{
    return value();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::operator*() const noexcept -> const result_type &
{
    return value();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::is_error() const noexcept -> bool
{
    return result_.index() == 2;
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::error() const noexcept -> const parse_error<T> &
{
    aeon_assert(is_error(), "error should only be called if is_error() returns true.");
    return std::get<parse_error<T>>(result_);
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto parse_result<T, ResultT>::is_unmatched() const noexcept -> bool
{
    return result_.index() == 1;
}

template <common::concepts::string_view_like T>
inline void print_parse_error(const parse_error<T> &error)
{
    print_parse_error<T>(error.cursor(), error.message());
}

template <common::concepts::string_view_like T>
inline void print_parse_error(const parse_error<T> &error, std::ostream &stream)
{
    print_parse_error<T>(error.cursor(), error.message(), stream);
}

template <common::concepts::string_view_like T, typename ResultT>
void print_parse_error(const parse_result<T, ResultT> &result)
{
    aeon_assert(result.is_error(), "Can't print parse error for a result that doesn't contain a parse error.");
    print_parse_error<T>(result.error());
}

template <common::concepts::string_view_like T, typename ResultT>
void print_parse_error(const parse_result<T, ResultT> &result, std::ostream &stream)
{
    aeon_assert(result.is_error(), "Can't print parse error for a result that doesn't contain a parse error.");
    print_parse_error<T>(result.error(), stream);
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const parse_result<T, ResultT> &lhs, const unmatched) noexcept -> bool
{
    return lhs.is_unmatched();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const unmatched, const parse_result<T, ResultT> &rhs) noexcept -> bool
{
    return rhs.is_unmatched();
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const parse_result<T, ResultT> &lhs, const ResultT &rhs) noexcept -> bool
{
    if (!lhs.result())
        return false;

    return lhs.value() == rhs;
}

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const ResultT &lhs, const parse_result<T, ResultT> &rhs) noexcept -> bool
{
    if (!rhs.result())
        return false;

    return rhs.value() == lhs;
}

} // namespace aeon::rdp

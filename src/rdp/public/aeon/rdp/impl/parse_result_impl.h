// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

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

inline parse_error::parse_error(const parser &parser, common::string message) noexcept
    : cursor_(parser.cursor())
    , message_(std::move(message))
{
}

inline auto parse_error::cursor() const noexcept -> const rdp::cursor &
{
    return cursor_;
}

inline auto parse_error::message() const noexcept -> const common::string &
{
    return message_;
}

template <typename ResultT>
inline parse_result<ResultT>::parse_result() noexcept
    : result_{unmatched{}}
{
}

template <typename ResultT>
inline parse_result<ResultT>::parse_result(unmatched result) noexcept
    : result_{std::move(result)}
{
}

template <typename ResultT>
inline parse_result<ResultT>::parse_result(matched<ResultT> result) noexcept
    : result_{std::move(result)}
{
}

template <typename ResultT>
inline parse_result<ResultT>::parse_result(parse_error error)
    : result_{std::move(error)}
{
}

template <typename ResultT>
inline auto parse_result<ResultT>::result() const noexcept -> bool
{
    return result_.index() == 0;
}

template <typename ResultT>
inline parse_result<ResultT>::operator bool() const noexcept
{
    return result();
}

template <typename ResultT>
inline auto parse_result<ResultT>::value() noexcept -> result_type &
{
    aeon_assert(result(), "value should only be called if result() returns true.");
    return std::get<matched<result_type>>(result_).value();
}

template <typename ResultT>
inline auto parse_result<ResultT>::value() const noexcept -> const result_type &
{
    aeon_assert(result(), "value should only be called if result() returns true.");
    return std::get<matched<result_type>>(result_).value();
}

template <typename ResultT>
inline auto parse_result<ResultT>::operator*() noexcept -> result_type &
{
    return value();
}

template <typename ResultT>
inline auto parse_result<ResultT>::operator*() const noexcept -> const result_type &
{
    return value();
}

template <typename ResultT>
inline auto parse_result<ResultT>::is_error() const noexcept -> bool
{
    return result_.index() == 2;
}

template <typename ResultT>
inline auto parse_result<ResultT>::error() const noexcept -> const parse_error &
{
    aeon_assert(is_error(), "error should only be called if is_error() returns true.");
    return std::get<parse_error>(result_);
}

template <typename ResultT>
inline auto parse_result<ResultT>::is_unmatched() const noexcept -> bool
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

template <typename ResultT>
void print_parse_error(const parse_result<ResultT> &result)
{
    aeon_assert(result.is_error(), "Can't print parse error for a result that doesn't contain a parse error.");
    print_parse_error(result.error());
}

template <typename ResultT>
void print_parse_error(const parse_result<ResultT> &result, std::ostream &stream)
{
    aeon_assert(result.is_error(), "Can't print parse error for a result that doesn't contain a parse error.");
    print_parse_error(result.error(), stream);
}

template <typename ResultT>
inline auto operator==(const parse_result<ResultT> &lhs, const unmatched) noexcept -> bool
{
    return lhs.is_unmatched();
}

template <typename ResultT>
inline auto operator==(const unmatched, const parse_result<ResultT> &rhs) noexcept -> bool
{
    return rhs.is_unmatched();
}

template <typename ResultT>
inline auto operator==(const parse_result<ResultT> &lhs, const ResultT &rhs) noexcept -> bool
{
    if (!lhs.result())
        return false;

    return lhs.value() == rhs;
}

template <typename ResultT>
inline auto operator==(const ResultT &lhs, const parse_result<ResultT> &rhs) noexcept -> bool
{
    if (!rhs.result())
        return false;

    return rhs.value() == lhs;
}

} // namespace aeon::rdp

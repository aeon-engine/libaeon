// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/rdp/cursor.h>
#include <type_traits>
#include <string>
#include <variant>

namespace aeon::rdp
{

template <common::concepts::string_view_like T>
class parser;

template <typename T = bool>
class matched
{
public:
    using result_type = T;

    explicit matched() noexcept;

    explicit matched(T value) noexcept(std::is_nothrow_move_constructible_v<T>);

    ~matched() = default;

    matched(const matched<T> &) noexcept(std::is_nothrow_copy_constructible_v<T>) = default;
    auto operator=(const matched<T> &) noexcept(std::is_nothrow_copy_assignable_v<T>) -> matched<T> & = default;

    matched(matched<T> &&) noexcept(std::is_nothrow_move_constructible_v<T>) = default;
    auto operator=(matched<T> &&) noexcept(std::is_nothrow_move_assignable_v<T>) -> matched<T> & = default;

    auto value() noexcept -> result_type &;

    auto value() const noexcept -> const result_type &;

private:
    result_type value_;
};

class unmatched final
{
};

template <common::concepts::string_view_like T>
class parse_error final
{
    template <common::concepts::string_view_like U, typename ResultT>
    friend class parse_result;

public:
    explicit parse_error(const parser<T> &parser, std::u8string message) noexcept;

    ~parse_error() = default;

    parse_error(const parse_error<T> &) = default;
    auto operator=(const parse_error<T> &) -> parse_error<T> & = default;

    parse_error(parse_error<T> &&) noexcept = default;
    auto operator=(parse_error<T> &&) noexcept -> parse_error<T> & = default;

    auto cursor() const noexcept -> const rdp::cursor<T> &;

    auto message() const noexcept -> const std::u8string &;

private:
    rdp::cursor<T> cursor_;
    std::u8string message_;
};

template <common::concepts::string_view_like T, typename ResultT = bool>
class parse_result final
{
public:
    using result_type = ResultT;

    parse_result() noexcept;
    parse_result(unmatched result) noexcept;
    parse_result(matched<ResultT> result) noexcept;
    parse_result(parse_error<T> error);

    ~parse_result() noexcept = default;

    parse_result(const parse_result<T, ResultT> &) = default;
    auto operator=(const parse_result<T, ResultT> &) -> parse_result<T, ResultT> & = default;

    parse_result(parse_result<T, ResultT> &&) noexcept = default;
    auto operator=(parse_result<T, ResultT> &&) noexcept -> parse_result<T, ResultT> & = default;

    auto result() const noexcept -> bool;

    operator bool() const noexcept;

    auto value() noexcept -> result_type &;

    auto value() const noexcept -> const result_type &;

    auto operator*() noexcept -> result_type &;

    auto operator*() const noexcept -> const result_type &;

    auto is_error() const noexcept -> bool;

    auto error() const noexcept -> const parse_error<T> &;

    auto is_unmatched() const noexcept -> bool;

private:
    std::variant<matched<result_type>, unmatched, parse_error<T>> result_;
};

template <common::concepts::string_view_like T>
void print_parse_error(const parse_error<T> &error);

template <common::concepts::string_view_like T>
void print_parse_error(const parse_error<T> &error, std::ostream &stream);

template <common::concepts::string_view_like T, typename ResultT>
void print_parse_error(const parse_result<T, ResultT> &result);

template <common::concepts::string_view_like T, typename ResultT>
void print_parse_error(const parse_result<T, ResultT> &result, std::ostream &stream);

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const parse_result<T, ResultT> &lhs, const unmatched) noexcept -> bool;

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const unmatched, const parse_result<T, ResultT> &rhs) noexcept -> bool;

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const parse_result<T, ResultT> &lhs, const ResultT &rhs) noexcept -> bool;

template <common::concepts::string_view_like T, typename ResultT>
inline auto operator==(const ResultT &lhs, const parse_result<T, ResultT> &rhs) noexcept -> bool;

} // namespace aeon::rdp

#include <aeon/rdp/impl/parse_result_impl.h>

// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/rdp/cursor.h>
#include <aeon/common/string.h>
#include <type_traits>
#include <variant>

namespace aeon::rdp
{

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

class parse_error final
{
    template <typename ResultT>
    friend class parse_result;

public:
    explicit parse_error(const parser &parser, common::string message) noexcept;

    ~parse_error() = default;

    parse_error(const parse_error &) = default;
    auto operator=(const parse_error &) -> parse_error & = default;

    parse_error(parse_error &&) noexcept = default;
    auto operator=(parse_error &&) noexcept -> parse_error & = default;

    [[nodiscard]] auto cursor() const noexcept -> const rdp::cursor &;

    [[nodiscard]] auto message() const noexcept -> const common::string &;

private:
    rdp::cursor cursor_;
    common::string message_;
};

template <typename ResultT = bool>
class parse_result final
{
public:
    using result_type = ResultT;

    parse_result() noexcept;
    parse_result(unmatched result) noexcept;
    parse_result(matched<ResultT> result) noexcept;
    parse_result(parse_error error);

    ~parse_result() noexcept = default;

    parse_result(const parse_result<ResultT> &) = default;
    auto operator=(const parse_result<ResultT> &) -> parse_result<ResultT> & = default;

    parse_result(parse_result<ResultT> &&) noexcept = default;
    auto operator=(parse_result<ResultT> &&) noexcept -> parse_result<ResultT> & = default;

    auto result() const noexcept -> bool;

    operator bool() const noexcept;

    auto value() noexcept -> result_type &;

    auto value() const noexcept -> const result_type &;

    auto operator*() noexcept -> result_type &;

    auto operator*() const noexcept -> const result_type &;

    auto is_error() const noexcept -> bool;

    auto error() const noexcept -> const parse_error &;

    auto is_unmatched() const noexcept -> bool;

private:
    std::variant<matched<result_type>, unmatched, parse_error> result_;
};

void print_parse_error(const parse_error &error);

void print_parse_error(const parse_error &error, std::ostream &stream);

template <typename ResultT>
void print_parse_error(const parse_result<ResultT> &result);

template <typename ResultT>
void print_parse_error(const parse_result<ResultT> &result, std::ostream &stream);

template <typename ResultT>
inline auto operator==(const parse_result<ResultT> &lhs, const unmatched) noexcept -> bool;

template <typename ResultT>
inline auto operator==(const unmatched, const parse_result<ResultT> &rhs) noexcept -> bool;

template <typename ResultT>
inline auto operator==(const parse_result<ResultT> &lhs, const ResultT &rhs) noexcept -> bool;

template <typename ResultT>
inline auto operator==(const ResultT &lhs, const parse_result<ResultT> &rhs) noexcept -> bool;

} // namespace aeon::rdp

#include <aeon/rdp/impl/parse_result_impl.h>

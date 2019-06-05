// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/rdp/cursor.h>
#include <type_traits>
#include <string>
#include <variant>

namespace aeon::rdp
{

class parser;

template <typename T = bool>
class matched
{
public:
    explicit matched() noexcept;

    explicit matched(T value) noexcept(std::is_nothrow_move_constructible_v<T>);

    ~matched() = default;

    matched(const matched<T> &) noexcept(std::is_nothrow_copy_constructible_v<T>) = default;
    auto operator=(const matched<T> &) noexcept(std::is_nothrow_copy_assignable_v<T>) -> matched<T> & = default;

    matched(matched<T> &&) noexcept(std::is_nothrow_move_constructible_v<T>) = default;
    auto operator=(matched<T> &&) noexcept(std::is_nothrow_move_assignable_v<T>) -> matched<T> & = default;

    auto value() const noexcept -> const T &;

private:
    T value_;
};

class unmatched final
{
};

class parse_error final
{
    template <typename T>
    friend class parse_result;

public:
    explicit parse_error(const parser &parser, std::string message) noexcept;

    ~parse_error() = default;

    parse_error(const parse_error &) = default;
    auto operator=(const parse_error &) -> parse_error & = default;

    parse_error(parse_error &&) noexcept = default;
    auto operator=(parse_error &&) noexcept -> parse_error & = default;

    auto cursor() const noexcept -> const rdp::cursor &;

    auto message() const noexcept -> const std::string &;

private:
    rdp::cursor cursor_;
    std::string message_;
};

template <typename T = bool>
class parse_result final
{
public:
    parse_result() noexcept;
    parse_result(unmatched result) noexcept;
    parse_result(matched<T> result) noexcept;
    parse_result(parse_error error);

    ~parse_result() noexcept = default;

    parse_result(const parse_result<T> &) = default;
    auto operator=(const parse_result<T> &) -> parse_result<T> & = default;

    parse_result(parse_result<T> &&) noexcept = default;
    auto operator=(parse_result<T> &&) noexcept -> parse_result<T> & = default;

    auto result() const noexcept -> bool;

    operator bool() const noexcept;

    auto value() const noexcept -> const T &;

    auto operator*() const noexcept -> const T &;

    auto is_error() const noexcept -> bool;

    auto error() const noexcept -> const parse_error &;

    auto is_unmatched() const noexcept -> bool;

private:
    std::variant<matched<T>, unmatched, parse_error> result_;
};

void print_parse_error(const parse_error &error);
void print_parse_error(const parse_error &error, std::ostream &stream);

template <typename T>
void print_parse_error(const parse_result<T> &result);

template <typename T>
void print_parse_error(const parse_result<T> &result, std::ostream &stream);

template <typename T>
inline auto operator==(const parse_result<T> &lhs, const unmatched) noexcept -> bool;

template <typename T>
inline auto operator==(const unmatched, const parse_result<T> &rhs) noexcept -> bool;

template <typename T>
inline auto operator==(const parse_result<T> &lhs, const T &rhs) noexcept -> bool;

template <typename T>
inline auto operator==(const T &lhs, const parse_result<T> &rhs) noexcept -> bool;

} // namespace aeon::rdp

#include <aeon/rdp/impl/parse_result_impl.h>

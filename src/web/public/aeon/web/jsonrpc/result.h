// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/ptree/ptree.h>
#include <string>
#include <optional>

namespace aeon::web::jsonrpc
{

enum class rpc_result_type
{
    result,
    error
};

namespace json_rpc_error
{
static constexpr int parse_error = -32700;
static constexpr int invalid_request = -32600;
static constexpr int method_not_found = -32601;
static constexpr int invalid_params = -32602;
static constexpr int internal_error = -32603;
static constexpr int server_error = -32000; // -32000 to -32099 are reserved for implementation-defined server-errors.
} // namespace json_rpc_error

class result
{
    friend class server;

public:
    explicit result(ptree::property_tree &&result);
    explicit result(const int error_code, std::string description);

    ~result() = default;

    result(result &&) = default;
    auto operator=(result &&) -> result & = default;

    result(const result &) = default;
    auto operator=(const result &) -> result & = default;

    [[nodiscard]] auto id() const noexcept
    {
        return id_;
    }

    [[nodiscard]] auto has_id() const noexcept
    {
        return id_.has_value();
    }

    [[nodiscard]] auto type() const noexcept
    {
        return result_type_;
    }

    [[nodiscard]] auto &result_type() const noexcept
    {
        return result_;
    }

    [[nodiscard]] auto error_code() const noexcept
    {
        return error_code_;
    }

    [[nodiscard]] auto &error_description() const noexcept
    {
        return error_description_;
    }

private:
    explicit result(ptree::property_tree &&result, const std::optional<int> id);
    explicit result(const int error_code, std::string description, const std::optional<int> id);

    void set_id(const int id) noexcept
    {
        id_ = id;
    }

    std::optional<int> id_;
    rpc_result_type result_type_;
    ptree::property_tree result_;
    int error_code_;
    std::string error_description_;
};

} // namespace aeon::web::jsonrpc

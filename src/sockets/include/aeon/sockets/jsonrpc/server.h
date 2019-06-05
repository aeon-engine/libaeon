// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/jsonrpc/method.h>
#include <aeon/sockets/jsonrpc/result.h>
#include <json11.hpp>
#include <string>

namespace aeon::sockets::jsonrpc
{

auto respond(const result &result) -> json11::Json;

class server
{
public:
    server() = default;
    ~server() = default;

    server(server &&) = default;
    auto operator=(server &&) -> server & = default;

    server(const server &) = default;
    auto operator=(const server &) -> server & = default;

    void register_method(const method &method);

    auto request(const std::string &str) const -> std::string;
    auto request(const json11::Json &request) const -> json11::Json;

private:
    auto handle_requests(const json11::Json &request) const -> std::vector<result>;
    auto handle_single_rpc_request(const json11::Json &request) const -> result;

    std::map<std::string, method> methods_;
};

} // namespace aeon::sockets::jsonrpc

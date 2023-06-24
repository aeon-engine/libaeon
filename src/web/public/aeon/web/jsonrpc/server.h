// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/web/jsonrpc/method.h>
#include <aeon/web/jsonrpc/result.h>
#include <aeon/ptree/ptree.h>
#include <aeon/common/string.h>
#include <map>

namespace aeon::web::jsonrpc
{

auto respond(const result &result) -> ptree::property_tree;

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

    [[nodiscard]] auto request(const common::string &str) const -> common::string;
    [[nodiscard]] auto request(const ptree::property_tree &request) const -> ptree::property_tree;

private:
    [[nodiscard]] auto handle_requests(const ptree::property_tree &request) const -> std::vector<result>;
    [[nodiscard]] auto handle_single_rpc_request(const ptree::property_tree &request) const -> result;

    std::map<common::string, method> methods_;
};

} // namespace aeon::web::jsonrpc

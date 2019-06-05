// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/jsonrpc/server.h>
#include <aeon/sockets/http/route.h>
#include <string>
#include <memory>

namespace aeon::sockets::http
{

class rpc_result;

class http_jsonrpc_route : public route
{
public:
    explicit http_jsonrpc_route(const std::string &mount_point);
    explicit http_jsonrpc_route(const std::string &mount_point, std::unique_ptr<jsonrpc::server> json_rpc_server);
    explicit http_jsonrpc_route(const std::string &mount_point, jsonrpc::server &json_rpc_server);
    virtual ~http_jsonrpc_route();

    http_jsonrpc_route(http_jsonrpc_route &&) = delete;
    auto operator=(http_jsonrpc_route &&) -> http_jsonrpc_route & = delete;

    http_jsonrpc_route(const http_jsonrpc_route &) = delete;
    auto operator=(const http_jsonrpc_route &) -> http_jsonrpc_route & = delete;

    void register_method(const jsonrpc::method &method) const;

private:
    void on_http_request(http_server_socket &source, routable_http_server_session &session,
                         const request &request) override;

    auto validate_request(http_server_socket &source, const request &request) const -> bool;

    std::unique_ptr<jsonrpc::server> rpc_server_;
    jsonrpc::server &rpc_server_ref_;
};

} // namespace aeon::sockets::http

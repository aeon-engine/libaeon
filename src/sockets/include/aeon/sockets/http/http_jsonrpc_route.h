/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

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

    http_jsonrpc_route(http_jsonrpc_route &&) = default;
    auto operator=(http_jsonrpc_route &&) -> http_jsonrpc_route & = default;

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

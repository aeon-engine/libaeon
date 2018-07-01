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

#include <aeon/sockets/http/rpc/rpc_method.h>
#include <aeon/sockets/http/route.h>
#include <aeon/common/stdoptional.h>
#include <string>
#include <map>

namespace aeon::sockets::http::rpc
{

namespace json_rpc_error
{
static constexpr int parse_error = -32700;
static constexpr int invalid_request = -32600;
static constexpr int method_not_found = -32601;
static constexpr int invalid_params = -32602;
static constexpr int internal_error = -32603;
static constexpr int server_error = -32000; // -32000 to -32099 are reserved for implementation-defined server-errors.
} // namespace json_rpc_error

class rpc_result;

class http_json_rpc_route : public route
{
public:
    explicit http_json_rpc_route(const std::string &mount_point);
    virtual ~http_json_rpc_route();

    http_json_rpc_route(http_json_rpc_route &&) = default;
    auto operator=(http_json_rpc_route &&) -> http_json_rpc_route & = default;

    http_json_rpc_route(const http_json_rpc_route &) = delete;
    auto operator=(const http_json_rpc_route &) -> http_json_rpc_route & = delete;

    void register_method(const rpc_method &method);

private:
    void on_http_request(http_server_socket &source, routable_http_server_session &session,
                         const request &request) override;

    auto generate_response(const rpc_result &result, const std::optional<std::string> &id = std::nullopt) const
        -> json11::Json;
    auto generate_json_object_response(const rpc_result &result) const -> json11::Json;
    auto generate_error_response(const rpc_result &result) const -> json11::Json;

    auto handle_rpc_requests(routable_http_server_session &session, const request &request) const
        -> std::vector<rpc_result>;
    auto handle_single_rpc_request(const json11::Json &request) const -> rpc_result;

    std::map<std::string, rpc_method> methods_;
};

} // namespace aeon::sockets::http::rpc

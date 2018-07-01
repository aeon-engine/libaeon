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

#include <aeon/sockets/http/http_jsonrpc_route.h>
#include <aeon/sockets/jsonrpc/result.h>
#include <aeon/sockets/http/request.h>
#include <aeon/sockets/http/http_server_socket.h>
#include <json11.hpp>

namespace aeon::sockets::http
{

static const auto json_rpc_content_type = "application/json";
static const auto error_respond_type = "text/plain";

http_jsonrpc_route::http_jsonrpc_route(const std::string &mount_point)
    : http_jsonrpc_route{mount_point, std::make_unique<jsonrpc::server>()}
{
}

http_jsonrpc_route::http_jsonrpc_route(const std::string &mount_point, std::unique_ptr<jsonrpc::server> json_rpc_server)
    : route{mount_point}
    , rpc_server_{std::move(json_rpc_server)}
    , rpc_server_ref_{*rpc_server_}
{
}

http_jsonrpc_route::http_jsonrpc_route(const std::string &mount_point, jsonrpc::server &json_rpc_server)
    : route{mount_point}
    , rpc_server_{}
    , rpc_server_ref_{json_rpc_server}
{
}

http_jsonrpc_route::~http_jsonrpc_route() = default;

void http_jsonrpc_route::register_method(const jsonrpc::method &method) const
{
    rpc_server_ref_.register_method(method);
}

void http_jsonrpc_route::on_http_request(http_server_socket &source, routable_http_server_session &session,
                                         const request &request)
{
    if (!validate_request(source, request))
        return;

    const auto result = rpc_server_ref_.request(request.get_content_string());
    source.respond(json_rpc_content_type, result);
}

auto http_jsonrpc_route::validate_request(http_server_socket &source, const request &request) const -> bool
{
    if (!request.has_content())
    {
        const auto response =
            jsonrpc::respond(jsonrpc::result{jsonrpc::json_rpc_error::parse_error, "No content"}).dump();
        source.respond(json_rpc_content_type, response);
        return false;
    }

    if (request.get_content_type() != json_rpc_content_type)
    {
        const auto response = jsonrpc::respond(jsonrpc::result{jsonrpc::json_rpc_error::parse_error,
                                                               "Invalid content type. Expected application/json."})
                                  .dump();
        source.respond(json_rpc_content_type, response);
        return false;
    }

    return true;
}

} // namespace aeon::sockets::http

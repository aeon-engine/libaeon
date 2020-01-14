// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/web/http/http_jsonrpc_route.h>
#include <aeon/web/jsonrpc/result.h>
#include <aeon/web/http/request.h>
#include <aeon/web/http/http_server_socket.h>
#include <aeon/ptree/ptree.h>
#include <aeon/ptree/serialization/serialization_json.h>

namespace aeon::web::http
{

static const auto json_rpc_content_type = "application/json";

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

void http_jsonrpc_route::on_http_request(http_server_socket &source,
                                         [[maybe_unused]] routable_http_server_session &session, const request &request)
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
        const auto response = ptree::serialization::to_json(
            jsonrpc::respond(jsonrpc::result{jsonrpc::json_rpc_error::parse_error, "No content"}));
        source.respond(json_rpc_content_type, response);
        return false;
    }

    if (request.get_content_type() != json_rpc_content_type)
    {
        const auto response = ptree::serialization::to_json(jsonrpc::respond(
            jsonrpc::result{jsonrpc::json_rpc_error::parse_error, "Invalid content type. Expected application/json."}));
        source.respond(json_rpc_content_type, response);
        return false;
    }

    return true;
}

} // namespace aeon::web::http

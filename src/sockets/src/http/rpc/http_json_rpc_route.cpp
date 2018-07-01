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

#include <aeon/sockets/http/rpc/http_json_rpc_route.h>
#include <aeon/sockets/http/rpc/rpc_result.h>
#include <aeon/sockets/http/request.h>
#include <aeon/sockets/http/http_server_socket.h>
#include <json11.hpp>

namespace aeon::sockets::http::rpc
{

static const auto json_rpc_content_type = "application/json";
static const auto json_rpc_version_string = "2.0";
static const auto error_respond_type = "text/plain";

http_json_rpc_route::http_json_rpc_route(const std::string &mount_point)
    : route{mount_point}
{
}

http_json_rpc_route::~http_json_rpc_route() = default;

void http_json_rpc_route::register_method(const rpc_method &method)
{
    const auto name = method.name();
    methods_.insert({name, method});
}

void http_json_rpc_route::on_http_request(http_server_socket &source, routable_http_server_session &session,
                                          const request &request)
{
    auto result = handle_rpc_requests(session, request);

    json11::Json response;

    // Batch request?
    if (result.size() > 1)
    {
        json11::Json::array response_array;
        for (const auto &r : result)
        {
            response_array.emplace_back(generate_response(r));
        }

        response = response_array;
    }
    else if (result.size() == 1)
    {
        response = generate_response(result.at(0));
    }
    else
    {
        source.respond_default(status_code::internal_server_error);
    }

    source.respond(json_rpc_content_type, response.dump());
}

auto http_json_rpc_route::generate_response(const rpc_result &result, const std::optional<std::string> &id) const
    -> json11::Json
{
    switch (result.type())
    {
        case rpc_result_type::result:
            return generate_json_object_response(result);
        case rpc_result_type::error:
        default:
            return generate_error_response(result);
    }
}

auto http_json_rpc_route::generate_json_object_response(const rpc_result &result) const -> json11::Json
{
    json11::Json id_obj;

    if (result.has_id())
        id_obj = json11::Json(result.id().value());

    return json11::Json::object{{"jsonrpc", json_rpc_version_string}, {"result", result.result()}, {"id", id_obj}};
}

auto http_json_rpc_route::generate_error_response(const rpc_result &result) const -> json11::Json
{
    json11::Json id_obj;

    if (result.has_id())
        id_obj = json11::Json(result.id().value());

    return json11::Json::object{
        {"jsonrpc", json_rpc_version_string},
        {"error", json11::Json::object{{"code", result.error_code()}, {"message", result.error_description()}}},
        {"id", id_obj}};
}

auto http_json_rpc_route::handle_rpc_requests(routable_http_server_session &session, const request &request) const
    -> std::vector<rpc_result>
{
    if (!request.has_content())
        return {rpc_result{json_rpc_error::parse_error, "No content"}};

    if (request.get_content_type() != json_rpc_content_type)
        return {rpc_result{json_rpc_error::parse_error, "Invalid content type. Expected application/json."}};

    const auto content = request.get_content_string();

    std::string error;
    const auto result = json11::Json::parse(content, error);

    if (result.is_null())
        return {rpc_result{json_rpc_error::parse_error, "Json parse error: " + error}};

    // Is this a batch request?
    if (result.is_array())
    {
        std::vector<rpc_result> results;
        for (const auto &r : result.array_items())
        {
            results.emplace_back(handle_single_rpc_request(r));
        }

        return results;
    }

    return {handle_single_rpc_request(result)};
}

auto http_json_rpc_route::handle_single_rpc_request(const json11::Json &request) const -> rpc_result
{
    auto jsonrpc_value = request["jsonrpc"];

    auto id_value = request["id"];

    if (id_value.is_null())
        return rpc_result{json_rpc_error::invalid_request, "Missing 'id' field."};

    if (!id_value.is_number())
        return rpc_result{json_rpc_error::invalid_request, "'Id' field must contain a number."};

    const auto id = id_value.int_value();

    if (jsonrpc_value.is_null())
        return rpc_result{json_rpc_error::invalid_request, "Missing 'jsonrpc' version field.", id};

    if (!jsonrpc_value.is_string())
        return rpc_result{json_rpc_error::invalid_request, "Invalid 'jsonrpc' version field.", id};

    if (jsonrpc_value.string_value() != json_rpc_version_string)
        return rpc_result{json_rpc_error::invalid_request, "Invalid rpc version. Required: '2.0'.", id};

    auto method_value = request["method"];

    if (method_value.is_null())
        return rpc_result{json_rpc_error::invalid_request, "Missing 'method' field.", id};

    if (!method_value.is_string())
        return rpc_result{json_rpc_error::invalid_request, "'method' field must contain a string.", id};

    const auto &method = method_value.string_value();

    const auto result = methods_.find(method);

    if (result == methods_.end())
        return rpc_result{json_rpc_error::method_not_found, "Method not found.", id};

    auto method_result = result->second(request["params"]);
    method_result.set_id(id);
    return method_result;
}

} // namespace aeon::sockets::http::rpc

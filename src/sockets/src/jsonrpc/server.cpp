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

#include <aeon/sockets/jsonrpc/server.h>

static const auto json_rpc_version_string = "2.0";

namespace aeon::sockets::jsonrpc
{

namespace detail
{

auto respond_object(const result &result) -> json11::Json
{
    json11::Json id_obj;

    if (result.has_id())
        id_obj = json11::Json(result.id().value());

    return json11::Json::object{{"jsonrpc", json_rpc_version_string}, {"result", result.result_type()}, {"id", id_obj}};
}

auto respond_error(const result &result) -> json11::Json
{
    json11::Json id_obj;

    if (result.has_id())
        id_obj = json11::Json(result.id().value());

    return json11::Json::object{
        {"jsonrpc", json_rpc_version_string},
        {"error", json11::Json::object{{"code", result.error_code()}, {"message", result.error_description()}}},
        {"id", id_obj}};
}

} // namespace detail

auto respond(const result &result) -> json11::Json
{
    switch (result.type())
    {
        case rpc_result_type::result:
            return detail::respond_object(result);
        case rpc_result_type::error:
        default:
            return detail::respond_error(result);
    }
}

void server::register_method(const method &method)
{
    const auto &name = method.name();
    methods_.insert({name, method});
}

auto server::request(const std::string &request) const -> std::string
{
    auto request_result = handle_requests(request);

    json11::Json response;

    // Batch request?
    if (request_result.size() > 1)
    {
        json11::Json::array response_array;
        for (const auto &r : request_result)
        {
            response_array.emplace_back(respond(r));
        }

        response = response_array;
    }
    else if (request_result.size() == 1)
    {
        response = respond(request_result.at(0));
    }
    else
    {
        response = detail::respond_error(result{json_rpc_error::server_error, "Internal server error"});
    }

    return response.dump();
}

auto server::handle_requests(const std::string &request) const -> std::vector<result>
{
    if (request.empty())
        return {result{json_rpc_error::parse_error, "No content"}};

    std::string error;
    const auto json = json11::Json::parse(request, error);

    if (json.is_null())
        return {result{json_rpc_error::parse_error, "Json parse error: " + error}};

    // Is this a batch request?
    if (json.is_array())
    {
        std::vector<result> results;
        for (const auto &r : json.array_items())
        {
            results.emplace_back(handle_single_rpc_request(r));
        }

        return results;
    }

    return {handle_single_rpc_request(json)};
}

auto server::handle_single_rpc_request(const json11::Json &request) const -> result
{
    auto jsonrpc_value = request["jsonrpc"];

    auto id_value = request["id"];

    if (id_value.is_null())
        return result{json_rpc_error::invalid_request, "Missing 'id' field."};

    if (!id_value.is_number())
        return result{json_rpc_error::invalid_request, "'Id' field must contain a number."};

    const auto id = id_value.int_value();

    if (jsonrpc_value.is_null())
        return result{json_rpc_error::invalid_request, "Missing 'jsonrpc' version field.", id};

    if (!jsonrpc_value.is_string())
        return result{json_rpc_error::invalid_request, "Invalid 'jsonrpc' version field.", id};

    if (jsonrpc_value.string_value() != json_rpc_version_string)
        return result{json_rpc_error::invalid_request, "Invalid rpc version. Required: '2.0'.", id};

    auto method_value = request["method"];

    if (method_value.is_null())
        return result{json_rpc_error::invalid_request, "Missing 'method' field.", id};

    if (!method_value.is_string())
        return result{json_rpc_error::invalid_request, "'method' field must contain a string.", id};

    const auto &method = method_value.string_value();

    const auto itr = methods_.find(method);

    if (itr == methods_.end())
        return result{json_rpc_error::method_not_found, "Method not found.", id};

    auto method_result = itr->second(request["params"]);
    method_result.set_id(id);
    return method_result;
}

} // namespace aeon::sockets::jsonrpc

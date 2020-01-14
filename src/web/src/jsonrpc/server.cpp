// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/web/jsonrpc/server.h>
#include <aeon/ptree/serialization/serialization_json.h>

static const auto json_rpc_version_string = "2.0";

namespace aeon::web::jsonrpc
{

namespace detail
{

auto respond_object(const result &result) -> ptree::property_tree
{
    ptree::property_tree id_obj;

    if (result.has_id())
        id_obj = ptree::property_tree(result.id().value());

    return ptree::object{{"jsonrpc", json_rpc_version_string}, {"result", result.result_type()}, {"id", id_obj}};
}

auto respond_error(const result &result) -> ptree::property_tree
{
    ptree::property_tree id_obj;

    if (result.has_id())
        id_obj = ptree::property_tree(result.id().value());

    return ptree::object{
        {"jsonrpc", json_rpc_version_string},
        {"error", ptree::object{{"code", result.error_code()}, {"message", result.error_description()}}},
        {"id", id_obj}};
}

} // namespace detail

auto respond(const result &result) -> ptree::property_tree
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

auto server::request(const std::string &str) const -> std::string
{
    if (str.empty())
        return ptree::serialization::to_json(detail::respond_error(result{json_rpc_error::parse_error, "No content"}));

    const auto json = ptree::serialization::from_json(str);

    if (json.is_null())
        return ptree::serialization::to_json(
            detail::respond_error(result{json_rpc_error::parse_error, "Json parse error."}));

    return ptree::serialization::to_json(request(json));
}

auto server::request(const ptree::property_tree &request) const -> ptree::property_tree
{
    auto request_result = handle_requests(request);

    // Batch request?
    if (request_result.size() > 1)
    {
        ptree::array response_array;
        for (const auto &r : request_result)
        {
            response_array.emplace_back(respond(r));
        }

        return response_array;
    }

    if (request_result.size() == 1)
        return respond(request_result.at(0));

    return detail::respond_error(result{json_rpc_error::invalid_request, "No content"});
}

auto server::handle_requests(const ptree::property_tree &request) const -> std::vector<result>
{
    if (request.is_null())
        return {result{json_rpc_error::parse_error, "Json parse error."}};

    // Is this a batch request?
    if (request.is_array())
    {
        std::vector<result> results;
        for (const auto &r : request.array_value())
        {
            results.emplace_back(handle_single_rpc_request(r));
        }

        return results;
    }

    return {handle_single_rpc_request(request)};
}

auto server::handle_single_rpc_request(const ptree::property_tree &request) const -> result
{
    if (!request.is_object())
        return result{json_rpc_error::invalid_request, "Invalid request format."};

    if (!request.contains("jsonrpc"))
        return result{json_rpc_error::invalid_request, "Missing 'jsonrpc' field."};

    if (!request.contains("id"))
        return result{json_rpc_error::invalid_request, "Missing 'id' field."};

    auto id_value = request.at("id");
    auto jsonrpc_value = request.at("jsonrpc");

    if (!id_value.is_integer())
        return result{json_rpc_error::invalid_request, "'Id' field must contain a number."};

    // TODO: Check if ID is out of bounds
    const auto id = static_cast<int>(id_value.integer_value());

    if (jsonrpc_value.is_null())
        return result{json_rpc_error::invalid_request, "Missing 'jsonrpc' version field.", id};

    if (!jsonrpc_value.is_string())
        return result{json_rpc_error::invalid_request, "Invalid 'jsonrpc' version field.", id};

    if (jsonrpc_value.string_value() != json_rpc_version_string)
        return result{json_rpc_error::invalid_request, "Invalid rpc version. Required: '2.0'.", id};

    if (request.contains("method"))
        return result{json_rpc_error::invalid_request, "Missing 'method' field.", id};

    auto method_value = request.at("method");

    if (!method_value.is_string())
        return result{json_rpc_error::invalid_request, "'method' field must contain a string.", id};

    const auto &method = method_value.string_value();

    const auto itr = methods_.find(method);

    if (itr == methods_.end())
        return result{json_rpc_error::method_not_found, "Method not found.", id};

    auto params = ptree::property_tree{};

    if (request.contains("params"))
        params = request.at("params");

    auto method_result = itr->second(params);
    method_result.set_id(id);

    return method_result;
}

} // namespace aeon::web::jsonrpc

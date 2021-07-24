// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/status_code.h>

namespace aeon::web::http
{

static const auto internal_server_error_str = u8"Internal Server Error";

struct status_code_lookup_t
{
    status_code code = status_code::internal_server_error;
    const char8_t *str = internal_server_error_str;
};

static const status_code_lookup_t status_code_lookup[] = {
    {status_code::continue_100, u8"Continue"},
    {status_code::switching_protocols, u8"Switching Protocols"},
    {status_code::processing, u8"Processing"},
    {status_code::early_hints, u8"Early Hints"},
    {status_code::ok, u8"Ok"},
    {status_code::created, u8"Created"},
    {status_code::accepted, u8"Accepted"},
    {status_code::non_authoritative_information, u8"Non-Authoritative Information"},
    {status_code::no_content, u8"No Content"},
    {status_code::reset_content, u8"Reset Content"},
    {status_code::partial_content, u8"Partial Content"},
    {status_code::multi_status, u8"Multi-Status"},
    {status_code::already_reported, u8"Already Reported"},
    {status_code::im_used, u8"IM Used"},
    {status_code::multiple_choices, u8"Multiple Choices"},
    {status_code::moved_permanently, u8"Moved Permanently"},
    {status_code::found, u8"Found"},
    {status_code::see_other, u8"See Other"},
    {status_code::not_modified, u8"Not Modified"},
    {status_code::use_proxy, u8"Use Proxy"},
    {status_code::switch_proxy, u8"Switch Proxy"},
    {status_code::temporary_redirect, u8"Temporary Redirect"},
    {status_code::permanent_redirect, u8"Permanent Redirect"},
    {status_code::bad_request, u8"Bad Request"},
    {status_code::unauthorized, u8"Unauthorized"},
    {status_code::payment_required, u8"Payment Required"},
    {status_code::forbidden, u8"Forbidden"},
    {status_code::not_found, u8"Not Found"},
    {status_code::method_not_allowed, u8"Method Not Allowed"},
    {status_code::not_acceptable, u8"Not Acceptable"},
    {status_code::proxy_authentication_required, u8"Proxy Authentication Required"},
    {status_code::request_timeout, u8"Request Timeout"},
    {status_code::conflict, u8"Conflict"},
    {status_code::gone, u8"Gone"},
    {status_code::length_required, u8"Length Required"},
    {status_code::precondition_failed, u8"Precondition Failed"},
    {status_code::payload_too_large, u8"Payload Too Large"},
    {status_code::uri_too_long, u8"URI Too Long"},
    {status_code::unsupported_media_type, u8"Unsupported Media Type"},
    {status_code::range_not_satisfiable, u8"Range Not Satisfiable"},
    {status_code::expectation_failed, u8"Expectation Failed"},
    {status_code::im_a_teapot, u8"I'm a teapot"},
    {status_code::misdirected_request, u8"Misdirected Request"},
    {status_code::unprocessable_entity, u8"Unprocessable Entity"},
    {status_code::locked, u8"Locked"},
    {status_code::failed_dependency, u8"Failed Dependency"},
    {status_code::upgrade_required, u8"Upgrade Required"},
    {status_code::precondition_required, u8"Precondition Required"},
    {status_code::too_many_requests, u8"Too Many Requests"},
    {status_code::request_header_fields_too_large, u8"Request Header Fields Too Large"},
    {status_code::unavailable_for_legal_reasons, u8"Unavailable For Legal Reasons"},
    {status_code::internal_server_error, internal_server_error_str},
    {status_code::not_implemented, u8"Not Implemented"},
    {status_code::bad_gateway, u8"Bad Gateway"},
    {status_code::service_unavailable, u8"Service Unavailable"},
    {status_code::gateway_timeout, u8"Gateway Timeout"},
    {status_code::http_version_not_supported, u8"HTTP Version Not Supported"},
    {status_code::variant_also_negotiates, u8"Variant Also Negotiates"},
    {status_code::insufficient_storage, u8"Insufficient Storage"},
    {status_code::loop_detected, u8"Loop Detected"},
    {status_code::not_extended, u8"Not Extended"},
    {status_code::network_authentication_required, u8"Network Authentication Required"}};

auto verify_status_code(const int code) noexcept -> bool
{
    for (const auto &status_code : status_code_lookup)
    {
        if (static_cast<int>(status_code.code) == code)
            return true;
    }

    return false;
}

auto status_code_to_string(const status_code code) noexcept -> const char8_t *
{
    for (const auto &status_code : status_code_lookup)
    {
        if (status_code.code == code)
            return status_code.str;
    }

    return internal_server_error_str;
}

} // namespace aeon::web::http

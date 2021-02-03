// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/status_code.h>

namespace aeon::web::http
{

static const auto internal_server_error_str = "Internal Server Error";

struct status_code_lookup_t
{
    status_code code = status_code::internal_server_error;
    const char *str = internal_server_error_str;
};

static const status_code_lookup_t status_code_lookup[] = {
    {status_code::continue_100, "Continue"},
    {status_code::switching_protocols, "Switching Protocols"},
    {status_code::processing, "Processing"},
    {status_code::early_hints, "Early Hints"},
    {status_code::ok, "Ok"},
    {status_code::created, "Created"},
    {status_code::accepted, "Accepted"},
    {status_code::non_authoritative_information, "Non-Authoritative Information"},
    {status_code::no_content, "No Content"},
    {status_code::reset_content, "Reset Content"},
    {status_code::partial_content, "Partial Content"},
    {status_code::multi_status, "Multi-Status"},
    {status_code::already_reported, "Already Reported"},
    {status_code::im_used, "IM Used"},
    {status_code::multiple_choices, "Multiple Choices"},
    {status_code::moved_permanently, "Moved Permanently"},
    {status_code::found, "Found"},
    {status_code::see_other, "See Other"},
    {status_code::not_modified, "Not Modified"},
    {status_code::use_proxy, "Use Proxy"},
    {status_code::switch_proxy, "Switch Proxy"},
    {status_code::temporary_redirect, "Temporary Redirect"},
    {status_code::permanent_redirect, "Permanent Redirect"},
    {status_code::bad_request, "Bad Request"},
    {status_code::unauthorized, "Unauthorized"},
    {status_code::payment_required, "Payment Required"},
    {status_code::forbidden, "Forbidden"},
    {status_code::not_found, "Not Found"},
    {status_code::method_not_allowed, "Method Not Allowed"},
    {status_code::not_acceptable, "Not Acceptable"},
    {status_code::proxy_authentication_required, "Proxy Authentication Required"},
    {status_code::request_timeout, "Request Timeout"},
    {status_code::conflict, "Conflict"},
    {status_code::gone, "Gone"},
    {status_code::length_required, "Length Required"},
    {status_code::precondition_failed, "Precondition Failed"},
    {status_code::payload_too_large, "Payload Too Large"},
    {status_code::uri_too_long, "URI Too Long"},
    {status_code::unsupported_media_type, "Unsupported Media Type"},
    {status_code::range_not_satisfiable, "Range Not Satisfiable"},
    {status_code::expectation_failed, "Expectation Failed"},
    {status_code::im_a_teapot, "I'm a teapot"},
    {status_code::misdirected_request, "Misdirected Request"},
    {status_code::unprocessable_entity, "Unprocessable Entity"},
    {status_code::locked, "Locked"},
    {status_code::failed_dependency, "Failed Dependency"},
    {status_code::upgrade_required, "Upgrade Required"},
    {status_code::precondition_required, "Precondition Required"},
    {status_code::too_many_requests, "Too Many Requests"},
    {status_code::request_header_fields_too_large, "Request Header Fields Too Large"},
    {status_code::unavailable_for_legal_reasons, "Unavailable For Legal Reasons"},
    {status_code::internal_server_error, internal_server_error_str},
    {status_code::not_implemented, "Not Implemented"},
    {status_code::bad_gateway, "Bad Gateway"},
    {status_code::service_unavailable, "Service Unavailable"},
    {status_code::gateway_timeout, "Gateway Timeout"},
    {status_code::http_version_not_supported, "HTTP Version Not Supported"},
    {status_code::variant_also_negotiates, "Variant Also Negotiates"},
    {status_code::insufficient_storage, "Insufficient Storage"},
    {status_code::loop_detected, "Loop Detected"},
    {status_code::not_extended, "Not Extended"},
    {status_code::network_authentication_required, "Network Authentication Required"}};

auto verify_status_code(const int code) noexcept -> bool
{
    for (const auto &status_code : status_code_lookup)
    {
        if (static_cast<int>(status_code.code) == code)
            return true;
    }

    return false;
}

auto status_code_to_string(const status_code code) noexcept -> const char *
{
    for (const auto &status_code : status_code_lookup)
    {
        if (status_code.code == code)
            return status_code.str;
    }

    return internal_server_error_str;
}

} // namespace aeon::web::http

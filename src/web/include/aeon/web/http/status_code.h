// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

namespace aeon::web::http
{

enum class status_code
{
    continue_100 = 100, // Continue is a reserved keyword...
    switching_protocols = 101,
    processing = 102,  // WebDAV, RF 2518
    early_hints = 103, // RFC 8297
    ok = 200,
    created = 201,
    accepted = 202,
    non_authoritative_information = 203,
    no_content = 204,
    reset_content = 205,
    partial_content = 206,  // RFC 7233
    multi_status = 207,     // WebDAV, RFC 4918
    already_reported = 208, // WebDAV, RFC 5842
    im_used = 226,          // RFC 3229
    multiple_choices = 300,
    moved_permanently = 301,
    found = 302,
    see_other = 303,
    not_modified = 304, // RFC 7232
    use_proxy = 305,
    switch_proxy = 306,
    temporary_redirect = 307,
    permanent_redirect = 308, // RFC 7538
    bad_request = 400,
    unauthorized = 401, // RFC 7235
    payment_required = 402,
    forbidden = 403,
    not_found = 404,
    method_not_allowed = 405,
    not_acceptable = 406,
    proxy_authentication_required = 407, // RFC 7235
    request_timeout = 408,
    conflict = 409,
    gone = 410,
    length_required = 411,
    precondition_failed = 412, // RFC 7232
    payload_too_large = 413,   // RFC 7231
    uri_too_long = 414,        // RFC 7231
    unsupported_media_type = 415,
    range_not_satisfiable = 416, // RFC 7233
    expectation_failed = 417,
    im_a_teapot = 418,          // RFC 2324
    misdirected_request = 421,  // RFC 7540
    unprocessable_entity = 422, // WebDAV, RFC 4918
    locked = 423,               // WebDAV, RFC 4918
    failed_dependency = 424,    // WebDAV, RFC 4918
    upgrade_required = 426,
    precondition_required = 428,           // RFC 6585
    too_many_requests = 429,               // RFC 6585
    request_header_fields_too_large = 431, // RFC 6585
    unavailable_for_legal_reasons = 451,   // RFC 7725
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503,
    gateway_timeout = 504,
    http_version_not_supported = 505,
    variant_also_negotiates = 506,         // RFC 2295
    insufficient_storage = 507,            // WebDAV, RFC 4918
    loop_detected = 508,                   // WebDAV, RFC 5842
    not_extended = 510,                    // RFC 2774
    network_authentication_required = 511, // RFC 6585
};

auto verify_status_code(const int code) noexcept -> bool;
auto status_code_to_string(const status_code code) noexcept -> const char *;

} // namespace aeon::web::http

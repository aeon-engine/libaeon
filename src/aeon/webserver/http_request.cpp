/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2016 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#include <aeon/webserver.h>

namespace aeon
{
namespace webserver
{

http_request::http_request(http_protocol_handler *handler, http_method method)
    : method_(method)
    , handler_(handler)
{
}

http_request::http_request(http_protocol_handler *handler, const std::string &method, const std::string &uri,
                           const std::string &version_string)
    : method_(__string_to_http_method(method))
    , uri_(uri)
    , version_string_(version_string)
    , handler_(handler)
{
    if (!__validate_http_version_string())
        method_ = http_method::invalid;

    if (!__validate_uri())
        method_ = http_method::invalid;
}

void http_request::append_raw_http_header_line(const std::string &header_line)
{
    std::cout << header_line << std::endl;
    raw_headers_.push_back(header_line);
}

bool http_request::parse_http_headers()
{
    for (const std::string &header_line : raw_headers_)
    {
        std::size_t header_name_end = header_line.find_first_of(':');

        if (header_name_end == std::string::npos)
            return false;

        if (header_name_end + 2 >= header_line.size())
            return false;

        std::string header_name = header_line.substr(0, header_name_end);
        std::string header_value = header_line.substr(header_name_end + 2);

        headers_[header_name] = header_value;
    }

    return true;
}

std::string http_request::get_header_value(const std::string &name)
{
    auto result = headers_.find(name);

    if (result == headers_.end())
        return "";

    return result->second;
}

void http_request::strip_uri_prefix(const std::string &prefix)
{
    const char last_char = *(--prefix.end());

    std::size_t strip_length = prefix.size();
    if (last_char == '/')
        --strip_length;

    if (strip_length > 0)
        uri_ = uri_.substr(strip_length);
}

bool http_request::__validate_http_version_string() const
{
    if (version_string_ != "HTTP/1.1")
        return false;

    return true;
}

bool http_request::__validate_uri()
{
    for (const char c : uri_)
    {
        //Valid character?
        if (!(
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '/' || c == '?' || c == '%' || c == '&' ||
            c == '=' || c == '+' || c == '-' || c == '*' ||
            c == '.' || c == '_' || c == '@' || c == ','))
        {
            return false;
        }
    }

    return true;
}

http_method http_request::__string_to_http_method(const std::string &str) const
{
    if (str == "GET")
        return http_method::get;

    if (str == "POST")
        return http_method::post;

    if (str == "HEAD")
        return http_method::head;

    if (str == "OPTIONS")
        return http_method::options;

    return http_method::invalid;
}

} // namespace webserver
} // namespace aeon

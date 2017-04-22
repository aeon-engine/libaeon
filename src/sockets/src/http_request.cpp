/*
 * Copyright (c) 2012-2017 Robin Degen
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

#include <aeon/sockets/webserver/http_request.h>
#include <iostream>

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

auto http_request::parse_http_headers() -> bool
{
    for (const std::string &header_line : raw_headers_)
    {
        auto header_name_end = header_line.find_first_of(':');

        if (header_name_end == std::string::npos)
            return false;

        if (header_name_end + 2 >= header_line.size())
            return false;

        auto header_name = header_line.substr(0, header_name_end);
        auto header_value = header_line.substr(header_name_end + 2);

        headers_[header_name] = header_value;
    }

    return true;
}

auto http_request::get_header_value(const std::string &name) -> std::string
{
    auto result = headers_.find(name);

    if (result == headers_.end())
        return "";

    return result->second;
}

void http_request::strip_uri_prefix(const std::string &prefix)
{
    auto last_char = *(--prefix.end());

    auto strip_length = prefix.size();
    if (last_char == '/')
        --strip_length;

    if (strip_length > 0)
        uri_ = uri_.substr(strip_length);
}

auto http_request::__validate_http_version_string() const -> bool
{
    if (version_string_ != "HTTP/1.1")
        return false;

    return true;
}

auto http_request::__validate_uri() const -> bool
{
    for (auto c : uri_)
    {
        // Valid character?
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '/' || c == '?' ||
              c == '%' || c == '&' || c == '=' || c == '+' || c == '-' || c == '*' || c == '.' || c == '_' ||
              c == '@' || c == ','))
        {
            return false;
        }
    }

    return true;
}

auto http_request::__string_to_http_method(const std::string &str) const -> http_method
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

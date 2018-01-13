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

#pragma once

#include <string>
#include <vector>
#include <map>

namespace aeon
{
namespace webserver
{

enum class http_method
{
    invalid,
    get,
    post,
    head,
    options
};

class http_protocol_handler;

class http_request
{
public:
    explicit http_request(http_protocol_handler *handler, http_method method);
    explicit http_request(http_protocol_handler *handler, const std::string &method, const std::string &uri,
                          const std::string &version_string);

    auto method() const
    {
        return method_;
    }

    auto uri() const
    {
        return uri_;
    }

    auto version_string() const
    {
        return version_string_;
    }

    auto handler() const
    {
        return handler_;
    }

    void strip_uri_prefix(const std::string &prefix);

    void append_raw_http_header_line(const std::string &header_line);

    auto parse_http_headers() -> bool;

    auto get_header_value(const std::string &name) -> std::string;

private:
    auto __string_to_http_method(const std::string &str) const -> http_method;

    auto __validate_http_version_string() const -> bool;
    auto __validate_uri() const -> bool;

    http_method method_;
    std::string uri_;
    std::string version_string_;
    http_protocol_handler *handler_;
    std::vector<std::string> raw_headers_;
    std::map<std::string, std::string> headers_;
};

} // namespace webserver
} // namespace aeon

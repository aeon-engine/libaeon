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

#pragma once

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

    http_method method() const
    {
        return method_;
    }

    const std::string &uri() const
    {
        return uri_;
    }

    const std::string &version_string() const
    {
        return version_string_;
    }

    http_protocol_handler *handler() const
    {
        return handler_;
    }

    void strip_uri_prefix(const std::string &prefix);

    void append_raw_http_header_line(const std::string &header_line);

    bool parse_http_headers();

    std::string get_header_value(const std::string &name);

private:
    http_method __string_to_http_method(const std::string &str) const;

    bool __validate_http_version_string() const;
    bool __validate_uri();

    http_method method_;
    std::string uri_;
    std::string version_string_;
    http_protocol_handler *handler_;
    std::vector<std::string> raw_headers_;
    std::map<std::string, std::string> headers_;
};

} // namespace webserver
} // namespace aeon

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

enum class status_code
{
    ok = 200,
    not_found = 404,
    internal_server_error = 500,
};

class http_protocol_handler : public sockets::line_protocol_handler
{
    enum class http_state
    {
        method,
        headers,
        reply
    };

public:
    explicit http_protocol_handler(asio::ip::tcp::socket socket);
    void on_line(const std::string &line) override;

    void respond(const std::string &content_type, const std::string &data, status_code code = status_code::ok);
    void respond(const std::string &content_type, streams::stream_ptr data, status_code code = status_code::ok);

    void respond_default(status_code code);

    virtual void on_http_request(http_request &request) = 0;

private:
    const char *__http_status_to_string(status_code code) const;

    http_state state_;
    http_request request_;
};

} // namespace webserver
} // namespace aeon

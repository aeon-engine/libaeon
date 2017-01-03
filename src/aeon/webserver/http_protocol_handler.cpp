/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2017 Robin Degen
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

static const char *STATUS_OK = "Ok";
static const char *STATUS_NOT_FOUND = "Not Found";
static const char *STATUS_INTERNAL_SERVER_ERROR = "Internal Server Error";

http_protocol_handler::http_protocol_handler(asio::ip::tcp::socket socket)
    : sockets::line_protocol_handler(std::move(socket))
    , state_(http_state::method)
    , request_(this, http_method::invalid)
{
}

void http_protocol_handler::on_line(const std::string &line)
{
    switch (state_)
    {
        case http_state::method:
        {
            std::vector<std::string> method_line_split = utility::string::split(line, ' ');

            if (method_line_split.size() != 3)
            {
                std::cout << "TODO: Method Parse error." << std::endl;
                return;
            }

            std::string method = method_line_split[0];
            std::string request_uri = method_line_split[1];
            std::string version_string = method_line_split[2];

            http_request request(this, method, request_uri, version_string);

            if (request.method() == http_method::invalid)
            {
                std::cout << "TODO: Method Parse error." << std::endl;
                return;
            }

            request_ = request;
            state_ = http_state::headers;
        }
        break;

        case http_state::headers:
        {
            if (line.empty())
            {
                state_ = http_state::reply;
                on_http_request(request_);
                return;
            }

            request_.append_raw_http_header_line(line);
        }
        break;

        case http_state::reply:
        {
            std::cout << "TODO: Did not expect to receive more data in "
                         "reply state"
                      << std::endl;
            return;
        }
        break;
    }
}

void http_protocol_handler::respond(const std::string &content_type, const std::string &data, status_code code)
{
    streams::memory_stream_ptr stream = std::make_shared<streams::memory_stream>();
    stream->write(reinterpret_cast<const std::uint8_t *>(data.c_str()), data.size());
    respond(content_type, stream, code);
}

void http_protocol_handler::respond(const std::string &content_type, streams::stream_ptr data, status_code code)
{
    streams::memory_stream_ptr stream = std::make_shared<streams::memory_stream>();
    std::string headers = "HTTP/1.0 " + std::to_string(static_cast<int>(code)) + " " + __http_status_to_string(code) +
                          "\r\n"
                          "Connection: close\r\n" // TODO: Support keep-alive
                          "Content-type: " +
                          content_type + "\r\n"
                                         "Content-Length: " +
                          std::to_string(data->size()) + "\r\n\r\n";

    stream->write(reinterpret_cast<const std::uint8_t *>(headers.c_str()), headers.size());
    send(stream);
    send(data);
}

void http_protocol_handler::respond_default(status_code code)
{
    respond("text/plain", __http_status_to_string(code), code);
}

const char *http_protocol_handler::__http_status_to_string(status_code code) const
{
    switch (code)
    {
        case status_code::ok:
            return STATUS_OK;
        case status_code::not_found:
            return STATUS_NOT_FOUND;
        case status_code::internal_server_error:
            return STATUS_INTERNAL_SERVER_ERROR;
    }

    return STATUS_INTERNAL_SERVER_ERROR;
}

} // namespace webserver
} // namespace aeon

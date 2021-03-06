// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/web/http/request.h>
#include <aeon/web/http/status_code.h>
#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/streams/stream.h>
#include <asio.hpp>
#include <string>

namespace aeon::web::http
{

namespace detail
{
auto validate_http_version_string(const std::string &version_string) -> bool;
auto validate_uri(const std::string &uri) -> bool;
} // namespace detail

class http_server_session;

class http_server_socket : public sockets::tcp_socket
{
    enum class http_state
    {
        server_read_method,
        server_read_headers,
        server_read_body,
        server_reply
    };

public:
    /*!
     * Server socket ctor
     */
    explicit http_server_socket(asio::ip::tcp::socket socket);

    ~http_server_socket() override;

    http_server_socket(http_server_socket &&) = delete;
    auto operator=(http_server_socket &&) -> http_server_socket & = delete;

    http_server_socket(const http_server_socket &) = delete;
    auto operator=(const http_server_socket &) -> http_server_socket & = delete;

    void respond(const std::string &content_type, const std::string &data, const status_code code = status_code::ok);
    void respond(const std::string &content_type, streams::idynamic_stream &data,
                 const status_code code = status_code::ok);

    void respond_default(const status_code code);

    virtual void on_http_request(const request &request) = 0;

private:
    void on_data(const std::uint8_t *data, const std::size_t size) override;

    auto __on_line(const std::string &line) -> status_code;

    auto __parse_expected_content_length_and_type() -> status_code;

    auto __enter_parse_body_state() -> status_code;
    void __enter_reply_state();

    auto __handle_read_method_state(const std::string &line) -> status_code;
    auto __handle_read_headers_state(const std::string &line) -> status_code;

    void __reset_state();

    http_state state_;
    request request_;
    streams::aggregate_device<streams::circular_buffer_filter, streams::memory_device<std::vector<char>>>
        circular_buffer_;
    std::streamoff expected_content_length_;
};

} // namespace aeon::web::http

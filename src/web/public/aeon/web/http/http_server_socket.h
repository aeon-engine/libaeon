// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#pragma once

#include <aeon/web/http/request.h>
#include <aeon/web/http/status_code.h>
#include <aeon/sockets/tcp_socket.h>
#include <aeon/streams/devices/memory_device.h>
#include <aeon/streams/filters/circular_buffer_filter.h>
#include <aeon/streams/stream.h>
#include <aeon/common/string.h>
#include <asio.hpp>

namespace aeon::web::http
{

namespace detail
{
auto validate_http_version_string(const common::string &version_string) -> bool;
auto validate_uri(const common::string &uri) -> bool;
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

    void respond(const common::string &content_type, const common::string &data,
                 const status_code code = status_code::ok);
    void respond(const common::string &content_type, std::vector<std::byte> data,
                 const status_code code = status_code::ok);

    void respond_default(const status_code code);

    virtual void on_http_request(const request &request) = 0;

private:
    void on_data(const std::span<const std::byte> &data) override;

    auto __on_line(const common::string &line) -> status_code;

    auto __parse_expected_content_length_and_type() -> status_code;

    auto __enter_parse_body_state() -> status_code;
    void __enter_reply_state();

    auto __handle_read_method_state(const common::string &line) -> status_code;
    auto __handle_read_headers_state(const common::string &line) -> status_code;

    void __reset_state();

    http_state state_;
    request request_;
    streams::aggregate_device<streams::circular_buffer_filter, streams::memory_device<std::vector<char>>>
        circular_buffer_;
    std::streamoff expected_content_length_;
};

} // namespace aeon::web::http

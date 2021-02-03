// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/route.h>

namespace aeon::web::http
{

class routable_http_server_session;

class routable_http_server_socket final : public http_server_socket
{
public:
    /*!
     * Server socket ctor
     */
    explicit routable_http_server_socket(asio::ip::tcp::socket socket, routable_http_server_session &session);

    ~routable_http_server_socket() final;

    routable_http_server_socket(routable_http_server_socket &&) = delete;
    auto operator=(routable_http_server_socket &&) -> routable_http_server_socket & = delete;

    routable_http_server_socket(const routable_http_server_socket &) = delete;
    auto operator=(const routable_http_server_socket &) -> routable_http_server_socket & = delete;

private:
    void on_http_request(const request &request) override;

    routable_http_server_session &session_;
};

} // namespace aeon::web::http

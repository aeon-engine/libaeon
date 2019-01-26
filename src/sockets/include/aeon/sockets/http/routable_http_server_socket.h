// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/http/http_server_socket.h>
#include <aeon/sockets/http/route.h>
#include <string>
#include <memory>

namespace aeon::sockets::http
{

class routable_http_server_session;

class routable_http_server_socket : public http_server_socket
{
public:
    /*!
     * Server socket ctor
     */
    explicit routable_http_server_socket(asio::ip::tcp::socket socket, routable_http_server_session &session);

    virtual ~routable_http_server_socket();

    routable_http_server_socket(routable_http_server_socket &&) = delete;
    auto operator=(routable_http_server_socket &&) -> routable_http_server_socket & = delete;

    routable_http_server_socket(const routable_http_server_socket &) = delete;
    auto operator=(const routable_http_server_socket &) -> routable_http_server_socket & = delete;

private:
    void on_http_request(const request &request) override;

    routable_http_server_session &session_;
};

} // namespace aeon::sockets::http

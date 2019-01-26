// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/http/routable_http_server_socket.h>
#include <aeon/sockets/http/routable_http_server_session.h>
#include <aeon/sockets/tcp_server.h>

namespace aeon::sockets::http
{

using routable_http_server =
    sockets::tcp_server<sockets::http::routable_http_server_socket, sockets::http::routable_http_server_session>;

} // namespace aeon::sockets::http

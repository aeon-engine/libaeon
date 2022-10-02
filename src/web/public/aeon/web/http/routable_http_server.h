// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/web/http/routable_http_server_socket.h>
#include <aeon/web/http/routable_http_server_session.h>
#include <aeon/sockets/tcp_server.h>

namespace aeon::web::http
{

using routable_http_server = sockets::tcp_server<routable_http_server_socket, routable_http_server_session>;

} // namespace aeon::web::http

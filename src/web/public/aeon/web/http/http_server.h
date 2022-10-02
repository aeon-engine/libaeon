// Distributed under the BSD 2-Clause License - Copyright 2012-2022 Robin Degen

#pragma once

#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/http_server_session.h>
#include <aeon/sockets/tcp_server.h>

namespace aeon::web::http
{

template <typename http_server_socket_t>
using http_server = sockets::tcp_server<http_server_socket_t, http_server_session>;

} // namespace aeon::web::http

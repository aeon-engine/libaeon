// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/http/http_server_socket.h>
#include <aeon/sockets/http/http_server_session.h>
#include <aeon/sockets/tcp_server.h>

namespace aeon::sockets::http
{

template <typename http_server_socket_t>
using http_server = sockets::tcp_server<typename http_server_socket_t, sockets::http::http_server_session>;

} // namespace aeon::sockets::http

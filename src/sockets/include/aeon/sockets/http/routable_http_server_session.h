// Copyright (c) 2012-2019 Robin Degen

#pragma once

#include <aeon/sockets/http/http_server_socket.h>
#include <aeon/sockets/http/route.h>
#include <aeon/sockets/http/http_server_session.h>
#include <string>
#include <memory>

namespace aeon::sockets::http
{

class routable_http_server_session : public http_server_session
{
public:
    explicit routable_http_server_session();
    virtual ~routable_http_server_session();

    routable_http_server_session(routable_http_server_session &&) = default;
    auto operator=(routable_http_server_session &&) -> routable_http_server_session & = default;

    routable_http_server_session(const routable_http_server_session &) = delete;
    auto operator=(const routable_http_server_session &) -> routable_http_server_session & = delete;

    void add_route(std::unique_ptr<route> route);
    void remove_route(const std::string &mountpoint);

    auto find_best_match_route(const std::string &path, std::string &route_path) const -> route *;

private:
    std::map<std::string, std::unique_ptr<route>> routes_;
};

} // namespace aeon::sockets::http

// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#pragma once

#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/route.h>
#include <aeon/web/http/http_server_session.h>
#include <string>
#include <memory>

namespace aeon::web::http
{

class routable_http_server_session final : public http_server_session
{
public:
    explicit routable_http_server_session();
    ~routable_http_server_session() final;

    routable_http_server_session(routable_http_server_session &&) = default;
    auto operator=(routable_http_server_session &&) -> routable_http_server_session & = default;

    routable_http_server_session(const routable_http_server_session &) = delete;
    auto operator=(const routable_http_server_session &) -> routable_http_server_session & = delete;

    void add_route(std::unique_ptr<route> route);
    void remove_route(const std::u8string &mountpoint);

    auto find_best_match_route(const std::u8string &path, std::u8string &route_path) const -> route *;

private:
    std::map<std::u8string, std::unique_ptr<route>> routes_;
};

} // namespace aeon::web::http

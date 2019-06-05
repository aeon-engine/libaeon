// Distributed under the BSD 2-Clause License - Copyright 2012-2019 Robin Degen

#pragma once

#include <string>

namespace aeon::web::http
{

class request;
class http_server_socket;
class routable_http_server_session;

class route
{
public:
    explicit route(std::string mount_point);
    virtual ~route() = default;

    route(route &&) = default;
    auto operator=(route &&) -> route & = default;

    route(const route &) = delete;
    auto operator=(const route &) -> route & = delete;

    virtual void on_http_request(http_server_socket &source, routable_http_server_session &session,
                                 const request &request) = 0;

    auto mount_point() const noexcept -> const std::string &;

private:
    std::string mount_point_;
};

inline route::route(std::string mount_point)
    : mount_point_{std::move(mount_point)}
{
}

inline auto route::mount_point() const noexcept -> const std::string &
{
    return mount_point_;
}

} // namespace aeon::web::http

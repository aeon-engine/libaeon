// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/routable_http_server_session.h>
#include <aeon/common/literals.h>

namespace aeon::web::http
{

routable_http_server_session::routable_http_server_session()
    : http_server_session{}
    , routes_{}
{
}

routable_http_server_session::~routable_http_server_session() = default;

void routable_http_server_session::add_route(std::unique_ptr<route> route)
{
    const auto mountpoint = route->mount_point();
    routes_.insert({mountpoint, std::move(route)});
}

void routable_http_server_session::remove_route(const std::u8string &mountpoint)
{
    routes_.erase(mountpoint);
}

auto routable_http_server_session::find_best_match_route(const std::u8string &path, std::u8string &route_path) const
    -> route *
{
    auto actual_path = path;

    if (path[0] != '/')
        actual_path = u8"/" + path;

    auto best_match_length = 0_size_t;
    route *best_match_route = nullptr;

    for (auto &[route, route_ptr] : routes_)
    {
        const auto route_path_length = route.length();

        // Due to possible mountpoints being inside other mountpoints, the best match provider is the one that
        // has the most in common with the path
        if (route_path_length > best_match_length)
        {
            if (actual_path.compare(0, route_path_length, route) == 0)
            {
                best_match_length = route_path_length;
                best_match_route = route_ptr.get();
            }
        }
    }

    if (!best_match_route)
        return nullptr;

    route_path = actual_path.substr(best_match_length);

    return best_match_route;
}

} // namespace aeon::web::http

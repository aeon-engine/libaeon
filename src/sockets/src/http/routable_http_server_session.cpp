/*
 * Copyright (c) 2012-2018 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <aeon/sockets/http/routable_http_server_session.h>
#include <aeon/common/literals.h>

namespace aeon::sockets::http
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

void routable_http_server_session::remove_route(const std::string &mountpoint)
{
    routes_.erase(mountpoint);
}

auto routable_http_server_session::find_best_match_route(const std::string &path, std::string &route_path) const
    -> route *
{
    auto actual_path = path;

    if (path[0] != '/')
        actual_path = "/" + path;

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

} // namespace aeon::sockets::http

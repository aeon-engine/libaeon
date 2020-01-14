// Distributed under the BSD 2-Clause License - Copyright 2012-2020 Robin Degen

#include <aeon/web/http/routable_http_server_socket.h>
#include <aeon/web/http/routable_http_server_session.h>

namespace aeon::web::http
{

routable_http_server_socket::routable_http_server_socket(asio::ip::tcp::socket socket,
                                                         routable_http_server_session &session)
    : http_server_socket{std::move(socket)}
    , session_{session}
{
}

routable_http_server_socket::~routable_http_server_socket() = default;

void routable_http_server_socket::on_http_request(const request &request)
{
    std::string route_path;
    auto route = session_.find_best_match_route(request.get_uri(), route_path);

    if (!route)
    {
        respond_default(status_code::not_found);
        return;
    }

    // Change the request so actually use the new route_path. This way, a route doesn't need to know
    // what the full path is it's mounted on.
    auto new_request = request;
    new_request.set_uri(route_path);

    route->on_http_request(*this, session_, new_request);
}

} // namespace aeon::web::http

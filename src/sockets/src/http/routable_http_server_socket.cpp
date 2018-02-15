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

#include <aeon/sockets/http/routable_http_server_socket.h>
#include <aeon/sockets/http/routable_http_server_session.h>

namespace aeon::sockets::http
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

} // namespace aeon::sockets::http

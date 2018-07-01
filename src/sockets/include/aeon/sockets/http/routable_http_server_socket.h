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

#pragma once

#include <aeon/sockets/http/http_server_socket.h>
#include <aeon/sockets/http/route.h>
#include <string>
#include <memory>

namespace aeon::sockets::http
{

class routable_http_server_session;

class routable_http_server_socket : public http_server_socket
{
public:
    /*!
     * Server socket ctor
     */
    explicit routable_http_server_socket(asio::ip::tcp::socket socket, routable_http_server_session &session);

    virtual ~routable_http_server_socket();

    routable_http_server_socket(routable_http_server_socket &&) = delete;
    auto operator=(routable_http_server_socket &&) -> routable_http_server_socket & = delete;

    routable_http_server_socket(const routable_http_server_socket &) = delete;
    auto operator=(const routable_http_server_socket &) -> routable_http_server_socket & = delete;

private:
    void on_http_request(const request &request) override;

    routable_http_server_session &session_;
};

} // namespace aeon::sockets::http

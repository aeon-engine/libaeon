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

#include <aeon/sockets/http/rest/rest_server.h>

namespace aeon::sockets::http::rest
{

rest_server::rest_server(asio::ip::tcp::socket socket)
    : http_server_protocol(std::move(socket))
    , methods_()
{
}

rest_server::~rest_server() = default;

void rest_server::register_rest_method(const std::string &uri, const rest_method &method)
{
    assert(!method.has_http_method(method::invalid));
    assert(!method.has_http_method(method::head));

    methods_.insert({uri, method});
}

void rest_server::on_http_request(request &request)
{
    // std::cout << "Request: " << request.get_uri() << "\n";

    if (request.get_method() == method::post)
    {
        // std::cout << "Received post data: " << request.get_content_length() << "\n";
        auto content = request.get_content();

        // utility::hexdump(stdout, content.data(), content.size());
    }

    respond("text/plain", "Hello!");
}

void rest_server::on_error(const std::error_code &)
{
}

} // namespace aeon::sockets::http::rest

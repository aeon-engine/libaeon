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

#include <gtest/gtest.h>
#include <aeon/sockets/tcp_server.h>
#include <aeon/sockets/webserver/http_protocol_handler.h>

using namespace aeon;

class test_protocol_handler : public webserver::http_protocol_handler
{
public:
    explicit test_protocol_handler(asio::ip::tcp::socket socket)
        : webserver::http_protocol_handler(std::move(socket))
    {
    }

    virtual ~test_protocol_handler() = default;

    void on_http_request(webserver::http_request &request) override
    {
        std::cout << "Request: " << request.uri() << "\n";
        respond("text/plain", "Hello!");
    }

    void on_error(asio::error_code /*ec*/) override
    {
    }
};
/*
TEST(test_sockets, test_sockets_create)
{
    asio::io_service service;
    aeon::sockets::tcp_server<test_protocol_handler> handler(service, 1337);
}
*/
/*
TEST(test_sockets, test_sockets_create)
{
    asio::io_service service;
    sockets::tcp_server<test_protocol_handler> handler(service, 80);
    service.run();
}
*/

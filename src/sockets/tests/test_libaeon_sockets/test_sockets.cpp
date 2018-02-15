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
#include <aeon/sockets/http/rest/rest_server.h>
#include <aeon/sockets/http/http_server_protocol.h>
#include <aeon/sockets/http/http_client_protocol.h>
#include <aeon/sockets/tcp_server.h>
#include <aeon/sockets/tcp_client.h>
#include <aeon/utility/hexdump.h>

using namespace aeon;

class test_client : public sockets::http::http_client_protocol
{
public:
    using sockets::http::http_client_protocol::http_client_protocol;

    void on_connected() override
    {
        std::cout << "On Connected.\n";
        request_async("localhost", "/test");
    }

    void on_error(const std::error_code &ec) override
    {
        std::cout << "On error: " << ec.message() << "\n";
    }

    void on_disconnected() override
    {
        std::cout << "On Disconnected.\n";
    }

    void on_http_reply(sockets::http::reply &reply) override
    {
        std::cout << "Reply: " << sockets::http::status_code_to_string(reply.get_status_code()) << "\n"
                  << reply.get_content_length() << "\n";
    }
};

class test_server : public sockets::http::http_server_protocol
{
    using sockets::http::http_server_protocol::http_server_protocol;

    void on_connected() override
    {
        std::cout << "Server: on connected.\n";
    }

    void on_error(const std::error_code &ec) override
    {
        std::cout << "On error: " << ec.message() << "\n";
    }

    void on_disconnected() override
    {
        std::cout << "On Disconnected.\n";
    }

    void on_http_request(sockets::http::request &request) override
    {
        std::cout << "Request: " << request.get_uri() << "\n";

        if (request.get_method() == sockets::http::method::post)
        {
            std::cout << "Received post data: " << request.get_content_length() << "\n";
            auto content = request.get_content();

            utility::hexdump(stdout, content.data(), content.size());
        }

        respond("text/plain", "Hello!");
    }
};

/*
TEST(test_sockets, test_sockets_create)
{
    asio::io_context service;
    aeon::sockets::tcp_server<test_protocol_handler> handler(service, 1337);
}
*/
/*

/*TEST(test_sockets, test_sockets_create)
{
    asio::io_context service;
    sockets::tcp_server<test_protocol_handler> handler(service, 80);
    service.run();
}
*/

/*
TEST(test_sockets, test_sockets_http_rest_create)
{
    asio::io_context service;
    sockets::tcp_server<test_server> handler(service, 80);

    sockets::tcp_client<test_client> client(service, "localhost", 80);

    service.run();
}
*/
// Distributed under the BSD 2-Clause License - Copyright 2012-2021 Robin Degen

#include <aeon/web/http/http_server_socket.h>
#include <aeon/web/http/http_client_socket.h>
#include <aeon/web/http/routable_http_server.h>
#include <aeon/web/http/static_route.h>
#include <aeon/web/http/http_jsonrpc_route.h>
#include <aeon/sockets/tcp_server.h>
#include <aeon/sockets/tcp_client.h>
#include <aeon/common/hexdump.h>
#include <aeon/common/u8_stream.h>
#include <gtest/gtest.h>

using namespace aeon;

class test_client : public web::http::http_client_socket
{
public:
    using web::http::http_client_socket::http_client_socket;

    void on_connected() override
    {
        std::cout << "On Connected.\n";
        request_async(u8"localhost", u8"/test");
    }

    void on_error(const std::error_code &ec) override
    {
        std::cout << "On error: " << ec.message() << "\n";
    }

    void on_disconnected() override
    {
        std::cout << "On Disconnected.\n";
    }

    void on_http_reply(web::http::reply &reply) override
    {
        std::cout << "Reply: " << std::u8string_view{web::http::status_code_to_string(reply.get_status_code())} << "\n"
                  << reply.get_content_length() << "\n";
    }
};

class test_server : public web::http::http_server_socket
{
    using web::http::http_server_socket::http_server_socket;

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

    void on_http_request(const web::http::request &request) override
    {
        std::cout << "Request: " << request.get_uri() << "\n";

        if (request.get_method() == web::http::http_method::post)
        {
            std::cout << "Received post data: " << request.get_content_length() << "\n";
            auto content = request.get_content();

            common::hexdump::pretty_print(stdout, content.data(), content.size());
        }

        respond(u8"text/plain", u8"Hello!");
    }
};

// TODO: Write socket tests

/*
TEST(test_sockets, test_sockets_http_rest_create)
{
    asio::io_context service;

    sockets::http::routable_http_server handler(service, 80);

    auto route = std::make_unique<sockets::http::http_jsonrpc_route>("/api");
    route->register_method({"subtract", [](const json11::Json &params) -> sockets::jsonrpc::result {
                                return sockets::jsonrpc::result{{params["a"].int_value() - params["b"].int_value()}};
                            }});
    route->register_method({"raise_error", [](const json11::Json &params) -> sockets::jsonrpc::result {
                                return sockets::jsonrpc::result{1337, "This is an error!"};
                            }});

    handler.get_session().add_route(std::move(route));
    handler.get_session().add_route(std::make_unique<sockets::http::static_route>("/", "D:/"));

    service.run();
}
*/

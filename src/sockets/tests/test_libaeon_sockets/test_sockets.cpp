// Distributed under the BSD 2-Clause License - Copyright 2012-2023 Robin Degen

#include <aeon/sockets/tcp_server.h>
#include <aeon/sockets/tcp_client.h>
#include <gtest/gtest.h>

using namespace aeon;

// TODO: Write socket tests

TEST(test_sockets, test_sockets_create)
{
    /*
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
    */
}
